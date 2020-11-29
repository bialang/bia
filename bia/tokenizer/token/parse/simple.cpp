#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

error_info parse::return_stmt(parameter& param)
{
	if (!any_of(param, "return").second) {
		return param.make_error(error::code::expected_return);
	}
	param.bundle.emplace_back(token::keyword::return_);
	spacer(param);
	return multi_expression(param);
}

error_info parse::yield_stmt(parameter& param)
{
	if (!any_of(param, "yield").second) {
		return param.make_error(error::code::expected_yield);
	}
	param.bundle.emplace_back(token::keyword::yield);
	spacer(param);
	return multi_expression(param);
}

error_info parse::defer_stmt(parameter& param)
{
	if (!any_of(param, "defer").second) {
		return param.make_error(error::code::expected_yield);
	}
	param.bundle.emplace_back(token::keyword::defer);
	spacer(param);
	return any_of(param, single_expression, batch);
}
