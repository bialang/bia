#include "biaCString.h"

namespace bia
{
namespace framework
{

void BiaCString::Undefine()
{
	//Destroy this
	this->~BiaCString();

	//Undefine
	new(this) BiaUndefined();
}

void BiaCString::Call(BiaMember *)
{
	throw exception::BadCallException("Invalid function call on native type.");
}

BiaMember * BiaCString::GetMember(const char * p_szName)
{
	return this;
	throw exception::SymbolException("Unkown member.");
}

void * BiaCString::GetNativeData(NATIVE_TYPE p_nativeType)
{
	switch (p_nativeType)
	{
	case NATIVE_TYPE::CONST_STRING:
		return &m_szString;
	default:
		throw exception::BadCastException("Native type is not supported.");
	}
}

void * BiaCString::GetData(const std::type_info & p_type, bool p_bConst)
{
	throw exception::BadCastException("Type is not supported.");
}

}
}