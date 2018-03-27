#pragma once

#include "biaMember.hpp"


namespace bia
{
namespace framework
{

void MemberCreator(BiaMember * p_pDestination);

template<typename T>
void MemberCreator(BiaMember * p_pDestination, T && p_value);

}
}