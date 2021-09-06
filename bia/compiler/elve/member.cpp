#include "helpers.hpp"

#include <bia/internal/type/object.hpp>

using namespace bia::tokenizer::token;
using namespace bia::internal;
using namespace bia::bytecode;

namespace bia {
namespace compiler {
namespace elve {

inline Tokens push_arguments(Parameter& param, Tokens tokens,
                             const type::Definition_invokable_base* function_definition,
                             const Tokens& function_tokens)
{
	BIA_EXPECTS(tokens.front().value == Operator::function_call_open);
	std::vector<symbol::Local_variable> pushed;
	std::streampos vararg_size_pos{};
	std::size_t arguments_at_vararg = 0;
	util::Optional<symbol::Local_variable> vararg_size;
	std::size_t argument_count = 0;
	tokens                     = tokens.subspan(1);
	for (; tokens.front().value != Operator::function_call_close; ++argument_count) {
		const auto required = function_definition ? function_definition->argument_at(argument_count) : nullptr;
		const auto union_definition =
		  dynamic_cast<const type::Definition_union_base*>(required ? required->definition : nullptr);
		std::streampos union_index_pos{};

		// varargs requires a size
		if (function_definition && function_definition->is_vararg_index(argument_count)) {
			BIA_LOG(INFO, "Setting vararg to {}", argument_count);
			arguments_at_vararg = argument_count;
			pushed.push_back(param.symbols.create_temporary(
			  param.context.global_namespace().type_system().definition_of<std::ptrdiff_t>()));
			vararg_size     = pushed.back();
			vararg_size_pos = param.instructor.output().tellp();
			param.instructor.write<bytecode::Op_code::store>(pushed.back().offset, std::ptrdiff_t{ 0 });
		}

		// type union requires an index
		if (union_definition) {
			pushed.push_back(param.symbols.create_temporary(
			  param.context.global_namespace().type_system().definition_of<std::size_t>()));
			union_index_pos = param.instructor.output().tellp();
			param.instructor.write<bytecode::Op_code::store>(pushed.back().offset, util::npos);
		}

		// evaluate argument
		util::Optional<symbol::Local_variable> argument;
		Tokens argument_tokens     = tokens;
		std::tie(tokens, argument) = single_expression(param, argument_tokens);
		argument_tokens            = argument_tokens.left(tokens.begin());

		if (argument.has_value()) {
			BIA_ASSERT(param.symbols.is_tos(*argument));

			// update index of type union
			if (union_definition) {
				const auto pos = param.instructor.output().tellp();
				param.instructor.output().seekp(union_index_pos);
				param.instructor.write<bytecode::Op_code::store>(
				  pushed.back().offset, union_definition->definition_index(argument->definition));
				param.instructor.output().seekp(pos);
			}

			pushed.push_back(*argument);

			// check type
			if (required && !required->definition->is_assignable(argument->definition)) {
				param.errors.add_error(error::Code::type_mismatch, argument_tokens);
			}
		}

		// consume comma
		if (tokens.front().value == Token::Control::comma) {
			tokens = tokens.subspan(1);
		}
	}

	// update size of varargs
	if (vararg_size.has_value()) {
		BIA_LOG(INFO, "dogin {}", argument_count);
		const auto pos = param.instructor.output().tellp();
		param.instructor.output().seekp(vararg_size_pos);
		param.instructor.write<bytecode::Op_code::store>(
		  vararg_size->offset, static_cast<std::ptrdiff_t>(argument_count - arguments_at_vararg));
		param.instructor.output().seekp(pos);
	}

	// check argument boundaries
	if (function_definition && argument_count < function_definition->argument_lower_count()) {
		param.errors.add_error(error::Code::too_few_arguments, function_tokens);
	} else if (function_definition && argument_count > function_definition->argument_upper_count()) {
		param.errors.add_error(error::Code::too_many_arguments, function_tokens);
	}

	// pop all pushed arguments
	for (auto it = pushed.rbegin(); it != pushed.rend(); ++it) {
		param.symbols.free_temporary(*it);
	}

	return tokens.subspan(1);
}

/// Handles the compilation part for a function call.
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

	tokens = push_arguments(param, tokens, function_definition, function_tokens);

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
  member_access(Parameter& param, Tokens tokens, symbol::Local_variable object, Tokens object_tokens)
{
	BIA_ASSERT(tokens.front().value == Operator::member_access);
	if (!dynamic_cast<const type::Definition<type::Dynamic_object>*>(object.definition)) {
		param.errors.add_error(error::Code::not_an_object, object_tokens);
	} else if (auto member = static_cast<const type::Definition<type::Dynamic_object>*>(object.definition)
	                           ->get_member(tokens[1].value.get<Token::Identifier>().memory)) {
		param.symbols.free_temporary(object);
		auto result = param.symbols.create_temporary(member->definition);
		// TODO
		param.instructor.write<Op_code::get>(result.offset, object.offset, member->offset);
		return { tokens.subspan(2), result };
	} else {
		param.errors.add_error(error::Code::undefined_symbol, tokens.subspan(1, 1));
	}
	return { tokens.subspan(2), {} };
}

} // namespace elve
} // namespace compiler
} // namespace bia
