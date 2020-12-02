#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

error_info parse::if_stmt(parameter& param)
{
	if (!any_of(param, "if").second || !spacer(param)) {
		return param.make_error(error::code::expected_if);
	}
	if (const auto err = single_expression(param)) {
		return err;
	}
	if (const auto err = batch(param)) {
		return err;
	}

	while (true) {
		const auto old = param.backup();
		if (else_if_stmt(param)) {
			param.restore(old);
			break;
		}
	}

	const auto old = param.backup();
	if (else_stmt(param)) {
		param.restore(old);
	}
	return {};
}

error_info parse::else_if_stmt(parameter& param)
{
	if (!any_of(param, "else").second || !spacer(param)) {
		return param.make_error(error::code::expected_else_if);
	}
	if (!any_of(param, "if").second || !spacer(param)) {
		return param.make_error(error::code::expected_else_if);
	}
	if (const auto err = single_expression(param)) {
		return err;
	}
	if (const auto err = batch(param)) {
		return err;
	}
	return {};
}

error_info parse::else_stmt(parameter& param)
{
	if (!any_of(param, "else").second || !spacer(param)) {
		return param.make_error(error::code::expected_else);
	}
	if (const auto err = batch(param)) {
		return err;
	}
	return {};
}
