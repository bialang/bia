#pragma once

#include "member.hpp"


namespace bia
{
namespace framework
{

class undefined_member final : public member
{
public:
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION undefine() noexcept override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION print() const override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION clone(member * _destination) override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION execute(member * _destination) override;
	BIA_EXPORT virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_count(member * _destination, void * _reserved, parameter_count _count...) override;
	BIA_EXPORT virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_format(member * _destination, const char * _format, parameter_count _count...) override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION operator_call(member * _destination, operator_type _operator, const member * _right) override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int32(member * _destination, operator_type _operator, int32_t _right) override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int64(member * _destination, operator_type _operator, int64_t _right) override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_double(member * _destination, operator_type _operator, double _right) override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION object_member(member * _destination, machine::string_manager::name_type _name) override;
	BIA_EXPORT virtual void set_instance(const void * _instance, const std::type_info & _type) override;
	BIA_EXPORT virtual int flags() const override;
	BIA_EXPORT virtual int32_t BIA_MEMBER_CALLING_CONVENTION test() const override;
	BIA_EXPORT virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_member(operator_type _operator, member * _right) const override;
	BIA_EXPORT virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int32(operator_type _operator, int32_t _right) const override;
	BIA_EXPORT virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int64(operator_type _operator, int64_t _right) const override;
	BIA_EXPORT virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_double(operator_type _operator, double _right) const override;
	BIA_EXPORT virtual int64_t to_int() const override;
	BIA_EXPORT virtual double to_double() const override;

protected:
	BIA_EXPORT virtual void * native_data(native::NATIVE_TYPE _type) override;
	BIA_EXPORT virtual const void * const_native_data(native::NATIVE_TYPE _type) const override;
	BIA_EXPORT virtual void * data(const std::type_info & _type) override;
	BIA_EXPORT virtual const void * const_data(const std::type_info & _type) const override;
};

}
}