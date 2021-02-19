#ifndef BIA_RESOURCE_STREAMBUF_HPP_
#define BIA_RESOURCE_STREAMBUF_HPP_

#include "info.hpp"
#include "view.hpp"

#include <bia/memory/space.hpp>
#include <streambuf>
#include <bia/util/gsl.hpp>

namespace bia {
namespace resource {

class Manager;

/// An output stream buffer for the @ref manager.
class Streambuf : public std::streambuf
{
public:
	Streambuf(util::Not_null<Manager*> manager);
	Streambuf(const Streambuf& copy) = delete;
	Streambuf(Streambuf&& move) noexcept;
	~Streambuf();
	View finish(Type type);
	bool valid() const noexcept;
	Streambuf& operator=(const Streambuf& copy) = delete;
	Streambuf& operator=(Streambuf&& move) noexcept;

protected:
	int_type sync() override;
	int_type overflow(int_type ch = traits_type::eof()) override;

private:
	/// The parent if valid.
	Manager* _manager  = nullptr;
	/// The size when this streambuf was created.
	memory::space::size_type _initial_size = 0;

	void _discard() noexcept;
};

} // namespace resource
} // namespace bia

#endif
