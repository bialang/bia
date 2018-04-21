#include "undefined_member.hpp"
#include "exception.hpp"

#define BIA_UNDEFINED_ERROR throw exception::symbol_error(BIA_EM_UNDEFINED_MEMBER)


namespace bia
{
namespace framework
{

void undefined_member::undefine() noexcept
{
}

void undefined_member::print() const
{
	BIA_UNDEFINED_ERROR;
}

void undefined_member::call(member * _instance, member * _destination)
{
	BIA_UNDEFINED_ERROR;
}

bool undefined_member::is_const() const
{
	BIA_UNDEFINED_ERROR;
}

void * undefined_member::get_native_data(native::NATIVE_TYPE _type)
{
	BIA_UNDEFINED_ERROR;
}

const void * undefined_member::get_const_native_data(native::NATIVE_TYPE _type) const
{
	BIA_UNDEFINED_ERROR;
}

void * undefined_member::get_data(const std::type_info & _type)
{
	BIA_UNDEFINED_ERROR;
}

const void * undefined_member::get_const_data(const std::type_info & _type) const
{
	BIA_UNDEFINED_ERROR;
}

}
}