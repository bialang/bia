#pragma once

#include <cstddef>

#include "function.hpp"
#include "share_def.hpp"
#include "instance_holder_def.hpp"


namespace bia
{
namespace framework
{
namespace executable
{

template<size_t Optional_count, typename Class, typename Return = void, typename... Arguments>
class member_function;

/**
 * @brief A member function member.
 *
 * @tparam Optional_count The amount of optional parameters.
 * @tparam Class The class of the function.
 * @tparam Return The return type of the function.
 * @tparam Arguments The arguemnt types of the function.
*/
template<size_t Optional_count, typename Class, typename Return, typename... Arguments>
class member_function<Optional_count, Return(Class::*)(Arguments...)> final : public function
{
public:
	typedef utility::share<std::pair<Return(Class::*)(Arguments...), object::instance_holder<Class>>> data_type;

	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _function The member function address.
	*/
	member_function(Return(Class::*_function)(Arguments...)) noexcept;
	member_function(const data_type & _data) noexcept;
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const override;
	virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION clone(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION execute(member * _destination) override;
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_count(member * _destination, void * _reserved, parameter_count_t _count, machine::stack * _stack) override;
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_format(member * _destination, const char * _format, parameter_count_t _count, machine::stack * _stack) override;
	virtual void set_instance(const void * _instance, const std::type_info & _type) override;

private:
	data_type _data;

	/**
	 * Retrieves the needed instance from the member.
	 *
	 * @since 3.56.117.675
	 * @date 28-Feb-18
	 *
	 * @param [in] _instance The instance that should be casted.
	 *
	 * @throws exception::argument_error If the passed instance is null.
	 * @throws ... See member::cast().
	 *
	 * @return The instance.
	*/
	Class * cast_instance();
};

}
}
}