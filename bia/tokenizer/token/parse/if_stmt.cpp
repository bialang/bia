#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

Error_info parse::if_stmt(Parameter& param)
{
	if (!any_of(param, "if").second || spacer(param)) {
		return param.make_error(error::Code::expected_if);
	}
	param.bundle.emplace_back(Token::Keyword::if_);
	if (const auto err = single_expression(param)) {
		return err;
	}
	spacer(param);
	if (const auto err = batch(param)) {
		return err;
	}

	while (true) {
		const auto old = param.backup();
		spacer(param);
		if (else_if_stmt(param)) {
			param.restore(old);
			break;
		}
	}

	const auto old = param.backup();
	spacer(param);
	if (else_stmt(param)) {
		param.restore(old);
	}
	return {};
}

Error_info parse::else_if_stmt(Parameter& param)
{
	if (!any_of(param, "else").second || spacer(param) || !any_of(param, "if").second || spacer(param)) {
		return param.make_error(error::Code::expected_else_if);
	}
	param.bundle.emplace_back(Token::Keyword::else_if);
	if (const auto err = single_expression(param)) {
		return err;
	}
	spacer(param);
	if (const auto err = batch(param)) {
		return err;
	}
	return {};
}

Error_info parse::else_stmt(Parameter& param)
{
	if (!any_of(param, "else").second || spacer(param)) {
		return param.make_error(error::Code::expected_else);
	}
	param.bundle.emplace_back(Token::Keyword::else_);
	if (const auto err = batch(param)) {
		return err;
	}
	return {};
}
