#pragma once

#include <cstdint>
#include <limits>
#include <utility>
#include <type_traits>

#include "max.hpp"


namespace bia
{
namespace utility
{

/**
 * @brief Holds one object of different type.
 *
 * Holds up to one object of the specified types in @a Types. The object is stored in local memory.
 *
 * @tparam Default The default return type.
 * @tparam Types The valid types.
 *
 * @see @ref local_object
*/
template<typename Default, typename... Types>
class virtual_object
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	*/
	virtual_object() noexcept
	{
		static_assert(sizeof...(Types) <= std::numeric_limits<uint8_t>::max(), "Too many virtual objects.");
		static_assert(sizeof(Default) <= max_size, "Default type exceeds virtual space.");

		_object_id = 0;
	}
	virtual_object(const virtual_object & _copy) = delete;
	virtual_object(virtual_object && _move) = delete;
	/**
	 * Destructor.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @throws See destroy().
	*/
	~virtual_object()
	{
		destroy();
	}
	/**
	 * Constructs a new virtual object. The old object will be destroyed.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @tparam Type The new virtual object type.
	 * @tparam Arguments The argument types for the virtual object.
	 *
	 * @param [in,out] _arguments The arguments for the new virtual object.
	 *
	 * @throws See destroy().
	 * @throws See constructor of @a Type.
	*/
	template<typename Type, typename... Arguments>
	void reconstruct(Arguments &&... _arguments)
	{
		destroy();

		new(_object_space) Type(std::forward<Arguments>(_arguments)...);

		_object_id = object_id<Type, Types...>();
	}
	/**
	 * Destroys the currently active virtual object, if any.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @throws See destructor of the current type.
	*/
	void destroy()
	{
		if (_object_id) {
			destroy<Types...>(0);

			_object_id = 0;
		}
	}
	/**
	 * Checks whether a virtual object is active.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @return true if a virtual object is active, otherwise false.
	*/
	operator bool() const noexcept
	{
		return _object_id != 0;
	}
	/**
	 * Returns the default object for the '->' operator.
	 *
	 * @warning Neither type compatibility checking, nor object checking is performed.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @return A pointer to the virtual object as the default type.
	*/
	Default * operator->() noexcept
	{
		return get<Default>();
	}
	/**
	 * Returns the default object for the '->' operator.
	 *
	 * @warning Neither type compatibility checking, nor object checking is performed.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @return A pointer to the virtual object as the default type.
	*/
	const Default * operator->() const noexcept
	{
		return get<Default>();
	}
	/**
	 * Casts the virtual object to @a Type.
	 *
	 * @warning Neither type compatibility checking, nor object checking is performed.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @tparam Type The desired type of @a Types.
	 *
	 * @return A pointer to the virtual object as @a Type.
	*/
	template<typename Type>
	Type * get() noexcept
	{
		valid_get_type<Type>();

		return reinterpret_cast<Type*>(_object_space);
	}
	/**
	 * Casts the virtual object to @a Type.
	 *
	 * @warning Neither type compatibility checking, nor object checking is performed.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @tparam Type The desired type of @a Types.
	 *
	 * @return A pointer to the virtual object as @a Type.
	*/
	template<typename Type>
	const Type * get() const noexcept
	{
		valid_get_type<Type>();

		return reinterpret_cast<const Type*>(_object_space);
	}

private:
	/** The max size of the virtual object space in bytes. */
	constexpr static auto max_size = max_sizeof<Types...>();
	/** If non-zero the currently active object, otherwise no object is active. */
	uint8_t _object_id;
	/** The virtual object space. */
	int8_t _object_space[max_size];

	/**
	 * Checks whether @a Type is in @a Types.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @tparam Type The desired get type.
	*/
	template<typename Type>
	static typename std::enable_if<std::is_same<Type, Default>::value>::type valid_get_type() noexcept
	{
	}
	/**
	 * Checks whether @a Type is in @a Types.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @tparam Type The desired get type.
	*/
	template<typename Type>
	static typename std::enable_if<!std::is_same<Type, Default>::value>::type valid_get_type() noexcept
	{
		object_id<Type, Types...>();
	}
	/**
	 * Destroys the current virtual object with the appropiate destructor.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @param _current_id The curren object id counter.
	 *
	 * @throws See destructor of @a Type.
	*/
	template<typename Type>
	void destroy(uint8_t _current_id)
	{
		reinterpret_cast<Type*>(_object_space)->~Type();
	}
	/**
	 * Destroys the current virtual object with the appropiate destructor.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @param _current_id The curren object id counter.
	 *
	 * @throws See destructor of the current type.
	*/
	template<typename Type, typename... Tys>
	typename std::enable_if<(sizeof...(Tys) > 0)>::type destroy(uint8_t _current_id)
	{
		if (_object_id == ++_current_id) {
			reinterpret_cast<Type*>(_object_space)->~Type();
		} else {
			destroy<Tys...>(_current_id);
		}
	}
	/**
	 * Returns the object id of @a Type.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @tparam Type The desired type.
	 * @tparam Ty The last type of @a Types.
	 *
	 * @return The object id.
	*/
	template<typename Type, typename Ty>
	constexpr static uint8_t object_id() noexcept
	{
		static_assert(std::is_same<Type, Ty>::value, "Invalid type.");

		return 1;
	}
	/**
	 * Returns the object id of @a Type.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @tparam Type The desired type.
	 * @tparam Ty A type of @a Types.
	 * @tparam Tys The rest of @a Types.
	 *
	 * @return The object id.
	*/
	template<typename Type, typename Ty, typename... Tys>
	constexpr static typename std::enable_if<(std::is_same<Type, Ty>::value && sizeof...(Tys) > 0), uint8_t>::type object_id() noexcept
	{
		return 1;
	}
	/**
	 * Returns the object id of @a Type.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @tparam Type The desired type.
	 * @tparam Ty A type of @a Types.
	 * @tparam Tys The rest of @a Types.
	 *
	 * @return The object id.
	*/
	template<typename Type, typename Ty, typename... Tys>
	constexpr static typename std::enable_if<(!std::is_same<Type, Ty>::value && sizeof...(Tys) > 0), uint8_t>::type object_id() noexcept
	{
		return object_id<Type, Tys...>() + 1;
	}
};

}
}