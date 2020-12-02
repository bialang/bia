#include "tokens.hpp"

#include <bia/error/exception.hpp>
#include <string>
#include <tuple>

using namespace bia::tokenizer::token;

inline std::tuple<std::string, enum token::number::type, error_info> extract_number(parameter& param)
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
	return { str, token::number::type::i, {} };
}

inline std::pair<enum token::number::type, error_info> check_special(parameter& param,
                                                                     enum token::number::type type)
{
	// TODO
	return { type, {} };
}

inline error_info convert(parameter& param, const std::string& str, enum token::number::type type)
{
	using number = token::number;
	// convert
	std::size_t processed = 0;
	number num{};
	num.type = type;
	try {
		switch (num.type) {
		case number::type::f32: num.value.f32 = std::stof(str, &processed); break;
		case number::type::f64: num.value.f64 = std::stod(str, &processed); break;
		default: BIA_THROW(bia::error::code::bad_switch_value);
		}
	} catch (const std::out_of_range& e) {
	} catch (const std::invalid_argument& e) {
	}

	if (processed != str.length()) {
	}
	param.bundle.emplace_back(num);
	return {};
}

error_info parse::number(parameter& param)
{
	const auto extracted = extract_number(param);
	if (std::get<2>(extracted)) {
		return std::get<2>(extracted);
	}
	const auto special = check_special(param, std::get<1>(extracted));
	return special.second ? special.second : convert(param, std::get<0>(extracted), special.first);
}
