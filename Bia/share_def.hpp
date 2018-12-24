#pragma once

#include <atomic>
#include <cstdint>
#include <utility>


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
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @tparam Arguments The arguments needed to create the underlying object.
	 *
	 * @param _arguments The arguments.
	 *
	 * @throws See machine::memory::allocator::construct().
	*/
	template<typename... Arguments>
	share(Arguments &&... _arguments);
	/**
	 * Constructor.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @param _copy The copy.
	*/
	share(const share & _copy) noexcept;
	share(share && _move) = delete;
	/**
	 * Destructor.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
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

private:
	typedef std::pair<int8_t[sizeof(Type)], std::atomic_size_t> data;

	data * _data;
};

}
}
