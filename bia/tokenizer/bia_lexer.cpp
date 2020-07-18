#include "bia_lexer.hpp"

#include "token/bundle.hpp"
#include "token/parse/tokens.hpp"
#include "token/parse/whitespace_eater.hpp"

#include <bia/exception/syntax_error.hpp>

namespace bia {
namespace tokenizer {

bia_lexer::bia_lexer(util::not_null<std::shared_ptr<gc::memory::allocator>> allocator)
    : _manager(std::move(allocator), 4096)
{}

void bia_lexer::lex(util::byte_istream_type& input, string::encoding::encoder& encoder,
                    token::receiver& receiver)
{
	token::bundle bundle;
	token::parameter parameter{ input, _manager, encoder, bundle };

	while (!(input.peek(), input.eof())) {
		token::parse::eat_whitespaces(parameter);

		// match single statements
		if (const auto err = token::parse::single_stmt(parameter)) {
			BIA_THROW(exception::syntax_error, "syntax error", err);
		}

		if (const auto err = token::parse::cmd_end(parameter)) {
			BIA_THROW(exception::syntax_error, "syntax error", err);
		}

		// give to receiver
		receiver.receive({ bundle.begin(), bundle.end() });
		bundle.clear();
	}
}

} // namespace tokenizer
} // namespace bia
