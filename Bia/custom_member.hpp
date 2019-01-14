#pragma once

#include <cstdio>
#include <utility>

#include "member.hpp"
#include "undefined_member.hpp"
#include "max_member_size.hpp"
#include "share.hpp"


namespace bia
{
namespace framework
{

template<typename Data>
class custom_member;

template<>
class custom_member<void> : public member
{
public:
	virtual void BIA_MEMBER_CALLING_CONVENTION undefine() override
	{
		replace_this<undefined_member>();
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const override
	{
		printf("<%s at %p>\n", typeid(*this).name(), this);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION clone(member * _destination) override
	{
		refer(_destination);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION execute(member * _destination) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_EXECUTE);
	}
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_count(member * _destination, void * _reserved, parameter_count _count...) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_EXECUTE);
	}
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_format(member * _destination, const char * _format, parameter_count _count...) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_EXECUTE);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call(member * _destination, operator_type _operator, const member * _right) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int32(member * _destination, operator_type _operator, int32_t _right) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int64(member * _destination, operator_type _operator, int64_t _right) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_double(member * _destination, operator_type _operator, double _right) override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_OPERATION);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION object_member(member * _destination, machine::string_manager::name_t _name) override
	{
		throw exception::symbol_error(BIA_EM_UNDEFINED_MEMBER);
	}
	virtual void set_instance(const void * _instance, const std::type_info & _type) override
	{
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test() const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_TEST);
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_member(operator_type _operator, member * _right) const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_TEST);
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int32(operator_type _operator, int32_t _right) const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_TEST);
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int64(operator_type _operator, int64_t _right) const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_TEST);
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_double(operator_type _operator, double _right) const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_TEST);
	}
	virtual int64_t to_int() const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_TYPE);
	}
	virtual double to_double() const override
	{
		throw exception::execution_error(BIA_EM_UNSUPPORTED_TYPE);
	}
};

template<typename Data>
class custom_member : public custom_member<void>
{
public:
	typedef utility::share<Data> data_type;

	/**
	 * Constructor.
	 *
	 * @since 3.68.140.789
	 * @date 20-Sep-18
	 *
	 * @param _arguments The arguments needed to construct the specified data.
	*/
	template<typename... Arguments>
	custom_member(Arguments &&... _arguments) : _data(std::forward<Arguments>(_arguments)...)
	{
	}
	/**
	 * Refer-Constructor.
	 *
	 * @since 3.68.140.789
	 * @date 20-Sep-18
	 *
	 * @param _data The data of the referred object.
	*/
	custom_member(const data_type & _data) noexcept : _data(_data)
	{
	}

protected:
	data_type _data;
};



template<typename Custom_member>
inline void test_custom_member() noexcept
{
	static_assert(sizeof(custom_member<int>) <= max_member_size && sizeof(custom_member<void>) <= max_member_size, "Custom member implementation error.");
	static_assert(sizeof(Custom_member) <= max_member_size, "Custom member exceeds max member size.");
}

}
}
