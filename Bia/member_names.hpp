#pragma once

#include <algorithm>

#include "config.hpp"


namespace bia
{
namespace common
{

class common_names
{
public:
	// Built-in functions
	static const char * print;
	static const char * max;
	static const char * min;
	static const char * all;
	static const char * any;
	static const char * count;

	// Common module names
	static const char * math;
	static const char * regex;

	// Common function names
	static const char * set;
	static const char * get;
	static const char * bin;
	static const char * hex;
	static const char * replace;

	// Special attributes
	static const char * attr_documentation;
	static const char * attr_to_bool;
	static const char * attr_to_int;
	static const char * attr_to_float;
	static const char * attr_to_string;
	static const char * attr_constructor;
	static const char * attr_destructor;
	static const char * attr_less_than;
	static const char * attr_less_equals;
	static const char * attr_greater_than;
	static const char * attr_greater_equals;
	static const char * attr_equals;
	static const char * attr_not_equals;
	static const char * attr_spaceship;
	static const char * attr_hash;
	static const char * attr_call;
	static const char * attr_item_access;
	static const char * attr_increment;
	static const char * attr_decrement;

	static void sort_list(const char ** _list, const char ** _end_list)
	{
		std::sort(_list, _end_list);
	}
	static bool in_list(const char ** _list, const char ** _end_list, const char * _name)
	{
		return std::binary_search(_list, _end_list, _name);
	}
};

}
}
