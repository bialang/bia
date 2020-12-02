#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

inline error_info operators(parameter& param)
{
	constexpr operator_ ops[] = { operator_::member_access,  operator_::exponentation,
		                          operator_::multiplication, operator_::division,
		                          operator_::remainder,      operator_::addition,
		                          operator_::subtraction,    operator_::equal,
		                          operator_::not_equal,      operator_::three_way_comparison,
		                          operator_::less_equal,     operator_::greater_equal,
		                          operator_::less,           operator_::greater,
		                          operator_::assign,         operator_::logical_and,
		                          operator_::logical_and,    operator_::logical_or,
		                          operator_::logical_or,     operator_::in,
		                          operator_::bitwise_and,    operator_::bitwise_or,
		                          operator_::bitwise_xor };
	const auto x              = parse::any_of(param, ".", "**", "*", "/", "%", "+", "-", "==", "!=", "<=>",
                                 "<=", ">=", "<", ">", "=", "and", "&&", "or", "||", "in", "&", "|", "^");

	if (!x.second) {
		return param.make_error(bia::error::code::bad_operator);
	}
	param.bundle.emplace_back(static_cast<operator_>(ops[x.first]));
	return {};
}

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
	return any_of(param, number, constant_keyword, string, identifier);
}

inline error_info expression_value(parameter& param)
{
	const auto use = static_cast<parse::token_type>([](parameter& param) -> error_info {
		if (param.encoder.read(param.input) != '(') {
		}
		parse::spacer(param);
		if (!parse::any_of(param, "use").second || !parse::spacer(param)) {
			return param.make_error(bia::error::code::expected_use, -1);
		}
		param.bundle.emplace_back(token::keyword::use);
		if (const auto err = parse::value(param)) {
			return err;
		}
		parse::spacer(param);
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
