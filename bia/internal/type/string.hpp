#ifndef BIA_INTERNAL_TYPE_STRING_HPP_
#define BIA_INTERNAL_TYPE_STRING_HPP_

#include "object.hpp"

#include <bia/memory/gc/types.hpp>

namespace bia {
namespace internal {
namespace type {

// class String : public Object
// {
// public:
// 	String()
// 	{
// 		static Integer i{ Integer::Size::u64, false };
// 		add_member(util::from_cstring("length"), &i);
// 	}
// 	bool is_assignable(const Definition_base* other) const noexcept override
// 	{
// 		return dynamic_cast<const String*>(other);
// 	}
// 	std::size_t size() const noexcept override
// 	{
// 		return sizeof(memory::gc::GC_able<memory::gc::String*>);
// 	}
// 	std::size_t alignment() const noexcept override
// 	{
// 		return alignof(memory::gc::GC_able<memory::gc::String*>);
// 	}
// 	int flags() const noexcept override
// 	{
// 		return 0;
// 	}
// 	int compare(util::Not_null<const Definition_base*> other) const noexcept override
// 	{
// 		return util::compare(ordinal(), other->ordinal());
// 	}
// 	unsigned int ordinal() const noexcept override
// 	{
// 		return 4;
// 	}
// };

} // namespace type
} // namespace internal
} // namespace bia

#endif
