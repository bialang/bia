#include "modules.hpp"

#include <cstdlib>

void bia::bsl::os(internal::Typed_object& object)
{
	object.put_invokable(util::from_cstring("system"),
	                     [](const std::string& cmd) { return std::system(cmd.c_str()); });
	object.put_invokable(util::from_cstring("getenv"), [](const std::string& key) {
		char* value = std::getenv(key.c_str());
		return std::string{ value ? value : "" };
	});
}
