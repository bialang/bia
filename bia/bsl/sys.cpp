#include "modules.hpp"

#include <bia/config.hpp>
#include <bia/util/config.hpp>
#include <cstdlib>

void bia::bsl::sys(internal::Typed_object& object)
{
	object.put_invokable(util::from_cstring("abort"), &std::abort);
	object.put_invokable(util::from_cstring("exit"), &std::exit);
	object.put_invokable(util::from_cstring("quick_exit"), &std::quick_exit);

	object.put_value(
	  util::from_cstring("byteorder"), std::string {
#if BIA_BIA_ENDIAN
		  "big"
#else
		  "little"
#endif
	  });
	object.put_value(util::from_cstring("int_size"), static_cast<std::ptrdiff_t>(sizeof(std::ptrdiff_t) * 8));
	object.put_value(util::from_cstring("version"), std::string{ BIA_LANG_VERSION });
}
