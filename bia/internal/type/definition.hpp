#ifndef BIA_INTERNAL_TYPE_DEFINITION_HPP_
#define BIA_INTERNAL_TYPE_DEFINITION_HPP_

#include <bia/util/gsl.hpp>
#include <functional>
#include <cstddef>

namespace bia {
namespace internal {
namespace type {

class Definition
{
public:
	enum Flag
	{
		flag_truthable = 0x01
	};

	virtual ~Definition()                                              = default;
	virtual bool is_assignable(const Definition* other) const noexcept = 0;
	/// The required size in bytes to store a value of this type.
	virtual std::size_t size() const noexcept                                   = 0;
	/// The required alignment of this type. Over-aligned types are not allowed.
	virtual std::size_t alignment() const noexcept                              = 0;
	virtual int flags() const noexcept                                          = 0;
	virtual int compare(util::Not_null<const Definition*> other) const noexcept = 0;
	virtual unsigned int ordinal() const noexcept                               = 0;
};

} // namespace type
} // namespace internal
} // namespace bia

namespace std {

template<>
struct less<bia::internal::type::Definition*>
{
	bool operator()(bia::internal::type::Definition* left,
	                bia::internal::type::Definition* right) const noexcept
	{
		return left->compare(right) < 0;
	}
};

template<>
struct less<const bia::internal::type::Definition*>
{
	bool operator()(const bia::internal::type::Definition* left,
	                const bia::internal::type::Definition* right) const noexcept
	{
		return left->compare(right) < 0;
	}
};

} // namespace std

#endif
