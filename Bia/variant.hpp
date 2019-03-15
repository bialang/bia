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
class variant
{
public:
	typedef uint16_t id_t;

	/**
	 * Constructor.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	*/
	variant() noexcept
	{
		static_assert(sizeof...(Types) + 1 <= std::numeric_limits<id_t>::max(), "Too many variants.");

		_object_id = 0;
	}
	variant(const variant & _copy) = delete;
	variant(variant && _move) = delete;
	/**
	 * Destructor.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @throws See destroy().
	*/
	~variant()
	{
		destroy();
	}
	/**
	 * Constructs a new variant. The old object will be destroyed.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @tparam Type The new variant type.
	 * @tparam Arguments The argument types for the variant.
	 *
	 * @param [in,out] _arguments The arguments for the new variant.
	 *
	 * @throws See destroy().
	 * @throws See constructor of @a Type.
	*/
	template<typename Type, typename... Arguments>
	void reconstruct(Arguments &&... _arguments)
	{
		destroy();

		_object_id = object_id<Type, Default, Types...>();
		new(_object_space) Type(std::forward<Arguments>(_arguments)...);
	}
	/**
	 * Destroys the currently active variant, if any.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @throws See do_destroy().
	*/
	void destroy()
	{
		if (_object_id) {
			do_destroy<Default, Types...>(1);

			_object_id = 0;
		}
	}
	/**
	 * Checks whether the type is in the variant type list.
	 *
	 * @since 3.75.150.820
	 * @date 15-Mar-19
	 *
	 * @tparam Type The type that should be checked.
	 *
	 * @return true if the test succeeded, otherwise false.
	*/
	template<typename Type>
	constexpr static bool has_type() noexcept
	{
		return do_has_type<Type, Default, Types...>();
	}
	/**
	 * Checks whether the variant is empty or not.
	 *
	 * @since 3.75.150.820
	 * @date 15-Mar-19
	 *
	 * @return true if the variant is empty, otherwise false.
	*/
	bool empty() const noexcept
	{
		return _object_id == 0;
	}
	/**
	 * Checks whether a values is being stored or not.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @return true if the variant holds a value, otherwise false.
	*/
	operator bool() const noexcept
	{
		return !empty();
	}
	/**
	 * Returns the id of the current value.
	 *
	 * @remarks The id are numbered starting with 1 to N. If 0 is returned, the variant is empty.
	 *
	 * @since 3.75.150.820
	 * @date 15-Mar-19
	 *
	 * @return The current id.
	*/
	id_t id() const noexcept
	{
		return _object_id;
	}
	/**
	 * Returns the default value for the '->' operator.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @return See get<Default>().
	*/
	Default * operator->() noexcept
	{
		return get<Default>();
	}
	/**
	 * Returns the default value for the '->' operator.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @return See get<Default>().
	*/
	const Default * operator->() const noexcept
	{
		return get<Default>();
	}
	/**
	 * Casts the variant to @a Type.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @tparam Type The desired type of @a Types.
	 *
	 * @return A pointer to the value as @a Type if the cast succeeded, otherwise null.
	*/
	template<typename Type>
	Type * get() noexcept
	{
		return _object_id ? do_get<Type, Default, Types...>(1) : nullptr;
	}
	/**
	 * Casts the variant to @a Type.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @tparam Type The desired type of @a Types.
	 *
	 * @return A pointer to the value as @a Type if the cast succeeded, otherwise null.
	*/
	template<typename Type>
	const Type * get() const noexcept
	{
		return _object_id ? do_get<Type, Default, Types...>(1) : nullptr;
	}

private:
	/** The max size of the virtual object space in bytes. */
	constexpr static auto max_size = max_sizeof<Default, Types...>();
	/** The virtual object space. */
	intptr_t _object_space[max_size / sizeof(intptr_t) + (max_size % sizeof(intptr_t) ? 1 : 0)];
	/** If non-zero the currently active object, otherwise no object is active. */
	id_t _object_id;

