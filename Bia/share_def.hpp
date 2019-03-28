#pragma once

#include <atomic>
#include <cstdint>


namespace bia
{
namespace utility
{

/**
 * @brief A shared object.
 *
 * A shared object with reference counting in only one thread.
 *
 * @tparam Type The type of the object.
*/
template<typename Type>
class share
{
public:
	/**
	 * Constructor.
	 *
	 * @remarks Creates the object inplace.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @tparam Arguments The arguments needed to create the underlying object.
	 *
	 * @param _arguments The arguments.
	 *
	 * @throws See the constructor of @a Type.
	 * @throws See machine::memory::allocator::construct().
	*/
	template<typename... Arguments>
	share(Arguments &&... _arguments);
	/**
	 * Copy-Constructor.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @param _copy The copy.
	*/
	share(const share & _copy) noexcept;
	/**
	 * Move-Constructor.
	 *
	 * @since 3.73.150.817
	 * @date 3-Mar-19
	 *
	 * @param [in,out] _move The object that should be moved.
	*/
	share(share && _move) noexcept;
	/**
	 * Destructor.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @throws See the destructor of @a Type.
	 * @throws See machine::memory::allocator::destroy().
	*/
	~share();
	/**
	 * Returns the referred object.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @return The object.
	*/
	Type & get() noexcept;
	/**
	 * Returns the referred object.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @return The object.
	*/
	const Type & get() const noexcept;
	/**
	 * The arrow access operator.
	 *
	 * @since 3.69.144.799
	 * @date 5-Dec-18
	 *
	 * @return The data of the share.
	*/
	Type * operator->() noexcept;
	/**
	 * The arrow access operator.
	 *
	 * @since 3.69.144.799
	 * @date 5-Dec-18
	 *
	 * @return The data of the share.
	*/
	const Type * operator->() const noexcept;
	/**
	 * Copies the right hand value.
	 *
	 * @since 3.73.150.817
	 * @date 3-Mar-19
	 *
	 * @param _copy The right hand value.
	 *
	 * @throws See ~share().
	 *
	 * @return Returns *this.
	*/
	share & operator=(const share & _copy);
	/**
	 * Moves the right hand value.
	 *
	 * @since 3.73.150.817
	 * @date 3-Mar-19
	 *
	 * @param [in,out] _move The right hand value.
	 *
	 * @throws See ~share().
	 *
	 * @return Returns *this.
	*/
	share & operator=(share && _move);
	template<typename... Arguments>
	static share factory_make(uint8_t _extra_size, Arguments &&... _arguments);

private:
	struct data
	{
		uint8_t extra_size;
		std::atomic_uint32_t reference_count;
	};

	/** The data pointer. */
	data * _data;

	template<typename... Arguments>
	share(uint8_t _extra_size, Arguments &&... _arguments);
	template<typename... Arguments>
	void create(uint8_t _extra_size, Arguments &&... _arguments);
	constexpr static size_t data_size();
};

}
}
