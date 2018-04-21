#pragma once

#include "member.hpp"


namespace bia
{
namespace framework
{

class undefined_member final : public member
{
public:
	virtual void undefine() noexcept override;
	virtual void print() const override;
	virtual void call(member * _instance, member * _destination) override;
	virtual bool is_const() const override;

protected:
	virtual void * get_native_data(native::NATIVE_TYPE _type) override;
	virtual const void * get_const_native_data(native::NATIVE_TYPE _type) const override;
	virtual void * get_data(const std::type_info & _type) override;
	virtual const void * get_const_data(const std::type_info & _type) const override;
};

}
}