#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

inline Error_info operators(Parameter& param)
{
	constexpr Operator ops[] = { Operator::member_access, Operator::exponentation,
		                           Operator::multiply,      Operator::divide,
		                           Operator::modulus,       Operator::plus,
		                           Operator::minus,         Operator::equal,
		                           Operator::not_equal,     Operator::three_way_comparison,
		                           Operator::less_equal,    Operator::greater_equal,
		                           Operator::less,          Operator::greater,
		                           Operator::assign,        Operator::logical_and,
		                           Operator::logical_and,   Operator::logical_or,
		                           Operator::logical_or,    Operator::in,
		                           Operator::bitwise_and,   Operator::bitwise_or,
		                           Operator::bitwise_xor };
	const auto ranger        = param.begin_range();
	const auto x = parse::any_of(param, ".", "**", "*", "/", "%", "+", "-", "==", "!=", "<=>", "<=", ">=", "<",
	                             ">", "=", "and", "&&", "or", "||", "in", "&", "|", "^");

	if (!x.second) {
		return param.make_error(bia::error::Code::bad_operator, ranger.range());
	}
	param.bundle.emplace_back(static_cast<Operator>(ops[x.first]), ranger.range());
	return {};
}

inline Error_info constant_keyword(Parameter& param)
{
	const auto ranger = param.begin_range();
	const auto tmp    = parse::any_of(param, "true", "false", "null");
	const auto range  = ranger.range();
	if (tmp.second && !parse::spacer(param)) {
		switch (tmp.first) {
		case 0: param.bundle.emplace_back(Token::Keyword::true_, range); break;
		case 1: param.bundle.emplace_back(Token::Keyword::false_, range); break;
		case 2: param.bundle.emplace_back(Token::Keyword::null, range); break;
		default: BIA_THROW(bia::error::Code::bad_switch_value);
		}
		return {};
	}
	return param.make_error(bia::error::Code::bad_constant_keyword, ranger.range());
}

inline Error_info single_expression_in_brackets(Parameter& param)
{
	auto ranger = param.begin_range();
	if (param.reader.read() != '(') {
		return param.make_error(bia::error::Code::expected_opening_bracket, ranger.range());
	}
	param.bundle.emplace_back(Token::Control::bracket_open, ranger.range());
	parse::spacer(param);
	if (const auto err = parse::single_expression(param)) {
		return err;
	}
	parse::spacer(param);
	ranger = param.begin_range();
	if (param.reader.read() != ')') {
		return param.make_error(bia::error::Code::expected_closing_bracket, ranger.range());
	}
	param.bundle.emplace_back(Token::Control::bracket_close, ranger.range());
	return {};
}

Error_info parse::value(Parameter& param)
{
	return any_of(param, number, constant_keyword, regex, string, identifier, single_expression_in_brackets);
}

inline Error_info use_value(Parameter& param)
{
	auto ranger = param.begin_range();
	if (param.reader.read() != '(') {
		return param.make_error(bia::error::Code::expected_use, ranger.range());
	}
	parse::spacer(param);
	ranger = param.begin_range();
	if (!parse::any_of(param, "use").second || parse::spacer(param)) {
		return param.make_error(bia::error::Code::expected_use, ranger.range());
	}
	param.bundle.emplace_back(Token::Keyword::use, ranger.range());
	if (const auto err = parse::value(param)) {
		return err;
	}
	parse::spacer(param);
	ranger = param.begin_range();
	if (param.reader.read() != ')') {
		return param.make_error(bia::error::Code::expected_use, ranger.range());
	}
	return {};
}

inline Error_info expression_value(Parameter& param)
{
	return parse::any_of(param, parse::value, use_value);
}

Error_info parse::multi_expression(Parameter& param)
{
	return single_expression(param);
}

Error_info parse::single_expression(Parameter& param)
{
	if (const auto err = expression_value(param)) {
		return err;
	}

	// operator chains
	while (true) {
		const auto old = param.backup();
		spacer(param);
		if (operators(param)) {
			param.restore(old);
			return {};
		}
		spacer(param);
		if (const auto err = expression_value(param)) {
			return err;
		}
	}
}
