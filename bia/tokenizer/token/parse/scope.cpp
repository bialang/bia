#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

Error_info parse::scope_stmt(Parameter& param)
{
	if (!any_of(param, "scoped").second) {
		return param.make_error(error::Code::expected_scope);
	}
	param.bundle.emplace_back(Token::Keyword::scoped);
	spacer(param);
	return batch(param);
}
