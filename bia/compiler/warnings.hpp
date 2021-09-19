#ifndef BIA_COMPILER_WARNINGS_HPP_
#define BIA_COMPILER_WARNINGS_HPP_

#include <bia/error/bia_error.hpp>
#include <bia/error/code.hpp>
#include <bia/tokenizer/token/token.hpp>
#include <bia/util/gsl.hpp>
#include <cstdint>
#include <vector>

namespace bia {
namespace compiler {

class Warnings
{
public:
	void add(error::Code code, util::Span<const tokenizer::token::Token*> tokens)
	{
		BIA_EXPECTS(!tokens.empty());
		_warnings.push_back({ code, { tokens.front().range.start, tokens.back().range.end } });
	}
	void add(error::Code code, error::Bia_range range)
	{
		_warnings.push_back({ code, range });
	}
	std::size_t size() const noexcept
	{
		return _warnings.size();
	}
	std::vector<error::Bia>::const_iterator begin() const noexcept
	{
		return _warnings.begin();
	}
	std::vector<error::Bia>::const_iterator end() const noexcept
	{
		return _warnings.end();
	}

private:
	std::vector<error::Bia> _warnings;
};

} // namespace compiler
} // namespace bia

#endif
