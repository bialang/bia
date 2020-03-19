#ifndef BIA_TOKENIZER_TOKEN_TOKEN_HPP_
#define BIA_TOKENIZER_TOKEN_TOKEN_HPP_

#include "../resource/memory/memory.hpp"

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
		resource::memory::memory memory;
	};

	enum class keyword
	{
		let,
		null,
		true_,
		false_,
	};

	enum class type
	{
		cmd_end,
		identifier,
		keyword,
		constant_int,
		constant_float,
	};

	util::variant<cmd_end, identifier, keyword, std::int64_t, double> value;
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif