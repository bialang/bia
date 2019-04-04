#pragma once

#include "function.hpp"
#include "share_def.hpp"
#include "function_holder.hpp"


namespace bia
{
namespace framework
{
namespace executable
{

class bia_function : public function
{
public:
	typedef utility::share<detail::function_holder> data_t;

	bia_function(const data_t & _data) noexcept;
	~bia_function();
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const override;
	virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION clone(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION execute(machine::stack * _stack, member * _destination) override;
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_count(machine::stack * _stack, member * _destination, void * _reserved, parameter_count_t _count) override;
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_format(machine::stack * _stack, member * _destination, const char * _format, parameter_count_t _count) override;
	virtual void set_instance(const void * _instance, const std::type_info & _type) override;

private:
	data_t _data;
};

}
}
}