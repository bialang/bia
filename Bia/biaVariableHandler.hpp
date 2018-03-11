#pragma once

#include <string>
#include <map>

#include "biaMember.hpp"
#include "biaAllocator.hpp"


namespace bia
{
namespace machine
{

typedef std::string StringKey;
typedef std::map<StringKey, BiaAllocator::Allocation<framework::BiaMember>> variable_index;

}
}