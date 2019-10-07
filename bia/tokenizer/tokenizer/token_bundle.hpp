#pragma once

#include "token.hpp"

#include <cstddef>
#include <vector>

namespace bia {
namespace tokenizer {

class token_bundle
{
public:
	void add(const token& tk)
	{
		tokens.push_back(tk);
	}
	void reset(std::size_t mk)
	{
		// check mark

		tokens.erase(tokens.begin() + mk, tokens.end());
	}
	token* begin()
	{
		return tokens.data();
	}
	const token* end() const
	{
		return tokens.data() + tokens.size();
	}
	std::size_t mark() const noexcept
	{
		return tokens.size();
	}

private:
	std::vector<token> tokens;
};

} // namespace tokenizer
} // namespace bia