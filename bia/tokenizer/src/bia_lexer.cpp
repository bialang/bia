#include "tokenizer/bia_lexer.hpp"

#include "tokenizer/token/statement.hpp"

#include <exception/syntax_error.hpp>

namespace bia {
namespace tokenizer {

bia_lexer::bia_lexer(util::not_null<std::shared_ptr<gc::memory_allocator>> allocator)
    : _resource_manager(std::move(allocator), 4096)
{}

void bia_lexer::lex(util::byte_istream_type& input, string::encoding::encoder& encoder,
                    token_receiver& receiver)
{
	token::token_parameter token_parameter{ input, _resource_manager, encoder };
	auto state = token_parameter.backup();

	// match single statements
	if (auto err = token::single_stmt(token_parameter)) {
		BIA_THROW(exception::syntax_error, "syntax error", err);
	}
}

} // namespace tokenizer
} // namespace bia