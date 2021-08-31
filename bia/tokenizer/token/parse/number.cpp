#include "tokens.hpp"

#include <bia/error/exception.hpp>
#include <string>
#include <tuple>

using namespace bia::tokenizer::token;

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

inline std::pair<Token::Number::Type, Error_info> check_special(Parameter& param, Token::Number::Type type)
{
	// TODO
	return { type, {} };
}

inline Error_info convert(Parameter& param, const std::string& str, Token::Number::Type type,
                          bia::tokenizer::Range range)
{
	using Number = Token::Number;
	// convert
	std::size_t processed = 0;
	Number num{};
	num.type = type;
	try {
		switch (num.type) {
		case Number::Type::i: num.value.i = std::stoll(str, &processed); break;
		case Number::Type::f32: num.value.f32 = std::stof(str, &processed); break;
		case Number::Type::f64: num.value.f64 = std::stod(str, &processed); break;
		default: BIA_THROW(bia::error::Code::bad_switch_value);
		}
	} catch (const std::out_of_range& e) {
	} catch (const std::invalid_argument& e) {
	}

	if (processed != str.length()) {
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
	const auto special = check_special(param, std::get<1>(extracted));
	return special.second ? special.second
	                      : convert(param, std::get<0>(extracted), special.first, ranger.range());
}
