#ifndef BIA_TOKENIZER_TOKEN_RECEIVER_HPP_
#define BIA_TOKENIZER_TOKEN_RECEIVER_HPP_

#include "keyword.hpp"
#include "../resource/memory/memory.hpp"

#include <cstdint>
#include <util/variant.hpp>

namespace bia {
namespace tokenizer {
namespace token {

/**
 * This interface receives the parsed input as tokens.
 */
class receiver
{
public:
	struct token
	{
		enum class type
		{
			cmd_end,
			identifier,
			keyword,
			constant_int,
			constant_float,
		};

		util::variant<int, resource::memory::memory, keyword, std::int64_t, double> value;
	};

	/**
	 * Destructor.
	 */
	virtual ~receiver() = default;
	/**
	 * This function is called when a new set of tokens is available. The token are not guaranteed to be
	 * grouped.
	 *
	 * @param begin the beginning of the token set
	 * @param end the end of the token set
	 */
	virtual void receive(const token* begin, const token* end) = 0;
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif