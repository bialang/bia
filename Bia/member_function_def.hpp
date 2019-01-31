#pragma once

#include "function.hpp"
#include "share_def.hpp"
#include "instance_holder_def.hpp"


namespace bia
{
namespace framework
{
namespace executable
{

template<typename _Class, typename _Return = void, typename... _Args>
class member_function;

/**
 * @brief A member function member.
 *
 * @tparam _Class The class of the function.
 * @tparam _Return The return type of the function.
 * @tparam _Args The arguemnt types of the function.
*/
template<typename _Class, typename _Return, typename... _Args>
class member_function<_Return(_Class::*)(_Args...)> final : public function
{
public:
	typedef utility::share<std::pair<_Return(_Class::*)(_Args...), object::instance_holder<_Class>>> data_type;

	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _function The member function address.
	*/
	member_function(_Return(_Class::*_function)(_Args...)) noexcept;
	member_function(const data_type & _data) noexcept;
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const override;
	virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION clone(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION execute(member * _destination) override;
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_count(member * _destination, void * _reserved, parameter_count _count, machine::stack * _stack) override;
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_format(member * _destination, const char * _format, parameter_count _count, machine::stack * _stack) override;
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
	_Class * cast_instance();
};

}
}
}