#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

error_info parse::return_stmt(parameter& param)
{
	if (!any_of(param, "return").second || spacer(param)) {
		return param.make_error(error::code::expected_return);
	}
	param.bundle.emplace_back(token::keyword::return_);
	return multi_expression(param);
}

error_info parse::yield_stmt(parameter& param)
{
	if (!any_of(param, "yield").second || spacer(param)) {
		return param.make_error(error::code::expected_yield);
	}
	param.bundle.emplace_back(token::keyword::yield);
	return multi_expression(param);
}

error_info parse::import_stmt(parameter& param)
{
	if (!any_of(param, "import").second || spacer(param)) {
		return param.make_error(error::code::expected_yield);
	}
	param.bundle.emplace_back(token::keyword::import);
	return string(param);
}

error_info parse::flow_control_stmt(parameter& param)
{
	const auto x = any_of(param, "break", "continue");
	if (!x.second || spacer(param)) {
		return param.make_error(error::code::expected_yield);
	}
	param.bundle.emplace_back(x.first == 1 ? token::keyword::break_ : token::keyword::continue_);

	const auto old = param.backup();
	if (identifier(param)) {
		param.restore(old);
	}
	return {};
}

error_info parse::defer_stmt(parameter& param)
{
	if (!any_of(param, "defer").second || spacer(param)) {
		return param.make_error(error::code::expected_yield);
	}
	param.bundle.emplace_back(token::keyword::defer);
	return any_of(param, single_expression, batch);
}
