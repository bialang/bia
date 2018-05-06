#pragma once

#include "member.hpp"


namespace bia
{
namespace framework
{

class undefined_member final : public member
{
public:
	~undefined_member() noexcept = default;
	virtual void undefine() noexcept override;
	virtual void print() const override;
	virtual void clone(member * _destination) override;
	virtual void execute(member * _instance, member * _destination) override;
	virtual void execute_count(member * _instance, member * _destination, parameter_count _count...) override;
	virtual void execute_format(member * _instance, member * _destination, const char * _format, parameter_count _count...) override;
	virtual void operator_call_int32(member * _destination, operator_type _operator, int32_t _right) override;
	virtual void operator_call_int64(member * _destination, operator_type _operator, int64_t _right) override;
	virtual void operator_call_double(member * _destination, operator_type _operator, double _right) override;
	virtual bool is_const() const override;
	virtual int32_t test() const override;
	virtual int32_t test_int32(operator_type _operator, int32_t _right) const override;
	virtual int32_t test_int64(operator_type _operator, int64_t _right) const override;
	virtual int32_t test_double(operator_type _operator, double _right) const override;

protected:
	virtual void * get_native_data(native::NATIVE_TYPE _type) override;
	virtual const void * get_const_native_data(native::NATIVE_TYPE _type) const override;
	virtual void * get_data(const std::type_info & _type) override;
	virtual const void * get_const_data(const std::type_info & _type) const override;
};

}
}