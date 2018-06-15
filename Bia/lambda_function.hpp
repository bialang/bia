#pragma once

#include <memory>
#include <cstdarg>

#include "function.hpp"
#include "exception.hpp"
#include "disguised_caller.hpp"


namespace bia
{
namespace framework
{
namespace executable
{

/**
 * @brief A lambda function member.
 *
 * @tparam _Lambda The lambda function.
*/
template<typename _Lambda>
class lambda_function final : public function
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _lambda The lambda function.
	*/
	explicit lambda_function(const _Lambda & _lambda) noexcept : _lambda(new _Lambda(_lambda))
	{
	}
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _lambda The lambda function.
	*/
	explicit lambda_function(_Lambda && _lambda) noexcept : _lambda(new _Lambda(std::move(_lambda)))
	{
	}
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _lambda The lambda function.
	*/
	explicit lambda_function(const std::shared_ptr<_Lambda> & _lambda) noexcept : _lambda(_lambda)
	{
	}
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _lambda The lambda function.
	*/
	explicit lambda_function(std::shared_ptr<_Lambda> && _lambda) noexcept : _lambda(std::move(_lambda))
	{
	}
	virtual void print() override
	{
		puts(typeid(&_Lambda::operator()).name());
	}
	virtual void clone(member * _destination) override
	{
		_destination->replace_this<lambda_function<_Lambda>>(_lambda);
	}
	virtual void execute(member * _destination) override
	{
		force::disguised_caller(&_Lambda::operator(), _lambda.get(), _destination);
	}
	virtual void execute_count(member * _destination, parameter_count _count...) override
	{
		std::va_list _args;
		va_start(_args, _count);

		force::disguised_caller_count(&_Lambda::operator(), _lambda.get(), _destination, _count, _args);

		va_end(_args);
	}
	virtual void execute_format(member * _destination, const char * _format, parameter_count _count...) override
	{
		std::va_list _args;
		va_start(_args, _count);

		force::disguised_caller_format(&_Lambda::operator(), _lambda.get(), _destination, _format, _count, _args);

		va_end(_args);
	}

private:
	/** A pointer to a instance of the lambda function. */
	std::shared_ptr<_Lambda> _lambda;
};

}
}
}