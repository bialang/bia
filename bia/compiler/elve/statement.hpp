#ifndef BIA_COMPILER_ELVE_STATEMENT_HPP_
#define BIA_COMPILER_ELVE_STATEMENT_HPP_

#include "declaration.hpp"
#include "expression.hpp"
#include "for_each.hpp"
#include "if_.hpp"
#include "import.hpp"
#include "present.hpp"
#include "while_.hpp"

#include <bia/exception/implementation_error.hpp>
#include <bia/util/gsl.hpp>

namespace bia {
namespace compiler {
namespace elve {

inline tokens_type statement(present present, tokens_type tokens)
{
	using namespace tokenizer::token;

	BIA_EXPECTS(!tokens.empty());

	switch (static_cast<token::type>(tokens.data()->value.index())) {
	case token::type::keyword: {
		switch (tokens.data()->value.get<token::keyword>()) {
		case token::keyword::let: tokens = declaration(present, tokens); break;
		case token::keyword::import: tokens = import(present, tokens); break;
		case token::keyword::while_: tokens = while_(present, tokens); break;
		case token::keyword::if_: tokens = elve::if_(present, tokens); break;
		case token::keyword::for_: tokens = elve::for_each(present, tokens); break;
		default: BIA_IMPLEMENTATION_ERROR("invalid keyword");
		}

		break;
	}
	default: {
		bytecode::member::local tmp{ present.variables.add_tmp() };

		tokens = expression(present, tokens, tmp);

		present.variables.remove_tmp(tmp.index);

		break;
	}
	}

	BIA_EXPECTS(!tokens.empty() &&
	            static_cast<token::type>(tokens.data()->value.index()) == token::type::cmd_end);

	return tokens.subspan(1);
}

} // namespace elve
} // namespace compiler
} // namespace bia

#endif
