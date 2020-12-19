#include "bia_lexer.hpp"

#include "token/parse/tokens.hpp"

#include <bia/error/exception.hpp>
#include <vector>

namespace bia {
namespace tokenizer {

bia_lexer::bia_lexer(util::not_null<std::shared_ptr<gc::memory::allocator>> allocator)
    : _manager(std::move(allocator), 4096)
{}

void bia_lexer::lex(util::byte_istream_type& input, string::encoding::encoder& encoder,
                    token::receiver& receiver)
{
	std::vector<token::token> bundle;
	token::parameter param{ input, _manager, encoder, bundle };

	while (!(input.peek(), input.eof())) {
		token::parse::spacer(param);

		// match single statements
		if (const auto err = token::parse::root(param)) {
		}

		// give to receiver
		receiver.receive({ bundle.data(), bundle.size() }, _manager);
		bundle.clear();
	}
}

} // namespace tokenizer
} // namespace bia
