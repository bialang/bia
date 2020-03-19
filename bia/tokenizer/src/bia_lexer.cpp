#include "tokenizer/bia_lexer.hpp"

#include "tokenizer/token/bundle.hpp"
#include "tokenizer/token/parse/statement.hpp"

#include <exception/syntax_error.hpp>

namespace bia {
namespace tokenizer {

bia_lexer::bia_lexer(util::not_null<std::shared_ptr<gc::memory_allocator>> allocator)
    : _manager(std::move(allocator), 4096)
{}

void bia_lexer::lex(util::byte_istream_type& input, string::encoding::encoder& encoder,
                    token::receiver& receiver)
{
	token::bundle bundle;
	token::parameter parameter{ input, _manager, encoder, bundle };
	auto state = parameter.backup();

	// match single statements
	if (auto err = token::parse::single_stmt(parameter)) {
		BIA_THROW(exception::syntax_error, "syntax error", err);
	}

	// add cmd_end token; make sure its a token
	bundle.add(token::token{ token::token::cmd_end{} });

	// give to receiver
	receiver.receive(bundle.begin(), bundle.end());
}

} // namespace tokenizer
} // namespace bia