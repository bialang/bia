#ifndef BIA_TOKENIZER_TOKEN_TOKEN_HPP_
#define BIA_TOKENIZER_TOKEN_TOKEN_HPP_

#include "operator_.hpp"

#include <bia/bytecode/op_code.hpp>
#include <bia/resource/view.hpp>
#include <bia/util/variant.hpp>
#include <cstdint>

namespace bia {
namespace tokenizer {
namespace token {

struct token
{
	typedef std::int64_t int_type;
	typedef double float64_type;

	struct cmd_end
	{};

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
		} value;
	};

	struct array_dimension
	{
		std::uint32_t dimension;
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
	};

	util::variant<number, batch, control, keyword, string, regex, identifier, operator_, array_dimension>
	    value;
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
