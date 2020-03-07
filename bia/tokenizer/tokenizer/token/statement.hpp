#ifndef BIA_TOKENIZER_TOKEN_STATEMENT_HPP_
#define BIA_TOKENIZER_TOKEN_STATEMENT_HPP_

#include "any_of.hpp"
#include "expression.hpp"
#include "identifier.hpp"
#include "token_parameter.hpp"
#include "whitespace_eater.hpp"

#include <exception/syntax_error.hpp>
#include <log/log.hpp>

namespace bia {
namespace tokenizer {
namespace token {

inline exception::syntax_details decl_stmt(token_parameter& token_parameter)
{
	// compare let
	if (auto err = any_of(token_parameter, "invalid decl keyword", "let").second) {
		return err;
	}

	BIA_LOG(TRACE, "matched 'let'");

	// whitespaces are required
	if (auto err = eat_whitespaces(token_parameter)) {
		return err;
	}

	BIA_LOG(TRACE, "matched whitespace");

	if (auto err = identifier(token_parameter)) {
		return err;
	}

	BIA_LOG(TRACE, "matched identifier");

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
	auto old = token_parameter.backup();
	
	if (auto err = decl_stmt(token_parameter)) {
		BIA_LOG(INFO, "no decl statement {}", err.message);
		token_parameter.restore(old);

		return expression(token_parameter);
	}

	return {};
}

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif