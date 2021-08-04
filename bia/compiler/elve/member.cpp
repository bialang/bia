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
std::pair<Tokens, util::Optional<symbol::Variable>>
  member_invocation(Parameter& param, Tokens tokens, util::Optional<symbol::Variable> function,
                    Tokens function_tokens)
{
	BIA_EXPECTS(tokens.front().value == Operator::function_call_open);
	BIA_EXPECTS(function.empty() || param.symbols.is_tos(*function));

	const std::vector<type::Argument>* argument_definitions = nullptr;
	if (function.has_value()) {
		if (const auto ptr = dynamic_cast<const type::Function*>(function->definition)) {
			argument_definitions = &ptr->arguments();
		} else {
			param.errors.add_error(error::Code::not_a_function, function_tokens);
		}
	}
	const bool is_function = argument_definitions != nullptr;

	std::vector<symbol::Variable> pushed;
	tokens = tokens.subspan(1);
	while (tokens.front().value != Operator::function_call_close) {
		util::Optional<symbol::Variable> argument;
		Tokens argument_tokens = tokens;
		// evaluate the argument
		std::tie(tokens, argument) = single_expression(param, argument_tokens);
		argument_tokens            = argument_tokens.left(tokens.begin());
		if (argument) {
			pushed.push_back(param.symbols.push(*argument));
			// check argument type
			if (argument_definitions && pushed.size() <= argument_definitions->size() &&
			    !argument_definitions->at(pushed.size() - 1).definition->is_assignable(argument->definition)) {
				param.errors.add_error(error::Code::type_mismatch, argument_tokens);
			}

			// TODO
			BIA_ASSERT(pushed.back().location.offset == argument->location.offset);
		}
		// consume comma
		if (tokens.front().value == Token::Control::comma) {
			tokens = tokens.subspan(1);
		}
	}
	// check argument count
	if (argument_definitions && pushed.size() < argument_definitions->size()) {
		param.errors.add_error(error::Code::too_few_arguments, function_tokens);
	} else if (argument_definitions && pushed.size() > argument_definitions->size()) {
		param.errors.add_error(error::Code::too_many_arguments, function_tokens);
	}

	tokens = tokens.subspan(1);
	for (auto i = pushed.rbegin(); i != pushed.rend(); ++i) {
		param.symbols.pop(*i);
	}

	// invoke
	if (is_function) {
		param.instructor.write<bytecode::Op_code::invoke>(function->location.offset);
		// result
		param.symbols.free_temporary(*function);
		return { tokens, param.symbols.create_temporary(
			                 static_cast<const type::Function*>(function->definition)->return_type()) };
	}

	return { tokens, {} };
}

std::pair<Tokens, util::Optional<symbol::Variable>>
  member_access(Parameter& param, Tokens tokens, symbol::Variable member, Tokens member_tokens)
{
	BIA_ASSERT(tokens.front().value == Operator::member_access);
	if (!dynamic_cast<const type::Object*>(member.definition)) {
		param.errors.add_error(error::Code::not_an_object, member_tokens);
	} else if (auto object = static_cast<const type::Object*>(member.definition)
	                           ->get_member(tokens[1].value.get<Token::Identifier>().memory)) {
		param.symbols.free_temporary(member);
		auto result = param.symbols.create_temporary(object->first);
		// TODO
		param.instructor.write<Op_code::copy>(Size::bit_32, result.location.offset,
		                                      member.location.offset + object->second);
		return { tokens.subspan(2), result };
	} else {
		param.errors.add_error(error::Code::undefined_symbol, tokens.subspan(1, 1));
	}
	return { tokens.subspan(2), {} };
}

} // namespace elve
} // namespace compiler
} // namespace bia
