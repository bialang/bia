#ifndef BIA_RESOURCE_STREAMBUF_HPP_
#define BIA_RESOURCE_STREAMBUF_HPP_

#include "info.hpp"
#include "view.hpp"

#include <bia/gc/memory/space.hpp>
#include <streambuf>
#include <bia/util/gsl.hpp>

namespace bia {
namespace resource {

class manager;

/**
 * An output stream buffer for the @ref manager.
 *
 * @see @ref manager
 */
class streambuf : public std::streambuf
{
public:
	/**
	 * Constructor.
	 *
	 * @param space the destination of the data
	 */
	streambuf(util::not_null<manager*> manager);
	streambuf(streambuf&& move) noexcept;
	~streambuf();
	view finish(type type);
	/**
	 * Checks whether this streambuf is valid.
	 *
	 * @returns `true` if valid, otherwise `false`
	 */
	bool valid() const noexcept;
	streambuf& operator=(streambuf&& move) noexcept;

protected:
	int_type sync() override;
	int_type overflow(int_type ch = traits_type::eof()) override;

private:
	/** if non-null the parent */
	manager* _manager  = nullptr;
	/** the size when this streambuf was created */
	gc::memory::space::size_type _initial_size = 0;

	void _discard() noexcept;
};

} // namespace resource
} // namespace bia

#endif
