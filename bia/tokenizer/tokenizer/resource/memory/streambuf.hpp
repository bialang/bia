#ifndef BIA_TOKENIZER_RESOURCE_MEMORY_STREAMBUF_HPP_
#define BIA_TOKENIZER_RESOURCE_MEMORY_STREAMBUF_HPP_

#include "../size.hpp"
#include "memory.hpp"

#include <streambuf>
#include <util/gsl.hpp>

namespace bia {
namespace tokenizer {
namespace resource {

class manager;

namespace memory {

/**
 * An output streambuffer for the @ref manager.
 *
 * @see @ref manager, @ref memory
 */
class streambuf : public std::streambuf
{
public:
	streambuf(const streambuf& copy) = delete;
	streambuf(streambuf&& move) noexcept;
	~streambuf();
	/**
	 * Closes this streambuf.
	 *
	 * @pre `valid() == true`
	 * @post `valid() == false`
	 *
	 * @param discard if `true` discards the memory sequence and returns an invalid memory object
	 * @returns the memory object
	 */
	class memory close(bool discard);
	/**
	 * Checks whether this streambuf is valid.
	 *
	 * @returns `true` if valid, otherwise `false`
	 */
	bool valid() const noexcept;
	streambuf& operator=(streambuf&& move) = default;

protected:
	int_type sync() override;
	int_type overflow(int_type ch = traits_type::eof()) override;

private:
	friend manager;

	/** if non-null the parent */
	manager* _manager = nullptr;
	/** the current size pointer */
	size* _size = nullptr;
	/** the last size pointer */
	size* _last_size = nullptr;

	/**
	 * Constructor.
	 *
	 * @param manager the parent resouce manager
	 * @throw exception::memory_error if no memory could be allocated
	 */
	streambuf(util::not_null<manager*> manager);
	/**
	 * Updates the current size pointer and the old size.
	 *
	 * @post `_size == s`
	 *
	 * @param[in] s the new pointer
	 */
	void _update_size(size* s) noexcept;
};

} // namespace memory
} // namespace resource
} // namespace tokenizer
} // namespace bia

#endif