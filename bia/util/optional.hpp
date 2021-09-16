#ifndef BIA_UTIL_OPTIONAL_HPP_
#define BIA_UTIL_OPTIONAL_HPP_

#include <bia/error/exception.hpp>
#include <type_traits>
#include <utility>

namespace bia {
namespace util {

template<typename Type>
class Optional
{
public:
	Optional() noexcept = default;
	Optional(Type&& value)
	{
		emplace(std::move(value));
	}
	Optional(const Type& value)
	{
		emplace(value);
	}
	Optional(const Optional& copy)
	{
		if (copy.has_value()) {
			emplace(copy.get());
		}
	}
	Optional(Optional&& move)
	{
		if (move.has_value()) {
			emplace(std::move(move.get()));
			move.clear();
		}
	}
	~Optional() noexcept
	{
		clear();
	}
	void clear() noexcept
	{
		if (has_value()) {
			reinterpret_cast<Type*>(&_data)->~Type();
			_empty = true;
		}
	}
	template<typename... Arguments>
	Type& emplace(Arguments&&... arguments)
	{
		clear();
		const auto ptr = new (&_data) Type{ std::forward<Arguments>(arguments)... };
		_empty         = false;
		return *ptr;
	}
	bool has_value() const noexcept
	{
		return !_empty;
	}
	bool empty() const noexcept
	{
		return _empty;
	}
	operator bool() const noexcept
	{
		return has_value();
	}
	Type& get()
	{
		if (empty()) {
			BIA_THROW(error::Code::empty_optional);
		}
		return *reinterpret_cast<Type*>(&_data);
	}
	const Type& get() const
	{
		if (empty()) {
			BIA_THROW(error::Code::empty_optional);
		}
		return *reinterpret_cast<const Type*>(&_data);
	}
	Type* operator->()
	{
		return &get();
	}
	const Type* operator->() const
	{
		return &get();
	}
	Type& operator*()
	{
		return get();
	}
	const Type& operator*() const
	{
		return get();
	}
	Optional& operator=(const Optional& copy)
	{
		clear();
		if (copy.has_value()) {
			emplace(copy.get());
		}
		return *this;
	}
	Optional& operator=(Optional&& move)
	{
		clear();
		if (move.has_value()) {
			emplace(std::move(move.get()));
			move.clear();
		}
		return *this;
	}

private:
	/// The current value.
	typename std::aligned_storage<sizeof(Type), alignof(Type)>::type _data;
	bool _empty = true;
};

} // namespace util
} // namespace bia

#endif
