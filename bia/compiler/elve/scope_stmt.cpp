#include "helpers.hpp"

#include <bia/util/contract.hpp>
#include <tuple>

using namespace bia::compiler;
using namespace bia::tokenizer::token;

elve::Tokens elve::scope_stmt(Parameter& param, Tokens tokens)
{
	BIA_EXPECTS(tokens.front().value == Token::Keyword::scope);
	return batch(param, tokens.subspan(1));
}
