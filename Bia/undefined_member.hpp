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
	virtual void execute(BIA_PO_0_1_2(member * _destination, member * _instance)) override;
	virtual bool is_const() const override;
	virtual int32_t test() const override;

protected:
	virtual void * get_native_data(native::NATIVE_TYPE _type) override;
	virtual const void * get_const_native_data(native::NATIVE_TYPE _type) const override;
	virtual void * get_data(const std::type_info & _type) override;
	virtual const void * get_const_data(const std::type_info & _type) const override;
};

}
}