#ifndef BIA_TOKENIZER_TOKEN_PARSE_STATEMENT_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_STATEMENT_HPP_

#include "../parameter.hpp"
#include "any_of.hpp"
#include "expression.hpp"
#include "identifier.hpp"
#include "whitespace_eater.hpp"

#include <exception/syntax_error.hpp>
#include <log/log.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

inline exception::syntax_details decl_stmt(parameter& parameter)
{
	// compare let
	if (auto err = any_of(parameter, "invalid decl keyword", "let").second) {
		return err;
	}

	BIA_LOG(TRACE, "matched 'let'");

	// whitespaces are required
	if (auto err = eat_whitespaces(parameter)) {
		return err;
	}

	BIA_LOG(TRACE, "matched whitespace");

	if (auto err = identifier(parameter)) {
		return err;
	}

	BIA_LOG(TRACE, "matched identifier");

	// optional whitespaces
	eat_whitespaces(parameter);

	// compare '='
	auto pos = parameter.input.tellg();

	if (parameter.encoder.read(parameter.input) != '=') {
		return { pos, "expected assignment operator" };
	}

	// optional whitespaces
	eat_whitespaces(parameter);

	// read expression
	return expression(parameter);
}

inline exception::syntax_details single_stmt(parameter& parameter)
{
	auto old = parameter.backup();

	if (auto err = decl_stmt(parameter)) {
		BIA_LOG(INFO, "no decl statement {}", err.message);
		parameter.restore(old);

		return expression(parameter);
	}

	return {};
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif