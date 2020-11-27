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

	struct number
	{};

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
		type
	};

	util::variant<number, control, keyword, string, regex, identifier, operator_, array_dimension> value;
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
