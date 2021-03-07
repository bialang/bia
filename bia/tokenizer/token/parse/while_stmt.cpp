#include "any_of.hpp"
#include "tokens.hpp"

using namespace bia::tokenizer::token;

Error_info parse::while_stmt(Parameter& param)
{
	const auto ranger = param.begin_range();
	if (!any_of(param, "while").second || spacer(param)) {
		return param.make_error(error::Code::expected_while_statement, ranger.range());
	}
	param.bundle.emplace_back(Token::Keyword::while_, ranger.range());
	if (const auto err = single_expression(param)) {
		return err;
	}
	spacer(param);
	return batch(param);
}
