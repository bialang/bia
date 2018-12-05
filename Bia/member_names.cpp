#include "member_names.hpp"


namespace bia
{
namespace common
{

// Built-in functions
const char * common_names::print = "print";
const char * common_names::max = "max";
const char * common_names::min = "min";
const char * common_names::all = "all";
const char * common_names::any = "any";

// Common module names
const char * common_names::math = "math";
const char * common_names::regex = "regex";

// Common function names
const char * common_names::set = "set";
const char * common_names::get = "get";
const char * common_names::bin = "bin";
const char * common_names::hex = "hex";

// Special attributes
const char * common_names::attr_documentation = ":doc";
const char * common_names::attr_to_bool = ":bool";
const char * common_names::attr_to_int = ":int";
const char * common_names::attr_to_float = ":float";
const char * common_names::attr_to_string = ":str";
const char * common_names::attr_constructor = ":init";
const char * common_names::attr_destructor = ":finit";
const char * common_names::attr_less_than = ":lt";
const char * common_names::attr_less_equals = ":le";
const char * common_names::attr_greater_than = ":gt";
const char * common_names::attr_greater_equals = ":ge";
const char * common_names::attr_equals = ":e";
const char * common_names::attr_not_equals = ":ne";
const char * common_names::attr_spaceship = ":spc";
const char * common_names::attr_hash = ":hash";
const char * common_names::attr_call = ":call";
const char * common_names::attr_item_access = ":access";
const char * common_names::attr_increment = ":inc";
const char * common_names::attr_decrement = ":dec";

}
}