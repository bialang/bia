#pragma once

#include <utility>
#include <type_traits>


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
 * @tparam Destroy If true, the held object will be destroyed at the end of the lifetime of this object (even if it was not initialized).
 *
 * @see @ref virtual_object
*/
template<typename Type, size_t Size = sizeof(Type), size_t Alignment = alignof(Type)>
class local_object
{
public:
	local_object() noexcept
	{
		_initialized = false;
	}
	local_object(const local_object & _copy) = delete;
	local_object(local_object && _move) = delete;
	/**
	 * Destructor.
	 *
	 * @since 3.73.150.816
	 * @date 24-Feb-19
	 *
	 * @throws See destroy().
	*/
	~local_object()
	{
			destroy();
	}
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
		if (_initialized) {
			get<Ty>()->~Ty();

			_initialized = false;
		}
	}
	bool initialized() const noexcept
	{
		return _initialized;
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
	 * @throws See destroy().
	 *
	 * @return The address to the newly created object.
	*/
	template<typename Ty = Type, typename... Arguments>
	Ty * create(Arguments &&... _arguements)
	{
		static_assert(sizeof(Ty) <= Size, "Object does not fit.");

		destroy();

		auto _ptr = new(&_object_space) Ty(std::forward<Arguments>(_arguements)...);

		_initialized = true;

		return _ptr;
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

		return reinterpret_cast<Ty*>(&_object_space);
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

		return reinterpret_cast<const Ty*>(&_object_space);
	}
	operator bool() const noexcept
	{
		return initialized();
	}

private:
	/** The space which stores the local object. */
	typename std::aligned_storage<Size, Alignment>::type _object_space;
	/** If true the object was initialized, otherwise not. */
	bool _initialized;
};

}
}