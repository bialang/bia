#include "tokens.hpp"

#include <bia/error/exception.hpp>
#include <string>
#include <tuple>

using namespace bia::tokenizer::token;

inline std::tuple<std::string, enum Token::number::type, Error_info> extract_number(parameter& param)
{
	std::string str;
	while (true) {
		const auto pos = param.input.tellg();
		const auto c   = param.encoder.read(param.input);
		if (c < '0' || c > '9') {
			param.input.seekg(pos);
			break;
		}
		str.append(1, c);
	}
	if (str.empty()) {
		return { str, Token::number::type::i, param.make_error(bia::error::Code::bad_number) };
	}
	return { str, Token::number::type::i, {} };
}

inline std::pair<enum Token::number::type, Error_info> check_special(parameter& param,
                                                                     enum Token::number::type type)
{
	// TODO
	return { type, {} };
}

inline Error_info convert(parameter& param, const std::string& str, enum Token::number::type type)
{
	using number = Token::number;
	// convert
	std::size_t processed = 0;
	number num{};
	num.type = type;
	try {
		switch (num.type) {
		case number::type::i: num.value.i = std::stoi(str, &processed); break;
		case number::type::f32: num.value.f32 = std::stof(str, &processed); break;
		case number::type::f64: num.value.f64 = std::stod(str, &processed); break;
		default: BIA_THROW(bia::error::Code::bad_switch_value);
		}
	} catch (const std::out_of_range& e) {
	} catch (const std::invalid_argument& e) {
	}

	if (processed != str.length()) {
		return param.make_error(bia::error::Code::bad_number);
	}
	param.bundle.emplace_back(num);
	return {};
}

Error_info parse::number(parameter& param)
{
	const auto extracted = extract_number(param);
	if (std::get<2>(extracted)) {
		return std::get<2>(extracted);
	}
	const auto special = check_special(param, std::get<1>(extracted));
	return special.second ? special.second : convert(param, std::get<0>(extracted), special.first);
}
