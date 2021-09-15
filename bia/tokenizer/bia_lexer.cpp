#include "bia_lexer.hpp"

#include "token/parse/tokens.hpp"

#include <bia/error/exception.hpp>
#include <bia/log/log.hpp>
#include <vector>

namespace bia {
namespace tokenizer {

Bia_lexer::Bia_lexer(util::Not_null<std::shared_ptr<memory::Allocator>> allocator)
    : _manager{ std::move(allocator), 4096 }
{}

error::Bia Bia_lexer::lex(Reader& reader, token::Receiver& receiver)
{
	std::vector<token::Token> bundle;
	token::Parameter param{ reader, _manager, bundle };

	for (token::parse::spacer(param); !reader.eof(); token::parse::spacer(param)) {
		// match single statements
		if (const auto err = token::parse::root(param)) {
			// return err;
		}

		// nothing matched
		if (bundle.empty() && !reader.eof()) {
			BIA_LOG(ERROR, "Bundle is empty. Nothing could be parsed");
			// TODO add error
			return {};
		}

		// give to receiver
		receiver.receive({ bundle.data(), bundle.size() }, _manager);
		bundle.clear();
	}
	return {};
}

} // namespace tokenizer
} // namespace bia
