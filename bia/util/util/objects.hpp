#pragma once

#include <exception/nullpointer_exception.hpp>

namespace bia {
namespace util {

class objects
{
public:
	template<typename T>
	static T* require_non_null(T* ptr)
	{
		if (!ptr) {
			BIA_THROW(exception::nullpointer_exception, u"null object");
		}

		return ptr;
	}
};

} // namespace util
} // namespace bia