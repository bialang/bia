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
 * An output stream buffer for the @ref manager.
 *
 * @see @ref manager, @ref memory
 */
class streambuf : public std::streambuf
{
public:
	streambuf(const streambuf& copy) = delete;
	streambuf(streambuf&& move) noexcept;
	~streambuf();
	void finish();
	/**
	 * Checks whether this streambuf is valid.
	 *
	 * @returns `true` if valid, otherwise `false`
	 */
	bool valid() const noexcept;

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
};

} // namespace memory
} // namespace resource
} // namespace tokenizer
} // namespace bia

#endif