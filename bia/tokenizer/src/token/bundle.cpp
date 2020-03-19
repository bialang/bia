#include "tokenizer/token/bundle.hpp"

#include <util/gsl.hpp>

namespace bia {
namespace tokenizer {
namespace token {

void bundle::add(token token)
{
	_tokens.push_back(std::move(token));
}

void bundle::clear()
{
	_tokens.clear();
}

bundle::state_type bundle::save()
{
	return _tokens.size();
}

void bundle::restore(state_type state)
{
	BIA_EXPECTS(state <= _tokens.size());

	_tokens.resize(state);
}

const token* bundle::begin() const
{
	return _tokens.begin().base();
}

const token* bundle::end() const
{
	return _tokens.end().base();
}

} // namespace token
} // namespace tokenizer
} // namespace bia