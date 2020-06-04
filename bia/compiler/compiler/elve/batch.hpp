#ifndef BIA_COMPILER_ELVE_BATCH_HPP_
#define BIA_COMPILER_ELVE_BATCH_HPP_

#include "present.hpp"

namespace bia {
namespace compiler {
namespace elve {

tokens_type statement(present present, tokens_type tokens);

inline tokens_type batch(present present, tokens_type tokens)
{
	using namespace tokenizer::token;

	BIA_EXPECTS(!tokens.empty() &&
	            static_cast<token::type>(tokens.data()->value.index()) == token::type::batch);

	auto count = tokens.data()->value.get<token::batch>().count;

	tokens = tokens.subspan(1);

	while (count--) {
		tokens = statement(present, tokens);
	}

	return tokens;
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
