#pragma once

#include <memory>

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
	virtual void execute(member * _instance, member * _destination) override
	{
		force::disguised_caller(&_Lambda::operator(), _lambda.get(), _destination);
	}

private:
	/** A pointer to a instance of the lambda function. */
	std::shared_ptr<_Lambda> _lambda;
};

}
}
}