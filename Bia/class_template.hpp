#pragma once

#include "member.hpp"
#include "share.hpp"
#include "undefined_member.hpp"
#include "exception.hpp"
#include "string_manager.hpp"
#include "machine_context.hpp"
#include "allocator.hpp"
#include "initiator.hpp"
#include "object.hpp"
#include "member_map.hpp"
#include "guard.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename _Ty>
class class_template : public member
{
public:
	typedef utility::share<std::pair<member_map, machine::memory::allocator::allocation<force::initiator>>> data_type;

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
			auto _allocator = machine::machine_context::active_allocator();

			for (auto & _member : _data.get().first) {
				_allocator->destroy_blocks(_member.second);
			}
		}
	}
	virtual void undefine() noexcept override
	{
		replace_this<undefined_member>();
	}
	virtual void print() const override
	{
		printf("<class_template of %s>\n", typeid(_Ty).name());
	}
	virtual void copy(member * _destination) override
	{
	//	_destination->replace_this<class_template<_Ty>>(constructor_chain_wrapper<_Ty>(machine::machine_context::active_allocator(), *_data.get().first), true);
	}
	virtual void refer(member * _destination) override
	{
		_destination->replace_this<class_template<_Ty>>(_data);
	}
	virtual void clone(member * _destination) override
	{
		refer(_destination);
	}
	virtual void execute(member * _destination) override
	{
		instance_holder<_Ty> _instance(machine::memory::allocator::cast_allocation<_Ty>(_data.get().second->instantiate()), true);

		_destination->replace_this<object<_Ty>>(_instance, _data.get().first);
	}
	virtual void execute_count(member * _destination, parameter_count _count...) override
	{
		va_list _args;
		va_start(_args, _count);
		auto _guard = utility::make_guard(_args, [](va_list _args) {
			va_end(_args);
		});
		instance_holder<_Ty> _instance(machine::memory::allocator::cast_allocation<_Ty>(_data.get().second->instantiate_count(_count, _args)), true);

		_destination->replace_this<object<_Ty>>(_instance, _data.get().first);
	}
	virtual void execute_format(member * _destination, const char * _format, parameter_count _count...) override
	{
		va_list _args;
		va_start(_args, _count);
		auto _guard = utility::make_guard(_args, [](va_list _args) {
			va_end(_args);
		});
		instance_holder<_Ty> _instance(machine::memory::allocator::cast_allocation<_Ty>(_data.get().second->instantiate_format(_format, _count, _args)), true);

		_destination->replace_this<object<_Ty>>(_instance, _data.get().first);
	}
	virtual void operator_call(member * _destination, operator_type _operator, const member * _right) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual void operator_call_int32(member * _destination, operator_type _operator, int32_t _right) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual void operator_call_int64(member * _destination, operator_type _operator, int64_t _right) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual void operator_call_double(member * _destination, operator_type _operator, double _right) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	template<typename... _Args>
	void set_constructor()
	{
		auto _allocator = machine::machine_context::active_allocator();

		_allocator->destroy(_data.get().second);
		_data.get().second = _allocator->construct<force::initiator, force::real_initiator<_Ty, _Args...>>();
	}
	template<typename _Ty, typename... _Args>
	void emplace_member(machine::string_manager::name_type _name, _Args &&... _args)
	{
		auto & _map = _data.get().first;
		auto _result = _map.find(_name);

		// Create new
		if (_result == _map.end()) {
			_map.emplace(_name, machine::machine_context::active_allocator()->construct_blocks<member, _Ty>(1, std::forward<_Args>(_args)...));
		} else {
			_result->second->replace_this<_Ty>(std::forward<_Args>(_args)...);
		}
	virtual void object_member(member * _destination, machine::string_manager::name_type _name) override
	{
		_data.get().first.get(_name)->clone(_destination);
	}
	virtual int flags() const override
	{
		return F_NONE;
	}
	virtual int32_t test() const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual int32_t test_member(operator_type _operator, member * _right) const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual int32_t test_int32(operator_type _operator, int32_t _right) const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual int32_t test_int64(operator_type _operator, int64_t _right) const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual int32_t test_double(operator_type _operator, double _right) const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual int64_t to_int() const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual double to_double() const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}

protected:
	virtual void * native_data(native::NATIVE_TYPE _type) override
	{
		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}
	virtual const void * const_native_data(native::NATIVE_TYPE _type) const override
	{
		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}
	virtual void * data(const std::type_info & _type) override
	{
		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}
	virtual const void * const_data(const std::type_info & _type) const override
	{
		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}

private:
	data_type _data;
};

}
}
}