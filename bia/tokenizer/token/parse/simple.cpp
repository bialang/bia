#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

Error_info parse::return_stmt(Parameter& param)
{
	if (!any_of(param, "return").second || spacer(param)) {
		return param.make_error(error::Code::expected_return);
	}
	param.bundle.emplace_back(Token::Keyword::return_);
	return multi_expression(param);
}

Error_info parse::yield_stmt(Parameter& param)
{
	if (!any_of(param, "yield").second || spacer(param)) {
		return param.make_error(error::Code::expected_yield);
	}
	param.bundle.emplace_back(Token::Keyword::yield);
	return multi_expression(param);
}

Error_info parse::import_stmt(Parameter& param)
{
	if (!any_of(param, "import").second || spacer(param)) {
		return param.make_error(error::Code::expected_yield);
	}
	param.bundle.emplace_back(Token::Keyword::import);
	return string(param);
}

Error_info parse::flow_control_stmt(Parameter& param)
{
	const auto x = any_of(param, "break", "continue");
	if (!x.second || spacer(param)) {
		return param.make_error(error::Code::expected_yield);
	}
	param.bundle.emplace_back(x.first == 1 ? Token::Keyword::break_ : Token::Keyword::continue_);

	const auto old = param.backup();
	if (identifier(param)) {
		param.restore(old);
	}
	return {};
}

Error_info parse::defer_stmt(Parameter& param)
{
	if (!any_of(param, "defer").second || spacer(param)) {
		return param.make_error(error::Code::expected_yield);
	}
	param.bundle.emplace_back(Token::Keyword::defer);
	return any_of(param, single_expression, batch);
}
