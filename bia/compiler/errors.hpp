#ifndef BIA_COMPILER_ERRORS_HPP_
#define BIA_COMPILER_ERRORS_HPP_

#include <bia/error/bia_error.hpp>
#include <bia/error/code.hpp>
#include <bia/tokenizer/token/token.hpp>
#include <bia/util/gsl.hpp>
#include <vector>

namespace bia {
namespace compiler {

class Errors
{
public:
	void add_error(error::Code code, util::Span<const tokenizer::token::Token*> tokens)
	{
		BIA_EXPECTS(!tokens.empty());
		_errors.push_back({ code, { tokens.front().range.start, tokens.back().range.end } });
	}
	void reset_fail() noexcept
	{
		_last_check = _errors.size();
	}
	std::size_t size() const noexcept
	{
		return _errors.size();
	}
	bool has_failed() const noexcept
	{
		return !_errors.empty() && _last_check != _errors.size();
	}
	std::vector<error::Bia>::const_iterator begin() const noexcept
	{
		return _errors.begin();
	}
	std::vector<error::Bia>::const_iterator end() const noexcept
	{
		return _errors.end();
	}

private:
	std::vector<error::Bia> _errors;
	std::size_t _last_check = 0;
};

} // namespace compiler
} // namespace bia

#endif
