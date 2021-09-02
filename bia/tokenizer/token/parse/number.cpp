#include "tokens.hpp"

#include <bia/error/exception.hpp>
#include <limits>
#include <string>
#include <tuple>
#include <type_traits>

using namespace bia;
using namespace bia::tokenizer::token;

/// Extracts the string from the code which can be parsed by one of the standard conversion functions. Returns
/// the number string, it's desired type, the base and an error.
inline std::tuple<std::string, Token::Number::Type, int, Error_info> extract_number(Parameter& param)
{
	using Type        = Token::Number::Type;
	const auto ranger = param.begin_range();
	std::string str;
	Type type = Type::i;
	int base  = 10;
	enum class State
	{
		start,
		suffix,
		floating_point,
		zero_start,
		decimal,
		hexadecimal,
		octal,
		binary,
	} state = State::start;
	// automata: 🤮🤮🤮🤮🤮🤮🤮🤮🤮🤮🤮🤮
	// no, i was not drunk
	while (true) {
		auto old     = param.reader.backup();
		const auto c = param.reader.read();
		if (c == string::encoding::Encoder::eof) {
			break;
		}

		// prefix check
		if (state == State::start && str.empty() && (c == '+' || c == '-')) {
			str.push_back(c);
			continue;
		}

		// suffix check
		if (state >= State::zero_start && (c == 'i' || c == 'u')) {
			state = State::suffix;
			type  = c == 'i' ? Type::i : Type::u;
			continue;
		} else if (state == State::floating_point && (c == 'f' || c == 'F')) {
			type = Type::f32;
			break;
		}

		switch (state) {
		case State::start: {
			if (c == '0') {
				state = State::zero_start;
			} else if (c >= '1' && c <= '9') {
				state = State::decimal;
			} else {
				goto gt_error;
			}
			break;
		}
		case State::suffix: {
			if (c == '8') {
				type = type == Type::i ? Type::i8 : Type::u8;
			} else if (c == '1') {
				if (param.reader.read() != '6') {
					goto gt_error;
				}
				type = type == Type::i ? Type::i16 : Type::u16;
			} else if (c == '3') {
				if (param.reader.read() != '2') {
					goto gt_error;
				}
				type = type == Type::i ? Type::i32 : Type::u32;
			} else if (c == '6') {
				if (param.reader.read() != '4') {
					goto gt_error;
				}
				type = type == Type::i ? Type::i64 : Type::u64;
			} else if (parse::is_spacing_character(c)) {
				goto gt_end;
			} else {
				goto gt_error;
			}
			old = param.reader.backup();
			goto gt_end;
		}
		case State::floating_point: {
			if (c >= '0' && c <= '9') {
				break;
			} else if (parse::is_spacing_character(c)) {
				goto gt_end;
			}
			goto gt_error;
		}
		case State::zero_start: {
			str.pop_back();
			if (c == 'x' || c == 'X') {
				state = State::hexadecimal;
				base  = 16;
				continue;
			} else if (c == 'b' || c == 'B') {
				state = State::binary;
				base  = 2;
				continue;
			} else if (c >= '0' && c <= '7') {
				state = State::octal;
				base  = 8;
				break;
			} else if (c == '.') {
				str.push_back('0');
				state = State::floating_point;
				type  = Type::f64;
				break;
			} else if (parse::is_spacing_character(c)) {
				str.push_back('0');
				goto gt_end;
			}
			goto gt_error;
		}
		case State::decimal: {
			if (c >= '0' && c <= '9') {
				break;
			} else if (c == '.') {
				state = State::floating_point;
				type  = Type::f64;
				break;
			} else if (parse::is_spacing_character(c)) {
				goto gt_end;
			}
			goto gt_error;
		}
		case State::hexadecimal: {
			if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) {
				break;
			} else if (parse::is_spacing_character(c)) {
				goto gt_end;
			}
			goto gt_error;
		}
		case State::octal: {
			if (c >= '0' && c <= '7') {
				break;
			} else if (parse::is_spacing_character(c)) {
				goto gt_end;
			}
			goto gt_error;
		}
		case State::binary: {
			if (c == '0' || c == '1') {
				break;
			} else if (parse::is_spacing_character(c)) {
				goto gt_end;
			}
			goto gt_error;
		}
		}
		str.push_back(c);
		continue;
	gt_end:
		param.reader.restore(old);
		break;
	}
	// error case
	if (str.empty() || (str.size() == 1 && (str.front() == '+' || str.front() == '-'))) {
	gt_error:
		// go until no space is available
		Parameter::State old;
		string::encoding::code_point_type cp;
		do {
			old = param.backup();
			cp  = param.reader.read();
		} while (cp != string::encoding::Encoder::eof && !parse::is_spacing_character(cp));
		param.restore(old);

		return { "", {}, 0, param.make_error(bia::error::Code::bad_number, ranger.range()) };
	}
	return { str, type, base, {} };
}