	/**
	 * Destroys the current variant with the appropiate destructor.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @tparam Type The last variant type.
	 *
	 * @param _id The current object id counter.
	 *
	 * @throws See destructor of @a Type.
	*/
	template<typename Type>
	void do_destroy(id_t _id)
	{
		reinterpret_cast<Type*>(_object_space)->~Type();
	}
	/**
	 * Destroys the current variant with the appropiate destructor.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @tparam Type The current variant type.
	 * @tparam Rest The rest of the variant types.
	 *
	 * @param _id The current object id counter.
	 *
	 * @throws See destructor of the current type.
	*/
	template<typename Type, typename... Rest>
	typename std::enable_if<sizeof...(Rest) != 0>::type do_destroy(id_t _id)
	{
		if (_object_id == _id) {
			reinterpret_cast<Type*>(_object_space)->~Type();
		} else {
			do_destroy<Rest...>(_id + 1);
		}
	}
	/**
	 * Returns false.
	 *
	 * @since 3.75.150.820
	 * @date 15-Mar-19
	 *
	 * @return Returns false.
	*/
	template<typename Type>
	constexpr static bool do_has_type() noexcept
	{
		return false;
	}
	/**
	 * Checks whether the @a Type is valid.
	 *
	 * @since 3.75.150.820
	 * @date 15-Mar-19
	 *
	 * @return true if the test succeeded, otherwise false.
	*/
	template<typename Type, typename Other, typename... Rest>
	constexpr static bool do_has_type() noexcept
	{
		return std::is_same<Type, Other>::value || do_has_type<Type, Rest...>();
	}
	/**
	 * Returns the object id of @a Type.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @tparam Type The desired type.
	 * @tparam Other The last type of @a Types.
	 *
	 * @return 1.
	*/
	template<typename Type, typename Other>
	constexpr static id_t object_id() noexcept
	{
		static_assert(std::is_same<Type, Other>::value, "Invalid variant type.");

		return 1;
	}
	/**
	 * Returns the object id of @a Type.
	 *
	 * @since 3.68.140.791
	 * @date 10-Nov-18
	 *
	 * @tparam Type The desired type.
	 * @tparam Other A type of @a Types.
	 * @tparam Rest The rest of @a Types.
	 *
	 * @return 1.
	*/
	template<typename Type, typename Other, typename... Rest>
	constexpr static typename std::enable_if<std::is_same<Type, Other>::value && sizeof...(Rest), id_t>::type object_id() noexcept
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
	 * @tparam Other A type of @a Types.
	 * @tparam Rest The rest of @a Types.
	 *
	 * @return The object id.
	*/
	template<typename Type, typename Other, typename... Rest>
	constexpr static typename std::enable_if<!std::is_same<Type, Other>::value && sizeof...(Rest), id_t>::type object_id() noexcept
	{
		return object_id<Type, Rest...>() + 1;
	}
	/**
	 * Returns the object as @a Type.
	 *
	 * @since 3.75.150.820
	 * @date 15-Mar-19
	 *
	 * @return The object.
	*/
	template<typename Type, typename Other>
	typename std::enable_if<std::is_base_of<Type, Other>::value, Type*>::type cast() noexcept
	{
		return static_cast<Type*>(reinterpret_cast<Other*>(_object_space));
	}
	/**
	 * Returns the object as @a Type.
	 *
	 * @since 3.75.150.820
	 * @date 15-Mar-19
	 *
	 * @return The object.
	*/
	template<typename Type, typename Other>
	typename std::enable_if<std::is_base_of<Type, Other>::value, const Type*>::type cast() const noexcept
	{
		return static_cast<const Type*>(reinterpret_cast<const Other*>(_object_space));
	}
	/**
	 * Returns null.
	 *
	 * @since 3.75.150.820
	 * @date 15-Mar-19
	 *
	 * @return Returns null.
	*/
	template<typename Type, typename Other>
	typename std::enable_if<!std::is_base_of<Type, Other>::value, Type*>::type cast() const noexcept
	{
		return nullptr;
	}
	/**
	 * Returns null.
	 *
	 * @since 3.75.150.820
	 * @date 15-Mar-19
	 *
	 * @return Returns null.
	*/
	template<typename Type>
	Type * do_get(id_t _id) const noexcept
	{
		return nullptr;
	}
	/**
	 * Returns the object as the valid type.
	 *
	 * @since 3.75.150.820
	 * @date 15-Mar-19
	 *
	 * @return A pointer to the object, otherwise null.
	*/
	template<typename Type, typename Other, typename... Rest>
	Type * do_get(id_t _id) noexcept
	{
		if (_object_id == _id) {
			return cast<Type, Other>();
		}

		return do_get<Type, Rest...>(_id + 1);
	}
	/**
	 * Returns the object as the valid type.
	 *
	 * @since 3.75.150.820
	 * @date 15-Mar-19
	 *
	 * @return A pointer to the object, otherwise null.
	*/
	template<typename Type, typename Other, typename... Rest>
	const Type * do_get(id_t _id) const noexcept
	{
		if (_object_id == _id) {
			return cast<Type, Other>();
		}

		return do_get<Type, Rest...>(_id + 1);
	}
};

}
}