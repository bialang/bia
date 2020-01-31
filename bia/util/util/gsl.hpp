#ifndef BIA_UTIL_GSL_HPP_
#define BIA_UTIL_GSL_HPP_

#include "contract.hpp"

#include <utility>

namespace bia {
namespace util {

template<typename T>
class not_null
{
public:
	static_assert(std::is_assignable<T&, std::nullptr_t>::value, "invalid T");

	template<typename Ty>
	not_null(Ty&& value) : _value(std::forward<Ty>(value))
	{
		BIA_EXPECTS(_value != nullptr);
	}
	template<typename Ty>
	not_null(const not_null<Ty>& other) noexcept : not_null(other.get())
	{}
	not_null(std::nullptr_t) = delete;
	T& get()
	{
		BIA_ENSURES(_value != nullptr);

		return _value;
	}
	operator T&()
	{
		return get();
	}
	T operator->()
	{
		return get();
	}
	auto operator*() -> decltype(*get())
	{
		return *get();
	}

private:
	T _value;
};

} // namespace util
} // namespace bia

#endif