#include "undefined_member.hpp"

#define BIA_UNDEFINED_ERROR throw exception::symbol_error("Undefined symbol.")


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

}
}