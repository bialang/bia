#include "any_of.hpp"
#include "tokens.hpp"

#include <bia/util/finally.hpp>
#include <limits>

using namespace bia;
using namespace bia::tokenizer::token;

inline error::Bia operators(Parameter& param)
{
	constexpr Operator ops[] = { Operator::logical_and,
		                           Operator::logical_or,
		                           Operator::in,
		                           Operator::member_access,
		                           Operator::exponentation,
		                           Operator::multiply,
		                           Operator::divide,
		                           Operator::modulus,
		                           Operator::plus,
		                           Operator::minus,
		                           Operator::equal,
		                           Operator::not_equal,
		                           Operator::three_way_comparison,
		                           Operator::less_equal,
		                           Operator::greater_equal,
		                           Operator::less,
		                           Operator::greater,
		                           Operator::assign,
		                           Operator::bitwise_and,
		                           Operator::bitwise_or,
		                           Operator::bitwise_xor };
	const auto ranger        = param.begin_range();
	const auto x             = parse::any_of(param, "and", "or", "in", ".", "**", "*", "/", "%", "+", "-",
	                                         "==", "!=", "<=>", "<=", ">=", "<", ">", "=", "&", "|", "^");

	if (!x.second || (x.first < 3 && parse::spacer(param))) {
		return param.make_error(bia::error::Code::bad_operator, ranger.range());
	}
	param.bundle.emplace_back(static_cast<Operator>(ops[x.first]), ranger.range());
	return {};
}

inline error::Bia self_operator(Parameter& param)
{
	const auto ranger = param.begin_range();
	const auto x      = parse::any_of(param, "not");
	if (!x.second || parse::spacer(param)) {
		return param.make_error(bia::error::Code::bad_operator, ranger.range());
	}
	param.bundle.emplace_back(Operator::logical_not, ranger.range());
	return {};
}

inline error::Bia constant_keyword(Parameter& param)
{
	const auto ranger = param.begin_range();
	const auto tmp    = parse::any_of(param, "true", "false", "null", "infinity", "nan");
	const auto range  = ranger.range();
	if (tmp.second && !parse::spacer(param)) {
		switch (tmp.first) {
		case 0: param.bundle.emplace_back(Token::Keyword::true_, range); break;
		case 1: param.bundle.emplace_back(Token::Keyword::false_, range); break;
		case 2: param.bundle.emplace_back(Token::Keyword::null, range); break;
		case 3: {
			static_assert(std::numeric_limits<double>::has_infinity, "Floating point infinity not supported");
			Token::Number number{};
			number.type      = Token::Number::Type::f64;
			number.value.f64 = std::numeric_limits<double>::infinity();
			param.bundle.emplace_back(number, range);
			break;
		}
		case 4: {
			static_assert(std::numeric_limits<double>::has_quiet_NaN, "Floating point NaN not supported");
			Token::Number number{};
			number.type      = Token::Number::Type::f64;
			number.value.f64 = std::numeric_limits<double>::quiet_NaN();
			param.bundle.emplace_back(number, range);
			break;
		}
		default: BIA_THROW(bia::error::Code::bad_switch_value);
		}
		return {};
	}
	return param.make_error(bia::error::Code::bad_constant_keyword, ranger.range());
}

error::Bia single_expression_impl(Parameter& param);

inline error::Bia single_expression_in_brackets(Parameter& param)
{
	auto ranger = param.begin_range();
	if (param.reader.read() != '(') {
		return param.make_error(bia::error::Code::expected_opening_bracket, ranger.range());
	}
	param.bundle.emplace_back(Token::Control::bracket_open, ranger.range());
	parse::spacer(param);
	if (const auto err = single_expression_impl(param)) {
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

error::Bia parse::value(Parameter& param)
{
	return any_of(param, number, constant_keyword, regex, string, identifier, single_expression_in_brackets);
}

inline error::Bia use_value(Parameter& param)
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

inline error::Bia expression_value(Parameter& param)
{
	return parse::any_of(param, parse::value, use_value);
}

error::Bia parse::multi_expression(Parameter& param)
{
	return single_expression(param);
}

inline error::Bia single_expression_impl(Parameter& param)
{
	using namespace parse;

	auto old = param.backup();
	if (self_operator(param)) {
		param.restore(old);
	}

	if (const auto err = expression_value(param)) {
		return err;
	}

	// member operations
	while (true) {
		old = param.backup();
		spacer(param);
		const auto result = any_of(param, member_access, member_invocation);
		if (result) {
			param.restore(old);
			break;
		}
	}

	// operator chains
	while (true) {
		const auto old = param.backup();
		spacer(param);
		if (operators(param)) {
			param.restore(old);
			break;
		}
		spacer(param);
		if (const auto err = single_expression_impl(param)) {
			return err;
		}
	}

	return {};
}

error::Bia parse::single_expression(Parameter& param)
{
	const std::size_t sequence_index = param.bundle.size();
	const auto ranger                = param.begin_range();
	param.bundle.emplace_back();
	const auto _ = util::finallay([&] {
		param.bundle[sequence_index] = { Token::Sequence{
			                                 Token::Sequence::Type::single_expression,
			                                 param.bundle.size() - sequence_index - 1,
			                               },
			                               ranger.range() };
	});
	return single_expression_impl(param);
}
