#pragma once

#include "object_variable.hpp"
#include "share.hpp"
#include "exception.hpp"
#include "string_manager.hpp"
#include "machine_context.hpp"
#include "initiator.hpp"
#include "object.hpp"
#include "member_map.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename _Ty>
class class_template : public object_variable
{
public:
	typedef utility::share<std::pair<member_map, machine::memory::allocation<force::initiator>>> data_type;

	class_template()
	{
		_data.get().second = machine::machine_context::active_allocator()->construct<force::initiator>();
	}
	/**
	 * Refer-Constructor.
	 *
	 * @since 3.67.135.752
	 * @date 5-Aug-18
	 *
	 * @param _data The data.
	*/
	class_template(const data_type & _data) noexcept : _data(_data)
	{
	}
	/**
	 * Destructor.
	 *
	 * @since 3.67.135.752
	 * @date 5-Aug-18
	 *
	 * @throws See machine::memory::allocator::destroy().
	*/
	~class_template()
	{
		if (_data.only_owner()) {
			machine::machine_context::active_allocator()->destroy(_data.get().second);
		}
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const override
	{
		printf("<class_template of %s>\n", typeid(_Ty).name());
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override
	{
		_destination->replace_this<class_template<_Ty>>(_data);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION execute(member * _destination) override
	{
		instance_holder<_Ty> _instance(machine::memory::cast_allocation<_Ty>(_data.get().second->instantiate()), true);

		_destination->replace_this<object<_Ty>>(_instance, _data.get().first);
	}
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_count(member * _destination, void * _reserved, parameter_count _count...) override
	{
		force::va_list_wrapper _args;
		va_start(_args.args, _count);
		auto _instance_created = false;

		try {
			instance_holder<_Ty> _instance(machine::memory::cast_allocation<_Ty>(_data.get().second->instantiate_count(_count, _args)), true);
			_destination->replace_this<object<_Ty>>(_instance, _data.get().first);

			_instance_created = true;
			va_end(_args.args);

			_destination->replace_this<object<_Ty>>(_instance, _data.get().first);
		} catch (...) {
			if (!_instance_created) {
				va_end(_args.args);
			}

			throw;
		}
	}
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_format(member * _destination, const char * _format, parameter_count _count...) override
	{
		force::va_list_wrapper _args;
		va_start(_args.args, _count);
		auto _instance_created = false;

		try {
			instance_holder<_Ty> _instance(machine::memory::cast_allocation<_Ty>(_data.get().second->instantiate_format(_format, _count, _args)), true);

			_instance_created = true;
			va_end(_args.args);

			_destination->replace_this<object<_Ty>>(_instance, _data.get().first);
		} catch (...) {
			if (!_instance_created) {
				va_end(_args.args);
			}

			throw;
		}
	}
	template<typename... _Args>
	void set_constructor()
	{
		auto _allocator = machine::machine_context::active_allocator();

		_allocator->destroy(_data.get().second);
		_data.get().second = _allocator->construct<force::initiator, force::real_initiator<_Ty, _Args...>>();
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION object_member(member * _destination, member_map::name_type _name) override
	{
		_data.get().first.get(_name)->refer(_destination);
	}
	virtual int flags() const override
	{
		return F_NONE;
	}
	/**
	 * Returns the member map.
	 *
	 * @since 3.68.140.788
	 * @date 16-Sep-18
	 *
	 * @return A reference to the member map.
	*/
	member_map & members() noexcept
	{
		return _data.get().first;
	}

private:
	data_type _data;
};

}
}
}
