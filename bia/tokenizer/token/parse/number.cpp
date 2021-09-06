#include "tokens.hpp"

#include <bia/error/exception.hpp>
#include <string>
#include <tuple>

using namespace bia;
using namespace bia::tokenizer::token;

inline std::tuple<std::string, Token::Number::Type, error::Bia> extract_number(Parameter& param)
{
	const auto ranger = param.begin_range();
	std::string str;
	while (true) {
		const auto state = param.reader.backup();
		const auto c     = param.reader.read();
		if (c < '0' || c > '9') {
			param.reader.restore(state);
			break;
		}
		str.append(1, c);
	}
	if (str.empty()) {
		return { str, Token::Number::Type::i, param.make_error(error::Code::bad_number, ranger.range()) };
	}
	return { str, Token::Number::Type::i, {} };
}

inline std::pair<Token::Number::Type, error::Bia> check_special(Parameter& param, Token::Number::Type type)
{
	// TODO
	return { type, {} };
}

inline error::Bia convert(Parameter& param, const std::string& str, Token::Number::Type type,
                          error::Bia_range range)
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

error::Bia parse::number(Parameter& param)
{
	const auto ranger    = param.begin_range();
	const auto extracted = extract_number(param);
	if (std::get<2>(extracted)) {
		return std::get<2>(extracted);
	}
	const auto special = check_special(param, std::get<1>(extracted));
	return special.second ? special.second
	                      : convert(param, std::get<0>(extracted), special.first, ranger.range());
}
