#ifndef BIA_TOKENIZER_TOKEN_RECEIVER_HPP_
#define BIA_TOKENIZER_TOKEN_RECEIVER_HPP_

#include "token.hpp"

#include <bia/resource/manager.hpp>
#include <bia/util/gsl.hpp>

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
	 * @param tokens the parsed tokens
	 * @param manager the resource manager for resource creation during compilation
	 */
	virtual void receive(util::span<const token*> tokens, resource::manager& manager) = 0;
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
