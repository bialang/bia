#include "tokenizer/bia_lexer.hpp"
#include "tokenizer/token/statement.hpp"

#include <exception/syntax_error.hpp>

namespace bia {
namespace tokenizer {

void bia_lexer::lex(std::istream& input, string::encoding::encoder& encoder, token_receiver& receiver) const
{
	token::token_parameter token_parameter{input, _resource_manager, encoder};
	auto state = token_parameter.backup();

	// match single statements
	if (auto err = token::single_stmt(token_parameter)) {
		BIA_THROW(exception::syntax_error, "syntax error", err);
	}

}

} // namespace tokenizer
} // namespace bia