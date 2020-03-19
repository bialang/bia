#ifndef BIA_TOKENIZER_TOKEN_RECEIVER_HPP_
#define BIA_TOKENIZER_TOKEN_RECEIVER_HPP_

#include "token.hpp"

namespace bia {
namespace tokenizer {
namespace token {

/**
 * This interface receives the parsed input as tokens.
 */
class receiver
{
public:
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