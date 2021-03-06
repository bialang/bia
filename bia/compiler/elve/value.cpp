#include "helpers.hpp"

#include <bia/internal/type/function.hpp>
#include <bia/internal/type/integer.hpp>
#include <bia/internal/type/regex.hpp>
#include <bia/internal/type/string.hpp>
#include <bia/internal/type/void.hpp>

using namespace bia::tokenizer::token;
using namespace bia::internal;

namespace bia {
namespace compiler {
namespace elve {

inline std::pair<Tokens, symbol::Variable> number_value(Parameter& param, Tokens tokens)
{
	using Type = Token::Number::Type;

	// get number type
	const auto& number = tokens.front().value.get<Token::Number>();

	symbol::Symbol right_type;
	switch (number.type) {
	case Type::i: right_type = param.symbols.symbol(util::from_cstring("int")); break;
	case Type::i32: right_type = param.symbols.symbol(util::from_cstring("int32")); break;
	case Type::f32: right_type = param.symbols.symbol(util::from_cstring("float32")); break;
	default: BIA_THROW(error::Code::bad_switch_value);
	}
	BIA_ASSERT(right_type.is_type<type::Definition*>());

	auto variable = param.symbols.create_temporary(right_type.get<type::Definition*>());
	switch (number.type) {
	case Type::i: {
		// TODO check size with default int size
		param.instructor.write<bytecode::Op_code::load>(variable.location.offset, number.value.i64);
		break;
	}
	case Type::i32:
	case Type::u32:
	case Type::f32:
		param.instructor.write<bytecode::Op_code::load>(variable.location.offset, number.value.i32);
		break;
	default: BIA_THROW(error::Code::bad_switch_value);
	}

	return { tokens.subspan(1), variable };
}

inline std::pair<Tokens, util::Optional<symbol::Variable>> keyword_value(Parameter& param, Tokens tokens)
{
	const auto right = param.symbols.symbol(util::from_cstring("bool"));
	BIA_ASSERT(right.is_type<type::Definition*>());

	auto variable = param.symbols.create_temporary(right.get<type::Definition*>());
	switch (tokens.front().value.get<Token::Keyword>()) {
	case Token::Keyword::true_:
		param.instructor.write<bytecode::Op_code::load>(variable.location.offset, std::int8_t{ 1 });
		break;
	case Token::Keyword::false_:
		param.instructor.write<bytecode::Op_code::load>(variable.location.offset, std::int8_t{ 0 });
		break;
	default:
		// TODO
		BIA_ASSERT(false);
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
		util::Optional<symbol::Variable> variable;
		const auto right = param.symbols.symbol(tokens.front().value.get<Token::Identifier>().memory);
		if (right.empty()) {
			param.errors.add_error(error::Code::undefined_symbol, tokens.subspan(+0, 1));
		} else if (!right.is_type<symbol::Variable>()) {
			param.errors.add_error(error::Code::symbol_not_a_variable, tokens.subspan(+0, 1));
		} else {
			variable = param.symbols.create_temporary(right.get<symbol::Variable>().definition);
			param.instructor.write<bytecode::Op_code::copy, std::int64_t>(
			  variable->location.offset, right.get<symbol::Variable>().location.offset);
		}
		return { tokens.subspan(1), variable };
	} else if (tokens.front().value.is_type<Token::String>()) {
		const auto right = param.symbols.symbol(util::from_cstring("string"));
		BIA_ASSERT(right.is_type<type::Definition*>());

		const auto variable = param.symbols.create_temporary(right.get<type::Definition*>());
		const auto index    = param.serializer.index_of(tokens.front().value.get<Token::String>().memory);
		param.instructor.write<bytecode::Op_code::load_resource, memory::gc::String>(variable.location.offset,
		                                                                             index);
		return { tokens.subspan(1), variable };
	} else if (tokens.front().value.is_type<Token::Regex>()) {
		const auto right = param.symbols.symbol(util::from_cstring("regex"));
		BIA_ASSERT(right.is_type<type::Definition*>());

		const auto variable = param.symbols.create_temporary(right.get<type::Definition*>());
		const auto index    = param.serializer.index_of(tokens.front().value.get<Token::Regex>().memory);
		param.instructor.write<bytecode::Op_code::load_resource, memory::gc::Regex>(variable.location.offset,
		                                                                            index);
		return { tokens.subspan(1), variable };
	}

	// TODO
	BIA_ASSERT(false);
}

} // namespace elve
} // namespace compiler
} // namespace bia
