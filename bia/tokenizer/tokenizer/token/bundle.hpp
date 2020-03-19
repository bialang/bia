#ifndef BIA_TOKENIZER_TOKEN_BUNDLE_HPP_
#define BIA_TOKENIZER_TOKEN_BUNDLE_HPP_

#include "receiver.hpp"

#include <util/gsl.hpp>
#include <vector>

namespace bia {
namespace tokenizer {
namespace token {

class bundle
{
public:
	typedef std::size_t state_type;

	void add(token::token token);
	void clear();
	state_type save();
	void restore(state_type state);
	const token::token* begin() const;
	const token::token* end() const;

private:
	std::vector<token::token> _tokens;
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif