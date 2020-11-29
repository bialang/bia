#include "any_of.hpp"
#include "tokens.hpp"
#include "whitespace_eater.hpp"

using namespace bia::tokenizer::token;

error_info parse::value(parameter& param)
{
	const auto constant_keyword = static_cast<error_info (*)(parameter&)>([](parameter& param) -> error_info {
		const auto tmp = any_of(param, "true", "false", "null");
		if (tmp.second) {
			switch (tmp.first) {
			case 0: param.bundle.emplace_back(token::keyword::true_); break;
			case 1: param.bundle.emplace_back(token::keyword::false_); break;
			case 2: param.bundle.emplace_back(token::keyword::null); break;
			default: BIA_THROW(error::code::bad_switch_value);
			}
			return {};
		}
		return param.make_error(error::code::bad_constant_keyword);
	});
	return any_of(param, number, constant_keyword, member);
}

inline error_info expression_value(parameter& param)
{
	const auto use = static_cast<parse::token_type>([](parameter& param) -> error_info {
		if (param.encoder.read(param.input) != '(') {
		}
		parse::eat_whitespaces(param);
		if (!parse::any_of(param, "use").second) {
			return param.make_error(bia::error::code::expected_use, -1);
		}
		param.bundle.emplace_back(token::keyword::use);
		if (const auto err = parse::eat_whitespaces(param)) {
			return err;
		}
		if (const auto err = parse::value(param)) {
			return err;
		}
		parse::eat_whitespaces(param);
		if (param.encoder.read(param.input) != ')') {
		}
		return {};
	});
	return parse::any_of(param, parse::value, use);
}

error_info parse::multi_expression(parameter& param)
{
	return single_expression(param);
}

error_info parse::single_expression(parameter& param)
{
	return expression_value(param);
}
