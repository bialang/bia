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

	struct cmd_end
	{};

	struct identifier
	{
		resource::view memory;
		bool is_builtin;
		bytecode::member::builtin builtin;
	};

	struct string
	{
		resource::view memory;
	};

	struct regex
	{
		resource::view memory;
	};

	struct batch
	{
		std::size_t count;
	};

	struct control
	{
		enum class type
		{
			bracket_open,
			bracket_close,
			comma,
			key
		};

		type type;
		std::size_t value;
	};

	enum class keyword
	{
		let,
		import,
		while_,
		for_,
		fun,
		return_,
		break_,
		continue_,
		null,
		true_,
		false_,
		not_,
		and_,
		or_,
		if_,
		else_if,
		else_,
		type_definition
	};

	enum class type
	{
		cmd_end,
		identifier,
		batch,
		control,
		keyword,
		operator_,
		constant_string,
		constant_regex,
		constant_int,
		constant_float,
	};

	util::variant<cmd_end, identifier, batch, control, keyword, operator_, string, regex, int_type, double>
	    value;
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
