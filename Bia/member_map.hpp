#pragma once

#include <map>

#include "member.hpp"
#include "allocator.hpp"
#include "string_manager.hpp"


namespace bia
{
namespace framework
{
namespace object
{

typedef std::map<machine::string_manager::name_type, machine::memory::allocator::allocation<member>> member_map;

}
}
}