#ifndef BIA_TOKENIZER_TOKEN_TOKEN_HPP_
#define BIA_TOKENIZER_TOKEN_TOKEN_HPP_

#include <cstdint>
#include <resource/view.hpp>
#include <util/variant.hpp>

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
	};

	struct string
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
			comma
		};

		type type;
		std::size_t value;
	};

	enum class keyword
	{
		let,
		import,
		while_,
		break_,
		continue_,
		null,
		true_,
		false_,
		not_,
		and_,
		or_
	};

	enum class operator_
	{
		tilde,
		minus
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
		constant_int,
		constant_float,
	};

	util::variant<cmd_end, identifier, batch, control, keyword, operator_, string, int_type, double> value;
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif