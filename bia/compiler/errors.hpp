#ifndef BIA_COMPILER_ERRORS_HPP_
#define BIA_COMPILER_ERRORS_HPP_

#include <bia/error/code.hpp>
#include <bia/tokenizer/location.hpp>
#include <bia/tokenizer/token/token.hpp>
#include <vector>

namespace bia {
namespace compiler {

struct Error
{
	std::error_code code;
	tokenizer::Range range;
};

class Errors
{
public:
	void add_error(error::Code code, const tokenizer::token::Token& token)
	{
		_errors.push_back({ code, token.range });
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
	std::vector<Error>::const_iterator begin() const noexcept
	{
		return _errors.begin();
	}
	std::vector<Error>::const_iterator end() const noexcept
	{
		return _errors.end();
	}

private:
	std::vector<Error> _errors;
	std::size_t _last_check = 0;
};

} // namespace compiler
} // namespace bia

#endif