template<typename Type>
inline error::Code convert_integral(Type& value, const std::string& str, int base)
{
	using T               = typename std::decay<Type>::type;
	std::size_t processed = 0;
	if (std::is_unsigned<T>::value) {
		// must not be negative
		if (str.front() == '-') {
			return error::Code::unsigned_cannot_be_negative;
		}
		const auto real = std::stoull(str, &processed, base);
		if (real > std::numeric_limits<T>::max()) {
			return error::Code::number_overflow;
		}
		value = static_cast<T>(real);
	} else {
		const auto real = std::stoll(str, &processed, base);
		if (real > std::numeric_limits<T>::max()) {
			return error::Code::number_overflow;
		} else if (real < std::numeric_limits<T>::min()) {
			return error::Code::number_underflow;
		}
		value = static_cast<T>(real);
	}
	return error::Code::success;
}

inline Error_info convert(Parameter& param, const std::string& str, Token::Number::Type type, int base,
                          bia::tokenizer::Range range)
{
	using Type = Token::Number::Type;
	// convert
	std::size_t processed = 0;
	auto code             = error::Code::success;
	Token::Number num{};
	num.type = type;
	try {
		switch (type) {
		case Type::i: code = convert_integral(num.value.i, str, base); break;
		case Type::i8: code = convert_integral(num.value.i8, str, base); break;
		case Type::i16: code = convert_integral(num.value.i16, str, base); break;
		case Type::i32: code = convert_integral(num.value.i32, str, base); break;
		case Type::i64: code = convert_integral(num.value.i64, str, base); break;
		case Type::u: code = convert_integral(num.value.u, str, base); break;
		case Type::u8: code = convert_integral(num.value.u8, str, base); break;
		case Type::u16: code = convert_integral(num.value.u16, str, base); break;
		case Type::u32: code = convert_integral(num.value.u32, str, base); break;
		case Type::u64: code = convert_integral(num.value.u64, str, base); break;
		case Type::f32: num.value.f32 = std::stof(str, &processed); break;
		case Type::f64: num.value.f64 = std::stod(str, &processed); break;
		default: BIA_THROW(bia::error::Code::bad_switch_value);
		}
	} catch (const std::out_of_range& e) {
	} catch (const std::invalid_argument& e) {
	}

	if (code != error::Code::success) {
		return param.make_error(code, range);
	} else if ((type == Type::f32 || type == Type::f64) && processed != str.length()) {
		return param.make_error(bia::error::Code::bad_number, range);
	}
	param.bundle.emplace_back(num, range);
	return {};
}

Error_info parse::number(Parameter& param)
{
	const auto ranger    = param.begin_range();
	const auto extracted = extract_number(param);
	// check error
	if (std::get<3>(extracted)) {
		return std::get<3>(extracted);
	}
	return convert(param, std::get<0>(extracted), std::get<1>(extracted), std::get<2>(extracted),
	               ranger.range());
}
