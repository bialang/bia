#include "helpers.hpp"

#include <bia/internal/type/function.hpp>
#include <bia/internal/type/regex.hpp>
#include <bia/internal/type/string.hpp>
#include <bia/internal/type/void.hpp>

using namespace bia::tokenizer::token;
using namespace bia::internal;
using namespace bia::bytecode;

namespace bia {
namespace compiler {
namespace elve {

template<std::size_t N, typename Type>
inline symbol::Local_variable write_number(Parameter& param, const char (&name)[N], Type value)
{
	const auto definition = param.symbols.symbol(util::Span<const char*>{ name, N });
	BIA_ASSERT(definition.is_type<const type::Definition_base*>());
	auto variable = param.symbols.create_temporary(definition.get<const type::Definition_base*>());
	param.instructor.write<bytecode::Op_code::store>(variable.offset, value);
	return variable;
}

inline std::pair<Tokens, symbol::Local_variable> number_value(Parameter& param, Tokens tokens)
{
	using Type = Token::Number::Type;

	// get number type
	const auto& number = tokens.front().value.get<Token::Number>();
	symbol::Local_variable variable;

	switch (number.type) {
	case Type::i: variable = write_number(param, "int", number.value.i); break;
	case Type::i8: variable = write_number(param, "int8", number.value.i8); break;
	case Type::i16: variable = write_number(param, "int16", number.value.i16); break;
	case Type::i32: variable = write_number(param, "int32", number.value.i32); break;
	case Type::i64: variable = write_number(param, "int64", number.value.i64); break;
	case Type::u: variable = write_number(param, "uint", number.value.u); break;
	case Type::u8: variable = write_number(param, "uint8", number.value.u8); break;
	case Type::u16: variable = write_number(param, "uint16", number.value.u16); break;
	case Type::u32: variable = write_number(param, "uint32", number.value.u32); break;
	case Type::u64: variable = write_number(param, "uint64", number.value.u64); break;
	case Type::f32: variable = write_number(param, "float32", number.value.f32); break;
	case Type::f64: variable = write_number(param, "float64", number.value.f64); break;
	default: BIA_THROW(error::Code::bad_switch_value);
	}

	return { tokens.subspan(1), variable };
}

inline std::pair<Tokens, util::Optional<symbol::Local_variable>> keyword_value(Parameter& param,
                                                                               Tokens tokens)
{
	const auto right = param.symbols.symbol(util::from_cstring("bool"));
	BIA_ASSERT(right.is_type<const type::Definition_base*>());

	auto variable = param.symbols.create_temporary(right.get<const type::Definition_base*>());
	switch (tokens.front().value.get<Token::Keyword>()) {
	case Token::Keyword::true_:
		param.instructor.write<bytecode::Op_code::store>(variable.offset, std::uint8_t{ 1 });
		break;
	case Token::Keyword::false_:
		param.instructor.write<bytecode::Op_code::store>(variable.offset, std::uint8_t{ 0 });
		break;
	default: BIA_THROW(error::Code::bad_switch_value);
	}
	return { tokens.subspan(1), variable };
}

/// Handles an identifier value and translates it to an usable variable.
inline std::pair<Tokens, util::Optional<symbol::Local_variable>> identifier_value(Parameter& param,
                                                                                  Tokens tokens)
{
	BIA_EXPECTS(tokens.front().value.is_type<Token::Identifier>());

	util::Optional<symbol::Local_variable> variable;
	const auto identifier = param.symbols.symbol(tokens.front().value.get<Token::Identifier>().memory);
	if (identifier.empty()) {
		param.errors.add_error(error::Code::undefined_symbol, tokens.subspan(+0, 1));
	} else if (identifier.is_type<symbol::Local_variable>()) {
		const auto& source = identifier.get<symbol::Local_variable>();
		variable           = param.symbols.create_temporary(source.definition);
		// copy all bits
		for (std::size_t copied = 0, size = source.definition->size(); copied < size;) {
			Size s = Size::bit_8;
			if (size >= 8) {
				s = Size::bit_64;
			} else if (size >= 4) {
				s = Size::bit_32;
			} else if (size >= 2) {
				s = Size::bit_16;
			}
			param.instructor.write<Op_code::copy>(s, variable->offset + copied, source.offset + copied);
			copied += size_to_bits(s) / 8;
		}
	} else if (identifier.is_type<internal::Global_variable>()) {
		variable = param.symbols.create_temporary(identifier.get<internal::Global_variable>().definition);
		param.instructor.write<bytecode::Op_code::load_from_namespace>(
		  Size::bit_64, variable->offset, identifier.get<internal::Global_variable>().offset);
	} else {
		param.errors.add_error(error::Code::symbol_not_a_value, tokens.subspan(+0, 1));
	}
	return { tokens.subspan(1), variable };
}

std::pair<Tokens, util::Optional<symbol::Local_variable>> value(Parameter& param, Tokens tokens)
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
		BIA_ASSERT(right.is_type<const type::Definition_base*>());

		const auto variable = param.symbols.create_temporary(right.get<const type::Definition_base*>());
		const auto index    = param.serializer.index_of(tokens.front().value.get<Token::String>().memory);
		param.instructor.write<bytecode::Op_code::load_resource>(variable.offset, index);
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
	// TODO
	BIA_ASSERT(false);
}

} // namespace elve
} // namespace compiler
} // namespace bia
