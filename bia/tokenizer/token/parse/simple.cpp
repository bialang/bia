#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

Error_info parse::return_stmt(parameter& param)
{
	if (!any_of(param, "return").second || spacer(param)) {
		return param.make_error(error::Code::expected_return);
	}
	param.bundle.emplace_back(Token::keyword::return_);
	return multi_expression(param);
}

Error_info parse::yield_stmt(parameter& param)
{
	if (!any_of(param, "yield").second || spacer(param)) {
		return param.make_error(error::Code::expected_yield);
	}
	param.bundle.emplace_back(Token::keyword::yield);
	return multi_expression(param);
}

Error_info parse::import_stmt(parameter& param)
{
	if (!any_of(param, "import").second || spacer(param)) {
		return param.make_error(error::Code::expected_yield);
	}
	param.bundle.emplace_back(Token::keyword::import);
	return string(param);
}

Error_info parse::flow_control_stmt(parameter& param)
{
	const auto x = any_of(param, "break", "continue");
	if (!x.second || spacer(param)) {
		return param.make_error(error::Code::expected_yield);
	}
	param.bundle.emplace_back(x.first == 1 ? Token::keyword::break_ : Token::keyword::continue_);

	const auto old = param.backup();
	if (identifier(param)) {
		param.restore(old);
	}
	return {};
}

Error_info parse::defer_stmt(parameter& param)
{
	if (!any_of(param, "defer").second || spacer(param)) {
		return param.make_error(error::Code::expected_yield);
	}
	param.bundle.emplace_back(Token::keyword::defer);
	return any_of(param, single_expression, batch);
}
