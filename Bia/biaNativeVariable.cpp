#include "biaNativeVariable.hpp"
#include "biaUndefined.hpp"
#include "biaException.hpp"


namespace bia
{
namespace framework
{
namespace native
{

void BiaNativeVariable::Undefine()
{
	ReplaceObject<BiaUndefined>();
}

void BiaNativeVariable::Call(BiaMember *, BiaMember *)
{
	throw exception::BadCallException("Invalid function call on native type.");
}

void BiaNativeVariable::CallCount(BiaMember *, BiaMember *, parameter_count, ...)
{
	throw exception::BadCallException("Invalid function call on native type.");
}

void BiaNativeVariable::CallFormat(BiaMember *, BiaMember *, parameter_count, const char *, ...)
{
	throw exception::BadCallException("Invalid function call on native type.");
}

void BiaNativeVariable::Instantiate(BiaMember *)
{
	throw exception::BadCallException("Invalid instantiation call on native type.");
}

void BiaNativeVariable::InstantiateCount(BiaMember *, parameter_count, ...)
{
	throw exception::BadCallException("Invalid instantiation call on native type.");
}

void BiaNativeVariable::InstantiateFormat(BiaMember *, parameter_count, const char *, ...)
{
	throw exception::BadCallException("Invalid instantiation call on native type.");
}

bool BiaNativeVariable::IsType(const std::type_info & p_type) const
{
	return false;
}

BiaMember * BiaNativeVariable::GetMember(const char * p_szName)
{
	return reinterpret_cast<BiaMember*>(reinterpret_cast<int>(p_szName) ^ reinterpret_cast<int>(p_szName) >> 32);
	//throw exception::SymbolException("Unkown member.");
}

void * BiaNativeVariable::GetData(const std::type_info & p_type, bool p_bConst)
{
	throw exception::BadCastException("Type is not supported.");
}

}
}
}