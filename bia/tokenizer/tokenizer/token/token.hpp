#ifndef BIA_TOKENIZER_TOKEN_TOKEN_HPP_
#define BIA_TOKENIZER_TOKEN_TOKEN_HPP_

#include <resource/view.hpp>
#include <util/variant.hpp>
#include <cstdint>

namespace bia {
namespace tokenizer {
namespace token {

struct token
{
	struct cmd_end
	{};

	struct identifier
	{
		resource::view memory;
	};

	enum class keyword
	{
		let,
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
		keyword,
		operator_,
		constant_int,
		constant_float,
	};

	util::variant<cmd_end, identifier, keyword, operator_, std::int64_t, double> value;
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif