#include "helpers.hpp"

#include <algorithm>
#include <bia/internal/type/object.hpp>

using namespace bia::tokenizer::token;
using namespace bia::internal;
using namespace bia::bytecode;

namespace bia {
namespace compiler {
namespace elve {

struct Arranged_argument
{
	const type::Argument* definition;
	Tokens tokens;
};

struct Pusher
{
	Parameter& param;
	const type::Definition_invokable_base* function_definition;
	std::vector<Arranged_argument> arguments;
	std::vector<symbol::Local_variable> pushed;

	void load_arguments(Tokens& tokens)
	{
		tokens = tokens.subspan(1);
		while (tokens.front().value != Operator::function_call_close) {
			// named parameter
			const type::Argument* required = nullptr;
			if (tokens[0].value.is_type<Token::Identifier>()) {
				required = function_definition == nullptr
				             ? nullptr
				             : function_definition->argument_at(tokens[0].value.get<Token::Identifier>().memory);
				if (function_definition != nullptr && required == nullptr) {
					param.errors.add_error(error::Code::unknown_argument, tokens.subspan(+0, 1));
				} else if (std::find_if(arguments.begin(), arguments.end(), [&](const Arranged_argument& arg) {
					           return arg.definition == required;
				           }) != arguments.end()) {
					param.errors.add_error(error::Code::multiple_argument, tokens.subspan(+0, 1));
				}
				tokens = tokens.subspan(1);
			} else {
				required =
				  function_definition == nullptr ? nullptr : function_definition->argument_at(arguments.size());
			}

			BIA_ASSERT(tokens.front().value == Token::Sequence::Type::single_expression);
			const std::size_t size = tokens[0].value.get<Token::Sequence>().count + 1;
			arguments.push_back({ required, tokens.subspan(+0, size) });

			// skip + comma
			tokens = tokens.subspan(size + static_cast<int>(tokens.at(size).value == Token::Control::comma));
		}
		tokens = tokens.subspan(1);
	}
	void rearrange_arguments()
	{
		// don't do it if there are arguments missing
		if (arguments.size() < function_definition->positional_argument_count()) {
			return;
		}

		for (std::size_t i = 0; i < function_definition->positional_argument_count(); ++i) {
			const auto real = function_definition->argument_at(i);
			const auto it   = std::find_if(arguments.begin() + i, arguments.end(),
			                               [&](const Arranged_argument& arg) { return arg.definition == real; });
			if (it != arguments.end()) {
				auto value = *it;
				arguments.erase(it);
				arguments.insert(arguments.begin() + i, std::move(value));
			}
		}
	}
	void push_argument(const Arranged_argument& argument)
	{
		const auto union_definition = dynamic_cast<const type::Definition_union_base*>(
		  argument.definition == nullptr ? nullptr : argument.definition->definition);
		std::streampos union_index_pos{};

		// type union requires an index
		if (union_definition != nullptr) {
			pushed.push_back(param.symbols.create_temporary(
			  param.context.global_namespace().type_system().definition_of<std::size_t>()));
			union_index_pos = param.instructor.output().tellp();
			param.instructor.write<bytecode::Op_code::store>(pushed.back().offset, util::npos);
		}

		// evaluate argument even if it has a faulty type
		auto value = single_expression(param, argument.tokens).second;
		if (value.has_value()) {
			BIA_ASSERT(param.symbols.is_tos(*value));

			// update index of type union
			if (union_definition) {
				const auto pos = param.instructor.output().tellp();
				param.instructor.output().seekp(union_index_pos);
				param.instructor.write<bytecode::Op_code::store>(
				  pushed.back().offset, union_definition->definition_index(value->definition));
				param.instructor.output().seekp(pos);
			}
			pushed.push_back(*value);

			// check type
			if (argument.definition != nullptr &&
			    !argument.definition->definition->is_assignable(value->definition)) {
				param.errors.add_error(error::Code::type_mismatch, argument.tokens);
			}
		}
	}
	void push_all()
	{
		const std::size_t argument_pivot = std::min(
		  arguments.size(),
		  function_definition == nullptr ? arguments.size() : function_definition->positional_argument_count());

		// push positionals
		for (std::size_t i = 0; i < argument_pivot; ++i) {
			push_argument(arguments[i]);
		}

		// varargs requires a size
		if (function_definition != nullptr && function_definition->has_vararg()) {
			pushed.push_back(param.symbols.create_temporary(
			  param.context.global_namespace().type_system().definition_of<std::ptrdiff_t>()));
			const auto count_value     = pushed.back();
			const auto stream_position = param.instructor.output().tellp();
			param.instructor.write<bytecode::Op_code::store>(pushed.back().offset, std::ptrdiff_t{ 0 });

			for (std::size_t i = argument_pivot; i < arguments.size(); ++i) {
				push_argument(arguments[i]);
			}

			// update size of varargs
			if (argument_pivot < arguments.size()) {
				const auto pos = param.instructor.output().tellp();
				param.instructor.output().seekp(stream_position);
				param.instructor.write<bytecode::Op_code::store>(
				  count_value.offset, static_cast<std::ptrdiff_t>(arguments.size() - argument_pivot));
				param.instructor.output().seekp(pos);
			}
		}

		// pop all pushed arguments
		for (auto it = pushed.rbegin(); it != pushed.rend(); ++it) {
			param.symbols.free_temporary(*it);
		}
	}
	error::Code check_errors()
	{
		if (function_definition != nullptr &&
		    arguments.size() < function_definition->positional_argument_count()) {
			return error::Code::too_few_arguments;
		} else if (function_definition != nullptr &&
		           arguments.size() > function_definition->positional_argument_count() &&
		           !function_definition->has_vararg()) {
			return error::Code::too_many_arguments;
		}
		return error::Code::success;
	}
};

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

	Pusher pusher{ param, function_definition };
	pusher.load_arguments(tokens);
	pusher.rearrange_arguments();
	pusher.push_all();
	const auto code = pusher.check_errors();
	if (code != error::Code::success) {
		param.errors.add_error(code, function_tokens);
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
  member_access(Parameter& param, Tokens tokens, util::Optional<symbol::Local_variable> object,
                Tokens object_tokens)
{
	BIA_ASSERT(tokens.front().value == Operator::member_access);
	if (object.has_value()) {
		if (!dynamic_cast<const type::Definition<type::Dynamic_object>*>(object->definition)) {
			param.errors.add_error(error::Code::not_an_object, object_tokens);
		} else {
			const auto symbol = static_cast<const type::Definition<type::Dynamic_object>*>(object->definition)
			                      ->get_member(tokens[1].value.get<Token::Identifier>().memory);
			if (symbol.is_type<internal::type::Variable>()) {
				const auto variable = symbol.get<internal::type::Variable>();
				param.symbols.free_temporary(*object);
				auto result = param.symbols.create_temporary(variable.definition);
				// TODO
				param.instructor.write<Op_code::load_object>(0, object->offset);
				param.instructor.write<Op_code::load_from_namespace>(Size::bit_64, result.offset, variable.offset, 0);
				return { tokens.subspan(2), result };
			} else if (symbol.is_type<const type::Definition_base*>()) {
				// TODO implement this
				BIA_ASSERT(false);
			} else {
				param.errors.add_error(error::Code::undefined_symbol, tokens.subspan(1, 1));
			}
		}
	}
	return { tokens.subspan(2), {} };
}

} // namespace elve
} // namespace compiler
} // namespace bia
