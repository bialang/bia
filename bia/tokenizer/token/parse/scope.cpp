#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

Error_info parse::scope_stmt(Parameter& param)
{
	const auto ranger = param.begin_range();
	if (!any_of(param, "scope").second) {
		return param.make_error(error::Code::expected_scope, ranger.range());
	}
	param.bundle.emplace_back(Token::Keyword::scope, ranger.range());
	spacer(param);
	return batch(param);
}
