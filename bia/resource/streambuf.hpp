#ifndef BIA_RESOURCE_STREAMBUF_HPP_
#define BIA_RESOURCE_STREAMBUF_HPP_

#include "info.hpp"
#include "view.hpp"

#include <bia/gc/memory/space.hpp>
#include <streambuf>
#include <bia/util/gsl.hpp>

namespace bia {
namespace resource {

class Manager;

/**
 * An output stream buffer for the @ref manager.
 *
 * @see @ref manager
 */
class Streambuf : public std::streambuf
{
public:
	/**
	 * Constructor.
	 *
	 * @param space the destination of the data
	 */
	Streambuf(util::Not_null<Manager*> manager);
	Streambuf(Streambuf&& move) noexcept;
	~Streambuf();
	View finish(type type);
	/**
	 * Checks whether this streambuf is valid.
	 *
	 * @returns `true` if valid, otherwise `false`
	 */
	bool valid() const noexcept;
	Streambuf& operator=(Streambuf&& move) noexcept;

protected:
	int_type sync() override;
	int_type overflow(int_type ch = traits_type::eof()) override;

private:
	/** if non-null the parent */
	Manager* _manager  = nullptr;
	/** the size when this streambuf was created */
	gc::memory::space::size_type _initial_size = 0;

	void _discard() noexcept;
};

} // namespace resource
} // namespace bia

#endif
