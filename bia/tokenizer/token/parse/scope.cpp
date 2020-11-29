#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

error_info parse::scope_stmt(parameter& param)
{
	if (!any_of(param, "scoped").second) {
		return param.make_error(error::code::expected_scope);
	}
	param.bundle.emplace_back(token::keyword::scoped);
	spacer(param);
	return batch(param);
}
