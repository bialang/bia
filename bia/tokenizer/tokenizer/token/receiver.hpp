#ifndef BIA_TOKENIZER_TOKEN_RECEIVER_HPP_
#define BIA_TOKENIZER_TOKEN_RECEIVER_HPP_

#include "token.hpp"

#include <util/gsl.hpp>

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
	 * @param first the beginning of the token set
	 * @param last the end of the token set
	 */
	virtual void receive(util::not_null<const token*> first, util::not_null<const token*> last) = 0;
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif