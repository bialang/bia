#pragma once

#include <cstddef>

#include "function.hpp"
#include "share_def.hpp"


namespace bia
{
namespace framework
{
namespace executable
{

/**
 * @brief A lambda function member.
 *
 * @tparam Optional_count The amount of optional parameters.
 * @tparam _Lambda The lambda function.
*/
template<size_t Optional_count, typename Lambda>
class lambda_function final : public function
{
public:
	typedef utility::share<Lambda> data_type;

	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _lambda The lambda function.
	 *
	 * @throws See utility::share::share().
	*/
	explicit lambda_function(const Lambda & _lambda);
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _lambda The lambda function.
	 *
	 * @throws See utility::share::share().
	*/
	explicit lambda_function(Lambda && _lambda);
	/**
	 * Refer-Constructor.
	 *
	 * @since 3.65.134.742
	 * @date 1-Aug-18
	 *
	 * @param _lambda The lambda function.
	*/
	explicit lambda_function(const data_type & _data) noexcept;
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const override;
	virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION clone(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION execute(member * _destination) override;
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_count(member * _destination, void * _reserved, parameter_count_t _count, machine::stack * _stack) override;
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_format(member * _destination, const char * _format, parameter_count_t _count, machine::stack * _stack) override;
	virtual void set_instance(const void * _instance, const std::type_info & _type) override;

private:
	/** The lambda function. */
	data_type _data;
};

}
}
}