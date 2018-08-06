#pragma once

#include <map>

#include "member.hpp"
#include "share.hpp"
#include "undefined_member.hpp"
#include "exception.hpp"
#include "string_manager.hpp"
#include "machine_context.hpp"
#include "allocator.hpp"


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
	typedef utility::share<std::map<machine::string_manager::name_type, member*>> data_type;

	/**
	 * Move-Constructor.
	 *
	 * @since 3.67.135.752
	 * @date 5-Aug-18
	 *
	 * @param [in,out] _object The object that should be set.
	 *
	 * @throws See constructor_chain().
	*/
	template<typename _T, typename A = typename std::enable_if<std::is_same<typename std::remove_cv<typename std::remove_reference<_T>::type>::type, typename std::remove_cv<typename std::remove_reference<_Ty>::type>::type>::value, int>::type>
	class_template(_T && _object) : _data(nullptr, false)
	{
		_data.get().first = constructor_chain_wrapper<_Ty>(machine::machine_context::active_allocator(), std::forward<_T>(_object));
		_data.get().second = true;
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
	 * Constructor.
	 *
	 * @since 3.67.135.752
	 * @date 5-Aug-18
	 *
	 * @param [in] _object The object address. This address must not be null.
	 * @param _owner true if this object is in charge of deallocating the object or not.
	*/
	class_template(_Ty * _object, bool _owner) noexcept : _data(nullptr, _owner)
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

			for (auto & _member : _data.get()) {
				_allocator->destroy_blocks<member>({ _member.second, 1 });
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
		_destination->replace_this<class_template<_Ty>>(constructor_chain_wrapper<_Ty>(machine::machine_context::active_allocator(), *_data.get().first), true);
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
		promote()->execute(_destination);
	}
	virtual void execute_count(member * _destination, parameter_count _count...) override
	{
		va_list _args;
		va_start(_args, _count);


		va_end(_args);
	}
	virtual void execute_format(member * _destination, const char * _format, parameter_count _count...) override
	{
		va_list _args;
		va_start(_args, _count);


		va_end(_args);
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
	virtual member * object_member(machine::string_manager::name_type _name) override
	{
		BIA_NOT_IMPLEMENTED;
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