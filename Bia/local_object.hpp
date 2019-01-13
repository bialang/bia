#pragma once

#include <cstdint>
#include <utility>
#include <array>


namespace bia
{
namespace utility
{

/**
 * @brief Holds a member in a local buffer.
 *
 * Holds a member in a local buffer instead of the heap. Unlike @ref virtual_object a @ref local_object does neither care about what object it's holding nor about cleanup.
 *
 * @tparam Type The default type. Can be void.
 * @tparam Size The size of the internal space for the objects.
 *
 * @see @ref virtual_object
*/
template<typename Type, size_t Size = sizeof(Type)>
class local_object
{
public:
	local_object(const local_object & _copy) = delete;
	local_object(local_object && _move) = delete;

	/**
	 * Destroy the local object.
	 *
	 * @since 3.70.149.807
	 * @date 26-Dec-18
	 *
	 * @tparam Ty The type of the local object.
	 *
	 * @throws See the destructor of @a Ty.
	*/
	template<typename Ty = Type>
	void destroy()
	{
		get<Ty>()->~Ty();
	}
	/**
	 * Creates a new object of the type @a Ty.
	 *
	 * @remarks No cleanup of previous objects is performed. See destroy() for manual cleanup.
	 *
	 * @since 3.70.149.807
	 * @date 26-Dec-18
	 *
	 * @tparam Ty The type of the new object.
	 * @tparam Arguments The type of the arguments passed to the constructor.
	 *
	 * @param _arguments The arguments passed to the constructor of @a Ty.
	 *
	 * @throws See the constructor of @a Ty.
	 *
	 * @return The address to the newly created object.
	*/
	template<typename Ty = Type, typename... Arguments>
	Ty * create(Arguments &&... _arguements)
	{
		static_assert(sizeof(Ty) <= Size, "Object does not fit.");

		return new(_object_space.begin()) Ty(std::forward<Arguments>(_arguements)...);
	}
	/**
	 * Returns the address of the local object as @a Ty.
	 *
	 * @since 3.70.149.807
	 * @date 26-Dec-18
	 *
	 * @param Ty The supposed type of the local object.
	 *
	 * @return The address.
	*/
	template<typename Ty = Type>
	Ty * get() noexcept
	{
		static_assert(sizeof(Ty) <= Size, "Wrong object type.");

		return reinterpret_cast<Ty*>(_object_space.begin());
	}
	/**
	 * Returns the address of the local object as @a Ty.
	 *
	 * @since 3.70.149.807
	 * @date 26-Dec-18
	 *
	 * @param Ty The supposed type of the local object.
	 *
	 * @return The address.
	*/
	template<typename Ty = Type>
	const Ty * get() const noexcept
	{
		static_assert(sizeof(Ty) <= Size, "Wrong object type.");

		return reinterpret_cast<const Ty*>(_object_space.begin());
	}

private:
	/** The space which stores the local object. */
	std::array<int8_t, Size> _object_space;
};

}
}