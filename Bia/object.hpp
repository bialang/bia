#pragma once

#include <type_traits>
#include <cstdarg>
#include <utility>

#include "member.hpp"
#include "allocator.hpp"
#include "undefined_member.hpp"
#include "share.hpp"
#include "type_traits.hpp"
#include "constructor_chain.hpp"
#include "machine_context.hpp"
#include "member_map.hpp"
#include "instance_holder.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename _Ty>
class object : public member
{
public:
	typedef utility::share<std::pair<instance_holder<_Ty>, member_map>> data_type;

	/**
	 * Constructor.
	 *
	 * @remarks A new share will be created for the object.
	 *
	 * @since 3.67.135.753
	 * @date 7-Aug-18
	 *
	 * @param _instance The instance.
	 * @param _members The known members.
	*/
	object(const instance_holder<_Ty> & _instance, const member_map & _members) noexcept : _data(_instance, _members)
	{
	}
	/**
	 * Refer-Constructor.
	 *
	 * @since 3.67.135.753
	 * @date 7-Aug-18
	 *
	 * @param _data The data.
	*/
	object(const data_type & _data) noexcept : _data(_data)
	{
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION undefine() noexcept override
	{
		replace_this<undefined_member>();
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const override
	{
		printf("<%s at %p>\n", typeid(_Ty).name(), this);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override
	{
		instance_holder<_Ty> _instance(constructor_chain_wrapper<_Ty>(machine::machine_context::active_allocator(), *_data.get().first.get()), true);

		_destination->replace_this<object<_Ty>>(_instance, _data.get().second);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override
	{
		_destination->replace_this<object<_Ty>>(_data);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION clone(member * _destination) override
	{
		refer(_destination);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION execute(member * _destination) override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_count(member * _destination, void * _reserved, parameter_count _count...) override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_format(member * _destination, const char * _format, parameter_count _count...) override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call(member * _destination, operator_type _operator, const member * _right) override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int32(member * _destination, operator_type _operator, int32_t _right) override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int64(member * _destination, operator_type _operator, int64_t _right) override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_double(member * _destination, operator_type _operator, double _right) override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION object_member(member * _destination, machine::string_manager::name_type _name) override
	{
		// Get instance, because this could be _destination
		auto _instance = _data.get().first;

		_data.get().second.get(_name)->copy(_destination);

		_destination->set_instance(&_instance, typeid(_Ty));
	}
	virtual void set_instance(const void * _instance, const std::type_info & _type) override
	{
	}
	virtual int flags() const override
	{
		return F_NONE;
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test() const override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_member(operator_type _operator, member * _right) const override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int32(operator_type _operator, int32_t _right) const override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int64(operator_type _operator, int64_t _right) const override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_double(operator_type _operator, double _right) const override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual int64_t to_int() const override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual double to_double() const override
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
		if (!std::is_const<_Ty>::value) {
			if (typeid(_Ty) == _type) {
				return const_cast<typename std::remove_cv<_Ty>::type*>(static_cast<_Ty*>(_data.get().first.get()));
			} else if (typeid(_Ty*) == _type) {
				return &_data.get().first.get();
			}
		}

		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}
	virtual const void * const_data(const std::type_info & _type) const override
	{
		if (typeid(_Ty) == _type) {
			return _data.get().first.get();
		} else if (typeid(_Ty*) == _type) {
			return &_data.get().first.get();
		}

		throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
	}

private:
	data_type _data;
};

}
}
}