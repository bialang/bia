#ifndef BIA_TOKENIZER_TOKEN_BUNDLE_HPP_
#define BIA_TOKENIZER_TOKEN_BUNDLE_HPP_

#include "receiver.hpp"

#include <vector>

namespace bia {
namespace tokenizer {
namespace token {

class bundle
{
public:
	typedef std::size_t state_type;

	/**
	 * Adds a new token to the bundle.
	 *
	 * @param token the new token
	 * @returns the index of the newly added token
	 */
	std::size_t add(token token);
	void clear();
	state_type save();
	void restore(state_type state);
	token& at(std::size_t index);
	const token* begin() const noexcept;
	const token* end() const noexcept;
	std::size_t size() const noexcept;

private:
	std::vector<token> _tokens;
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif