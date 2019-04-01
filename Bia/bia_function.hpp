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

	bia_function(data_t _data) noexcept;
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const override;
	virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION clone(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION execute(member * _destination) override;
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_count(member * _destination, void * _reserved, parameter_count_t _count, machine::stack * _stack) override;
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_format(member * _destination, const char * _format, parameter_count_t _count, machine::stack * _stack) override;
	virtual void set_instance(const void * _instance, const std::type_info & _type) override;

private:
	data_t _data;
};

}
}
}