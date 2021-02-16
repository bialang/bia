#include "bia_lexer.hpp"

#include "token/parse/tokens.hpp"

#include <bia/error/exception.hpp>
#include <vector>

namespace bia {
namespace tokenizer {

Bia_lexer::Bia_lexer(util::Not_null<std::shared_ptr<gc::memory::Allocator>> allocator)
    : _manager(std::move(allocator), 4096)
{}

void Bia_lexer::lex(Reader& reader, token::Receiver& receiver)
{
	std::vector<token::Token> bundle;
	token::Parameter param{ reader, _manager, bundle };

	while (!reader.eof()) {
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
