#pragma once

#include <cstdint>
#include <limits>
#include <utility>
#include <type_traits>


namespace bia
{
namespace utility
{

template<typename... Types>
class virtual_object
{
public:
	virtual_object()
	{
		static_assert(sizeof...(Types) <= std::numeric_limits<uint8_t>::max(), "Too many virtual objects.");

		_object_id = 0;
	}
	~virtual_object()
	{
		deinit();
	}
	template<typename Type, typename... Arguments>
	void reinit(Arguments &&... _arguments)
	{
		deinit();

		new(_object_space) Type(std::forward<Arguments>(_arguments)...);

		_object_id = object_id<Type, Types...>();
	}
	void deinit()
	{
		if (_object_id) {
			deinit<Types...>(0);

			_object_id = 0;
		}
	}
	template<typename Type>
	Type * operator->() noexcept
	{
		static_assert(sizeof(Type) <= max_size<Types...>(), "sizeof Type exceeds maximum.");

		return reinterpret_cast<Type*>(_object_space);
	}
	template<typename Type>
	const Type * operator->() const noexcept
	{
		static_assert(sizeof(Type) <= max_size<Types...>(), "sizeof Type exceeds maximum.");

		return reinterpret_cast<const Type*>(_object_space);
	}

private:
	uint8_t _object_id;
	int8_t _object_space[max_size<Types...>()];

	template<typename Type>
	void deinit(uint8_t _current_id)
	{
		reinterpret_cast<Type*>(_object_space)->~Type();
	}
	template<typename Type, typename... Tys>
	void deinit(uint8_t _current_id)
	{
		if (_object_id == ++_current_id) {
			reinterpret_cast<Type*>(_object_space)->~Type();
		} else {
			deinit<Tys...>(_current_id);
		}
	}
	template<typename Type, typename Ty>
	constexpr static uint8_t object_id() noexcept
	{
		static_assert(std::is_same<Type, Ty>::value, "Invalid type");

		return 1;
	}
	template<typename Type, typename Ty, typename... Tys>
	constexpr static uint8_t object_id() noexcept
	{
		return std::is_same<Type, Ty>::value ? 1 : object_id<Type, Tys...>() + 1;
	}
	template<typename Type>
	constexpr static size_t max_size() noexcept
	{
		return sizeof(Type);
	}
	template<typename Type, typename... Tys>
	constexpr static size_t max_size() noexcept
	{
		return sizeof(Type) > max_size<Tys...>() ? sizeof(Type) : max_size<Tys...>();
	}
};

}
}