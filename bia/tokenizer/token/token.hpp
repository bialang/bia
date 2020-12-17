#ifndef BIA_TOKENIZER_TOKEN_TOKEN_HPP_
#define BIA_TOKENIZER_TOKEN_TOKEN_HPP_

#include "operator_.hpp"

#include <bia/bytecode/op_code.hpp>
#include <bia/error/exception.hpp>
#include <bia/resource/view.hpp>
#include <bia/util/variant.hpp>
#include <cstdint>

namespace bia {
namespace tokenizer {
namespace token {

struct token
{
	struct batch
	{
		std::size_t statement_count;
	};

	struct number
	{
		enum class type
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

		type type;
		union
		{
			int i;
			std::int8_t i8;
			std::int16_t i16;
			std::int32_t i32;
			std::int64_t i64;
			unsigned int u;
			std::uint8_t u8;
			std::uint16_t u16;
			std::uint32_t u32;
			std::uint64_t u64;
			float f32;
			double f64;
		} value{};

		bool operator==(const number& other) const
		{
			if (type != other.type) {
				return false;
			}
			switch (type) {
			case type::i:
			case type::u: return value.u == other.value.u;
			case type::i8:
			case type::u8: return value.u8 == other.value.u8;
			case type::i16:
			case type::u16: return value.u16 == other.value.u16;
			case type::i32:
			case type::u32: return value.u32 == other.value.u32;
			case type::i64:
			case type::u64: return value.u64 == other.value.u64;
			case type::f32: return value.f32 == other.value.f32;
			case type::f64: return value.f64 == other.value.f64;
			default: BIA_THROW(error::code::bad_switch_value);
			}
		}
	};

	struct array_dimension
	{
		std::uint32_t dimension;

		bool operator==(const array_dimension& other) const noexcept
		{
			return dimension == other.dimension;
		}
	};

	struct identifier
	{
		resource::view memory;
	};

	struct string
	{
		resource::view memory;
	};

	struct regex
	{
		resource::view memory;
	};

	enum class control
	{
		type_definition,
		type_chain,
		bracket_open,
		bracket_close,
		comma,
		cmd_end,
	};

	enum class keyword
	{
		false_,
		true_,
		null,
		use,
		mut,
		type,
		scoped,
		defer,
		return_,
		yield,
		break_,
		continue_,
		import,
		as,
		let,
	};

	util::variant<number, array_dimension, batch, control, keyword, string, regex, identifier, operator_,
	              array_dimension>
	  value;

	token() = default;
	template<typename Type>
	token(Type&& value) : value{ std::forward<Type>(value) }
	{}
	token(const token& copy) : value{ copy.value }
	{}
	token(token&& move) : value{ std::move(move.value) }
	{}
	token& operator=(const token& copy)
	{
		value = copy.value;
		return *this;
	}
	token& operator=(token&& move)
	{
		value = std::move(move.value);
		return *this;
	}
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
