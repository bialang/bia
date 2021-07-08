#include "helpers.hpp"

#include <bia/internal/type/function.hpp>
#include <bia/internal/type/integer.hpp>
#include <bia/internal/type/regex.hpp>
#include <bia/internal/type/string.hpp>
#include <bia/internal/type/void.hpp>

using namespace bia::tokenizer::token;
using namespace bia::internal;
using namespace bia::bytecode;

namespace bia {
namespace compiler {
namespace elve {

inline std::pair<Tokens, symbol::Variable> number_value(Parameter& param, Tokens tokens)
{
	using Type = Token::Number::Type;

	// get number type
	const auto& number = tokens.front().value.get<Token::Number>();
	symbol::Variable variable;

	switch (number.type) {
	case Type::i:
		variable = param.symbols.create_temporary(
		  param.symbols.symbol(util::from_cstring("int")).get<const type::Definition*>());
		param.instructor.write<bytecode::Op_code::store>(variable.location.offset, number.value.i);
		break;
	default: BIA_THROW(error::Code::bad_switch_value);
	}

	return { tokens.subspan(1), variable };
}

inline std::pair<Tokens, util::Optional<symbol::Variable>> keyword_value(Parameter& param, Tokens tokens)
{
	const auto right = param.symbols.symbol(util::from_cstring("bool"));
	BIA_ASSERT(right.is_type<const type::Definition*>());

	auto variable = param.symbols.create_temporary(right.get<const type::Definition*>());
	switch (tokens.front().value.get<Token::Keyword>()) {
	case Token::Keyword::true_:
		param.instructor.write<bytecode::Op_code::store>(variable.location.offset, std::uint8_t{ 1 });
		break;
	case Token::Keyword::false_:
		param.instructor.write<bytecode::Op_code::store>(variable.location.offset, std::uint8_t{ 0 });
		break;
	default:
		// TODO
		BIA_ASSERT(false);
	}
	return { tokens.subspan(1), variable };
}

/// Handles an identifier value and translates it to an usable variable.
inline std::pair<Tokens, util::Optional<symbol::Variable>> identifier_value(Parameter& param, Tokens tokens)
{
	BIA_EXPECTS(tokens.front().value.is_type<Token::Identifier>());

	util::Optional<symbol::Variable> variable;
	const auto identifier = param.symbols.symbol(tokens.front().value.get<Token::Identifier>().memory);
	if (identifier.empty()) {
		param.errors.add_error(error::Code::undefined_symbol, tokens.subspan(+0, 1));
	} else if (identifier.is_type<symbol::Variable>()) {
		variable = param.symbols.create_temporary(identifier.get<symbol::Variable>().definition);
		// TODO actual copy size
		param.instructor.write<Op_code::copy>(Size::bit_32, variable->location.offset,
		                                      identifier.get<symbol::Variable>().location.offset);
	} else if (identifier.is_type<internal::Symbol>()) {
		BIA_ASSERT(false);
		// variable = param.symbols.create_temporary(right.get<internal::Symbol>().definition);
		// param.instructor.write<bytecode::Op_code::load_from_namespace, std::int64_t>(
		//   variable->location.offset, right.get<internal::Symbol>().offset);
	} else {
		param.errors.add_error(error::Code::symbol_not_a_value, tokens.subspan(+0, 1));
	}
	return { tokens.subspan(1), variable };
}

std::pair<Tokens, util::Optional<symbol::Variable>> value(Parameter& param, Tokens tokens)
{
	BIA_EXPECTS(!tokens.empty());
	if (tokens.front().value.is_type<Token::Keyword>()) {
		return keyword_value(param, tokens);
	} else if (tokens.front().value.is_type<Token::Number>()) {
		return number_value(param, tokens);
	} else if (tokens.front().value.is_type<Token::Identifier>()) {
		return identifier_value(param, tokens);
	} else if (tokens.front().value.is_type<Token::String>()) {
		const auto right = param.symbols.symbol(util::from_cstring("string"));
		BIA_ASSERT(right.is_type<const type::Definition*>());

		const auto variable = param.symbols.create_temporary(right.get<const type::Definition*>());
		const auto index    = param.serializer.index_of(tokens.front().value.get<Token::String>().memory);
		param.instructor.write<bytecode::Op_code::load_resource>(variable.location.offset, index);
		return { tokens.subspan(1), variable };
	} else if (tokens.front().value.is_type<Token::Regex>()) {
		BIA_ASSERT(false);
		// const auto right = param.symbols.symbol(util::from_cstring("regex"));
		// BIA_ASSERT(right.is_type<const type::Definition*>());

		// const auto variable = param.symbols.create_temporary(right.get<const type::Definition*>());
		// const auto index    = param.serializer.index_of(tokens.front().value.get<Token::Regex>().memory);
		// param.instructor.write<bytecode::Op_code::load_resource, memory::gc::Regex>(variable.location.offset,
		//                                                                             index);
		// return { tokens.subspan(1), variable };
	}
	printf("%zu\n", tokens.front().value.index());
	// TODO
	BIA_ASSERT(false);
}

} // namespace elve
} // namespace compiler
} // namespace bia
