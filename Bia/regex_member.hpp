#pragma once

#include "native_variable.hpp"
#include "share_def.hpp"
#include "regex.hpp"


namespace bia
{
namespace framework
{
namespace native
{

class regex_member : public native_variable
{
public:
	typedef utility::share<detail::regex> data_t;

	regex_member(const data_t & _data) noexcept;
	~regex_member();
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const override;
	virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION clone(member * _destination) override; virtual void BIA_MEMBER_CALLING_CONVENTION operator_call(member * _destination, operator_t _operator, const member * _right) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int32(member * _destination, operator_t _operator, int32_t _right) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int64(member * _destination, operator_t _operator, int64_t _right) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_big_int(member * _destination, operator_t _operator, const detail::big_int * _right) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_double(member * _destination, operator_t _operator, double _right) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION object_member(member * _destination, machine::name_manager::name_t _name) override;
	virtual int flags() const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test() const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_member(operator_t _operator, member * _right) const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int32(operator_t _operator, int32_t _right) const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int64(operator_t _operator, int64_t _right) const override;
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_double(operator_t _operator, double _right) const override;
	virtual int64_t to_int() const override;
	virtual double to_double() const override;
	virtual const char * to_cstring(utility::buffer_builder * _builder) const override;

private:
	data_t _data;
};

}
}
}