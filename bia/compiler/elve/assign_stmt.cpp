#include "helpers.hpp"

#include <bia/util/contract.hpp>
#include <tuple>

using namespace bia::compiler;
using namespace bia::tokenizer::token;

elve::Tokens elve::assign_stmt(Parameter& param, Tokens tokens)
{
	BIA_EXPECTS(!tokens.empty() && tokens.front().value == Token::Statement_type::assign_statement);

	util::Optional<internal::type::Variable> destination;
	bool global = false;

	{
		const auto tmp = param.symbols.symbol(tokens.at(1).value.get<Token::Identifier>().memory);
		if (tmp.empty()) {
			param.errors.add_error(error::Code::undefined_symbol, tokens.subspan(1, 1));
		} else {
			if (tmp.is_type<symbol::Local_variable*>()) {
				auto variable = tmp.get<symbol::Local_variable*>();
				variable->used = true;
				destination = *variable;
			} else if (tmp.is_type<internal::type::Variable>()) {
				destination = tmp.get<internal::type::Variable>();
				global      = true;
			} else {
				param.errors.add_error(error::Code::symbol_not_a_value, tokens.subspan(1, 1));
			}
			if (destination.has_value() && !(destination->flags & internal::type::Variable::flag_mutable)) {
				param.errors.add_error(error::Code::symbol_immutable, tokens.subspan(1, 1));
			}
		}
	}

	// TODO process multiple identifiers
	BIA_ASSERT(tokens.at(2).value == Operator::assign);

	tokens    = tokens.subspan(3);
	auto expr = single_expression(param, tokens);
	if (expr.second) {
		if (destination.has_value()) {
			if (!destination->definition->is_assignable(expr.second->definition)) {
				param.errors.add_error(error::Code::type_mismatch,
				                       tokens.subspan(+0, tokens.size() - expr.first.size()));
			} else if (global) {
				param.instructor.write<bytecode::Op_code::copy_to_namespace>(
				  bytecode::Size::bit_32, destination->offset, expr.second->offset, 1);
			} else {
				// TODO size
				param.instructor.write<bytecode::Op_code::copy>(bytecode::Size::bit_32, destination->offset,
				                                                expr.second->offset);
			}
		}
		param.symbols.free_temporary(*expr.second);
	} else {
		// TODO improve error output
		param.errors.add_error(error::Code::why_did_this_happen, tokens);
	}
	return expr.first;
}
