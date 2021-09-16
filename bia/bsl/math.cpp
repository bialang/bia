#include "modules.hpp"

#include <bia/config.hpp>
#include <bia/util/config.hpp>
#include <cstdlib>

void bia::bsl::math(internal::Typed_object& object)
{
	object.put_value(util::from_cstring("pi"), 3.14159265358979323846264);
	object.put_value(util::from_cstring("e"), 2.71828182845904523536028);
}
