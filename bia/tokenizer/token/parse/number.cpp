#include "tokens.hpp"

#include <bia/error/exception.hpp>
#include <limits>
#include <string>
#include <tuple>
#include <type_traits>

using namespace bia;
using namespace bia::tokenizer::token;

/// Extracts the string from the code which can be parsed by one of the standard conversion functions. Returns
/// the number string, it's desired type and an error.
inline std::tuple<std::string, Token::Number::Type, Error_info> extract_number(Parameter& param)
{
	using Type        = Token::Number::Type;
	const auto ranger = param.begin_range();
	std::string str;
	Type type = Type::i;
	while (true) {
		const auto state = param.reader.backup();
		const auto c     = param.reader.read();
		if ((type != Type::f32 || type != Type::f64) && c == '.') {
			type = Type::f64;
		} else if (type == Type::f64 && (c == 'f' || c == 'F')) {
			type = Type::f32;
		} else if (c < '0' || c > '9') {
			param.reader.restore(state);
			break;
		}
		str.append(1, c);
	}
	if (str.empty()) {
		return { "", Type::i, param.make_error(bia::error::Code::bad_number, ranger.range()) };
	}
	return { str, type, {} };
}

template<typename Type>
inline error::Code convert_integral(Type& value, const std::string& str)
{
	using T               = typename std::decay<Type>::type;
	std::size_t processed = 0;
	if (std::is_unsigned<T>::value) {
		const auto real = std::stoull(str, &processed);
		if (real > std::numeric_limits<T>::max()) {
			return error::Code::number_overflow;
		}
		value = static_cast<T>(real);
	} else {
		const auto real = std::stoll(str, &processed);
		if (real > std::numeric_limits<T>::max()) {
			return error::Code::number_overflow;
		} else if (real < std::numeric_limits<T>::min()) {
			return error::Code::number_underflow;
		}
		value = static_cast<T>(real);
	}
	return error::Code::success;
}

inline Error_info convert(Parameter& param, const std::string& str, Token::Number::Type type,
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
		case Type::i: code = convert_integral(num.value.i, str); break;
		case Type::i8: code = convert_integral(num.value.i8, str); break;
		case Type::i16: code = convert_integral(num.value.i16, str); break;
		case Type::i32: code = convert_integral(num.value.i32, str); break;
		case Type::i64: code = convert_integral(num.value.i64, str); break;
		case Type::u: code = convert_integral(num.value.u, str); break;
		case Type::u8: code = convert_integral(num.value.u8, str); break;
		case Type::u16: code = convert_integral(num.value.u16, str); break;
		case Type::u32: code = convert_integral(num.value.u32, str); break;
		case Type::u64: code = convert_integral(num.value.u64, str); break;
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
	if (std::get<2>(extracted)) {
		return std::get<2>(extracted);
	}
	return convert(param, std::get<0>(extracted), std::get<1>(extracted), ranger.range());
}
