#ifndef BIA_INTERNAL_TYPE_INTEGRAL_HPP_
#define BIA_INTERNAL_TYPE_INTEGRAL_HPP_

#include "definition.hpp"

#include <type_traits>

namespace bia {
namespace internal {
namespace type {

template<typename Type>
class Definition<Type, typename std::enable_if<std::is_integral<Type>::value>::type> : public Definition_base
{
public:
	static_assert(sizeof(Type) == 1 || sizeof(Type) == 2 || sizeof(Type) == 4 || sizeof(8),
	              "Size of given integral is not supported");

	bool is_assignable(const Definition_base* other) const noexcept override
	{
		return compare(other) == 0;
	}
	std::size_t size() const noexcept override
	{
		return Framer<Type>::size();
	}
	std::size_t alignment() const noexcept override
	{
		return Framer<Type>::alignment();
	}
	int flags() const noexcept override
	{
		return flag_arithmetic | (std::is_unsigned<Type>::value ? flag_unsigned : 0);
	}
	int compare(util::Not_null<const Definition_base*> other) const noexcept override
	{
		return util::compare(ordinal(), other->ordinal());
	}
	unsigned int ordinal() const noexcept override
	{
		// bool is considered a distinct type
		if (std::is_same<Type, bool>::value) {
			return 9;
		}
		switch (sizeof(Type)) {
		case 1: return 1 + (std::is_unsigned<Type>::value ? 4 : 0);
		case 2: return 2 + (std::is_unsigned<Type>::value ? 4 : 0);
		case 4: return 3 + (std::is_unsigned<Type>::value ? 4 : 0);
		case 8: return 4 + (std::is_unsigned<Type>::value ? 4 : 0);
		}
	}
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
