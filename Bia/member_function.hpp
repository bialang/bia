#pragma once

#include "function.hpp"
#include "exception.hpp"
#include "disguised_caller.hpp"
#include "share.hpp"
#include "instance_holder.hpp"


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
	member_function(_Return(_Class::*_function)(_Args...)) noexcept : _data(_function, object::instance_holder<_Class>(machine::memory::allocation<_Class>(), false))
	{
	}
	member_function(const data_type & _data) noexcept : _data(_data)
	{
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const override
	{
		puts(typeid(_Return(_Class::*)(_Args...)).name());
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override
	{
		_destination->replace_this<member_function<_Return(_Class::*)(_Args...)>>(_data.get().first);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override
	{
		_destination->replace_this<member_function<_Return(_Class::*)(_Args...)>>(_data);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION clone(member * _destination) override
	{
		refer(_destination);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION execute(member * _destination) override
	{
		force::disguised_caller(_data.get().first, cast_instance(), _destination);
	}
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_count(member * _destination, void * _reserved, parameter_count _count...) override
	{
		force::va_list_wrapper _args;
		va_start(_args.args, _count);

		force::disguised_caller_count(_data.get().first, cast_instance(), _destination, _count, _args);

		va_end(_args.args);
	}
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_format(member * _destination, const char * _format, parameter_count _count...) override
	{
		force::va_list_wrapper _args;
		va_start(_args.args, _count);

		force::disguised_caller_format(_data.get().first, cast_instance(), _destination, _format, _count, _args);

		va_end(_args.args);
	}
	virtual void set_instance(const void * _instance, const std::type_info & _type) override
	{
		if (_type != typeid(_Class)) {
			throw exception::type_error(BIA_EM_INVALID_INSTANCE_TYPE);
		}

		/// TODO
		_data.get().second.~instance_holder();
		new(&_data.get().second) object::instance_holder<_Class>(*static_cast<const object::instance_holder<_Class>*>(_instance));
	}

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
	_Class * cast_instance()
	{
		auto _instance = _data.get().second.get();

		if (_instance) {
			return _instance;
		} else {
			throw exception::argument_error(BIA_EM_NULL_INSTANCE);
		}
	}
};

}
}
}