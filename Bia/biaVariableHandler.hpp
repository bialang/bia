#pragma once

#include <string>
#include <map>

#include "biaMember.hpp"


namespace bia
{
namespace machine
{

typedef std::string StringKey;
typedef std::map<StringKey, framework::BiaMember*> variable_index;

}
}