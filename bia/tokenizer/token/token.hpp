#ifndef BIA_TOKENIZER_TOKEN_TOKEN_HPP_
#define BIA_TOKENIZER_TOKEN_TOKEN_HPP_

#include "operator_.hpp"

#include <bia/bytecode/op_code.hpp>
#include <bia/error/bia_error.hpp>
#include <bia/error/exception.hpp>
#include <bia/resource/view.hpp>
#include <bia/util/variant.hpp>
#include <cstdint>
#include <type_traits>

namespace bia {
namespace tokenizer {
namespace token {

struct Token
{
	struct Batch
	{
		std::size_t statement_count;
	};

	struct Number
	{
		enum class Type
		{
			i,
			i8,
			i16,
			i32,
			i64,
			u,
			u8,
			u16,
			u32,
			u64,
			f32,
			f64,
		};

		Type type;
		union
		{
			std::ptrdiff_t i;
			std::int8_t i8;
			std::int16_t i16;
			std::int32_t i32;
			std::int64_t i64;
			typename std::make_unsigned<std::ptrdiff_t>::type u;
			std::uint8_t u8;
			std::uint16_t u16;
			std::uint32_t u32;
			std::uint64_t u64;
			float f32;
			double f64;
		} value{};

		bool operator==(const Number& other) const
		{
			if (type != other.type) {
				return false;
			}
			switch (type) {
			case Type::i:
			case Type::u: return value.u == other.value.u;
			case Type::i8:
			case Type::u8: return value.u8 == other.value.u8;
			case Type::i16:
			case Type::u16: return value.u16 == other.value.u16;
			case Type::i32:
			case Type::u32: return value.u32 == other.value.u32;
			case Type::i64:
			case Type::u64: return value.u64 == other.value.u64;
			case Type::f32: return value.f32 == other.value.f32;
			case Type::f64: return value.f64 == other.value.f64;
			default: BIA_THROW(error::Code::bad_switch_value);
			}
		}
	};

	struct Array_dimension
	{
		std::uint32_t dimension;

		bool operator==(const Array_dimension& other) const noexcept
		{
			return dimension == other.dimension;
		}
	};

	struct Identifier
	{
		resource::View memory;
	};

	struct String
	{
		resource::View memory;
	};

	struct Regex
	{
		resource::View memory;
	};

	enum class Control
	{
		type_definition,
		type_chain,
		bracket_open,
		bracket_close,
		comma,
		cmd_end,
	};

	enum class Keyword
	{
		false_,
		true_,
		null,
		use,
		mut,
		type,
		scope,
		defer,
		return_,
		yield,
		break_,
		continue_,
		import,
		as,
		let,
		if_,
		else_if,
		else_,
		drop,
		while_,
	};

	enum class Statement_type
	{
		assign_statement,
	};

	struct Sequence
	{
		enum class Type
		{
			single_expression,
		};

		Type type;
		std::size_t count;

		bool operator==(const Sequence& other) const noexcept
		{
			return type == other.type && count == other.count;
		}
		bool operator==(const Type& other) const noexcept
		{
			return type == other;
		}
	};

	typedef util::Variant<Number, Array_dimension, Batch, Control, Keyword, String, Regex, Identifier, Operator,
	                      Statement_type, Sequence>
	  Value;

	Value value;
	error::Bia_range range;

	Token() = default;
	template<typename Type>
	Token(Type&& value, error::Bia_range range) : value{ std::forward<Type>(value) }, range{ std::move(range) }
	{}
	Token(const Token& copy) : value{ copy.value }, range{ copy.range }
	{}
	Token(Token&& move) : value{ std::move(move.value) }, range{ std::move(move.range) }
	{}
	~Token() noexcept = default;
	Token& operator   =(const Token& copy)
	{
		value = copy.value;
		range = copy.range;
		return *this;
	}
	Token& operator=(Token&& move)
	{
		value = std::move(move.value);
		range = std::move(move.range);
		return *this;
	}
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
