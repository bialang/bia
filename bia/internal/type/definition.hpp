#ifndef BIA_INTERNAL_TYPE_DEFINITION_HPP_
#define BIA_INTERNAL_TYPE_DEFINITION_HPP_

#include "framer.hpp"

#include <bia/util/algorithm.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/type_traits/is_frameable.hpp>
#include <bia/util/type_traits/type_index.hpp>
#include <cstddef>
#include <functional>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <vector>

namespace bia {
namespace internal {
namespace type {

/// The pure interface of a definition.
class Definition_base
{
public:
	enum Flag
	{
		flag_truthable  = 0x01,
		flag_arithmetic = 0x02,
		/// The definition is an unsigned integer.
		flag_unsigned = 0x04,
		flag_vararg   = 0x08,
	};

	virtual ~Definition_base()                                              = default;
	virtual bool is_assignable(const Definition_base* other) const noexcept = 0;
	/// The required size in bytes to store a value of this type.
	virtual std::size_t size() const noexcept = 0;
	/// The required alignment of this type. Over-aligned types are not allowed.
	virtual std::size_t alignment() const noexcept                                   = 0;
	virtual int flags() const noexcept                                               = 0;
	virtual int compare(util::Not_null<const Definition_base*> other) const noexcept = 0;
	virtual unsigned int ordinal() const noexcept                                    = 0;
};

template<typename Type, typename = void>
class Definition;

class Definition_real_base : virtual public Definition_base
{
public:
	virtual const std::type_index& type_index() const noexcept = 0;
};

/// Helper class which has a provides an overridable default implementation of the definition interface.
template<typename Type>
class Definition_helper : public Definition_real_base
{
public:
	static_assert(util::type_traits::Is_frameable<Type>::value, "Type must be frameable");
	static_assert(!std::is_integral<Type>::value, "Type must not be an integral");

	bool is_assignable(const Definition_base* other) const noexcept override
	{
		return dynamic_cast<const Definition<Type>*>(other);
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
		return (std::is_arithmetic<Type>::value ? flag_arithmetic : 0);
	}
	int compare(util::Not_null<const Definition_base*> other) const noexcept override
	{
		const int n = util::compare(ordinal(), other->ordinal());
		return n == 0
		         ? util::compare(_index, dynamic_cast<const Definition_real_base*>(other.get())->type_index())
		         : n;
	}
	unsigned int ordinal() const noexcept override
	{
		using Indexer = util::type_traits::type_index<Type, bool, char, signed char, unsigned char, wchar_t,
#if defined(__cpp_char8_t)
		                                              char8_t,
#endif
		                                              char16_t, char32_t, short int, unsigned short int, int,
		                                              unsigned int, long int, unsigned long int, long long int,
		                                              unsigned long long int, float, double, long double>;
		return Indexer::value == util::npos ? 99 : Indexer::value + 1;
	}
	const std::type_index& type_index() const noexcept override
	{
		return _index;
	}

private:
	std::type_index _index{ typeid(Type) };
};

// Default case
template<typename Type, typename>
class Definition : public Definition_helper<Type>
{};

} // namespace type
} // namespace internal
} // namespace bia

namespace std {

template<>
struct less<bia::internal::type::Definition_base*>
{
	bool operator()(bia::internal::type::Definition_base* left,
	                bia::internal::type::Definition_base* right) const noexcept
	{
		return left->compare(right) < 0;
	}
};

template<>
struct less<const bia::internal::type::Definition_base*>
{
	bool operator()(const bia::internal::type::Definition_base* left,
	                const bia::internal::type::Definition_base* right) const noexcept
	{
		return left->compare(right) < 0;
	}
};

} // namespace std

#endif
