#include "helpers.hpp"

#include <bia/internal/type/object.hpp>

using namespace bia::tokenizer::token;
using namespace bia::internal;
using namespace bia::bytecode;

namespace bia {
namespace compiler {
namespace elve {

/**
 * Handles the compilation part for a function call.
 */
std::pair<Tokens, util::Optional<symbol::Local_variable>>
  member_invocation(Parameter& param, Tokens tokens, util::Optional<symbol::Local_variable> function,
                    Tokens function_tokens)
{
	BIA_EXPECTS(tokens.front().value == Operator::function_call_open);
	BIA_EXPECTS(function.empty() || param.symbols.is_tos(*function));

	const type::Definition_invokable_base* function_definition = nullptr;
	if (function.has_value() &&
	    !(function_definition = dynamic_cast<const type::Definition_invokable_base*>(function->definition))) {
		param.errors.add_error(error::Code::not_a_function, function_tokens);
	}

	std::vector<symbol::Local_variable> pushed;
	tokens = tokens.subspan(1);
	while (tokens.front().value != Operator::function_call_close) {
		util::Optional<symbol::Local_variable> argument;
		Tokens argument_tokens = tokens;
		// evaluate the argument
		std::tie(tokens, argument) = single_expression(param, argument_tokens);
		argument_tokens            = argument_tokens.left(tokens.begin());
		if (argument) {
			pushed.push_back(param.symbols.push(*argument));
			// check argument type
			if (function_definition && pushed.size() <= function_definition->arguments_size() &&
			    !function_definition->arguments_begin()[pushed.size() - 1].definition->is_assignable(
			      argument->definition)) {
				param.errors.add_error(error::Code::type_mismatch, argument_tokens);
			}

			// TODO
			BIA_ASSERT(pushed.back().offset == argument->offset);
		}
		// consume comma
		if (tokens.front().value == Token::Control::comma) {
			tokens = tokens.subspan(1);
		}
	}
	// check argument count
	if (function_definition && pushed.size() < function_definition->arguments_size()) {
		param.errors.add_error(error::Code::too_few_arguments, function_tokens);
	} else if (function_definition && pushed.size() > function_definition->arguments_size()) {
		param.errors.add_error(error::Code::too_many_arguments, function_tokens);
	}

	tokens = tokens.subspan(1);
	for (auto i = pushed.rbegin(); i != pushed.rend(); ++i) {
		param.symbols.pop(*i);
	}

	// invoke
	if (function_definition) {
		param.instructor.write<bytecode::Op_code::invoke>(function->offset);
		// result
		param.symbols.free_temporary(*function);
		return { tokens,
			       param.symbols.create_temporary(
			         dynamic_cast<const type::Definition_invokable_base*>(function->definition)->return_type()) };
	}

	return { tokens, {} };
}

std::pair<Tokens, util::Optional<symbol::Local_variable>>
  member_access(Parameter& param, Tokens tokens, symbol::Local_variable member, Tokens member_tokens)
{
	BIA_ASSERT(tokens.front().value == Operator::member_access);
	if (!dynamic_cast<const type::Object*>(member.definition)) {
		param.errors.add_error(error::Code::not_an_object, member_tokens);
	} else if (auto object = static_cast<const type::Object*>(member.definition)
	                           ->get_member(tokens[1].value.get<Token::Identifier>().memory)) {
		param.symbols.free_temporary(member);
		auto result = param.symbols.create_temporary(object->first);
		// TODO
		param.instructor.write<Op_code::copy>(Size::bit_32, result.offset, member.offset + object->second);
		return { tokens.subspan(2), result };
	} else {
		param.errors.add_error(error::Code::undefined_symbol, tokens.subspan(1, 1));
	}
	return { tokens.subspan(2), {} };
}

} // namespace elve
} // namespace compiler
} // namespace bia
