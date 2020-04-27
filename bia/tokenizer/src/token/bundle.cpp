#include "tokenizer/token/bundle.hpp"

#include <exception/bounds_error.hpp>
#include <util/gsl.hpp>

namespace bia {
namespace tokenizer {
namespace token {

std::size_t bundle::add(token token)
{
	_tokens.push_back(std::move(token));

	return _tokens.size() - 1;
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

token& bundle::at(std::size_t index)
{
	if (index >= _tokens.size()) {
		BIA_THROW(exception::bounds_error, "out of bounds");
	}

	return _tokens[index];
}

const token* bundle::begin() const noexcept
{
	return _tokens.begin().base();
}

const token* bundle::end() const noexcept
{
	return _tokens.end().base();
}

const token& bundle::first() const noexcept
{
	return _tokens.front();
}

const token& bundle::last() const noexcept
{
	return _tokens.back();
}

std::size_t bundle::size() const noexcept
{
	return _tokens.size();
}

} // namespace token
} // namespace tokenizer
} // namespace bia