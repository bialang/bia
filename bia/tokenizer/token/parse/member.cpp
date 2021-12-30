#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia;
using namespace bia::tokenizer::token;

error::Bia parse::member_access(Parameter& param)
{
	const auto ranger = param.begin_range();
	auto cp           = param.reader.read();
	auto nullable     = false;
	if (cp == '?') {
		nullable = true;
		cp       = param.reader.read();
	}
	if (cp != '.') {
		return param.make_error(error::Code::expected_member_access, ranger.range());
	}
	param.bundle.emplace_back(nullable ? Operator::nullable_member_access : Operator::member_access,
	                          ranger.range());
	return parse::identifier(param);
}

inline error::Bia argument_list(Parameter& param)
{
	Parameter::State old;

	// positionals
	for (bool first = true, doing_positionals = true; true; first = false) {
		old = param.backup();
		// read comma
		if (!first) {
			parse::spacer(param);
			const auto ranger = param.begin_range();
			if (param.reader.read() != ',') {
				break;
			}
			param.bundle.emplace_back(Token::Control::comma, ranger.range());
			parse::spacer(param);
		}

		// try named
		{
			const auto tmp = param.backup();
			if (const auto err = parse::identifier(param)) {
				if (!doing_positionals) {
					return err;
				}
				param.restore(tmp);
				goto gt_not_named;
			}

			parse::spacer(param);
			const auto ranger = param.begin_range();
			if (param.reader.read() != '=') {
				if (!doing_positionals) {
					return param.make_error(error::Code::expected_assignment, ranger.range());
				}
				param.restore(tmp);
				goto gt_not_named;
			}
			parse::spacer(param);
			doing_positionals = false;
		}

	gt_not_named:
		if (const auto err = parse::single_expression(param)) {
			break;
		}
	}
	param.restore(old);
	return {};
}

error::Bia parse::member_invocation(Parameter& param)
{
	auto ranger = param.begin_range();
	if (param.reader.read() != '(') {
		return param.make_error(error::Code::expected_opening_bracket, ranger.range());
	}
	param.bundle.emplace_back(Operator::function_call_open, ranger.range());
	spacer(param);
	if (const auto err = argument_list(param)) {
		return err;
	}
	spacer(param);
	ranger = param.begin_range();
	if (param.reader.read() != ')') {
		return param.make_error(error::Code::expected_opening_bracket, ranger.range());
	}
	param.bundle.emplace_back(Operator::function_call_close, ranger.range());
	return {};
}

error::Bia parse::member_subscript(Parameter& param)
{
	return param.make_error(error::Code::expected_member_access, param.begin_range().range());
}
