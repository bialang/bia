#ifndef BIA_TOKENIZER_TOKEN_STATEMENT_HPP_
#define BIA_TOKENIZER_TOKEN_STATEMENT_HPP_

#include "any_of.hpp"
#include "expression.hpp"
#include "identifier.hpp"
#include "token_parameter.hpp"
#include "whitespace_eater.hpp"

#include <exception/syntax_error.hpp>

namespace bia {
namespace tokenizer {
namespace token {

inline exception::syntax_details decl_stmt(token_parameter& token_parameter)
{
	// compare let
	if (auto err = any_of(token_parameter, "invalid decl keyword", "let").second) {
		return err;
	}

	// whitespaces are required
	if (auto err = eat_whitespaces(token_parameter)) {
		return err;
	}

	identifier(token_parameter);

	// optional whitespaces
	eat_whitespaces(token_parameter);

	// compare '='
	auto pos = token_parameter.input.tellg();

	if (token_parameter.encoder.read(token_parameter.input) != '=') {
		return { pos, "expected assignment operator" };
	}

	// optional whitespaces
	eat_whitespaces(token_parameter);

	// read expression
	return expression(token_parameter);
}

inline exception::syntax_details single_stmt(token_parameter& token_parameter)
{
	return decl_stmt(token_parameter);
}

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif