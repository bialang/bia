#ifndef BIA_UTIL_MEMORY_STREAMBUF_HPP_
#define BIA_UTIL_MEMORY_STREAMBUF_HPP_

#include "gsl.hpp"

#include <streambuf>

namespace bia {
namespace util {

class Memory_streambuf : public std::streambuf
{
public:
	Memory_streambuf(Span<const Byte*> buffer) noexcept
	{
		setg(reinterpret_cast<char*>(const_cast<Byte*>(buffer.begin())),
		     reinterpret_cast<char*>(const_cast<Byte*>(buffer.begin())),
		     reinterpret_cast<char*>(const_cast<Byte*>(buffer.end())));
	}

protected:
	pos_type seekpos(pos_type position, std::ios_base::openmode which) override
	{
		return seekoff(position, std::ios_base::beg, which);
	}
	pos_type seekoff(off_type offset, std::ios_base::seekdir direction, std::ios_base::openmode which) override
	{
		if (which != std::ios_base::in) {
			return pos_type(off_type(-1));
		}

		char* ptr = nullptr;

		switch (direction) {
		case std::ios_base::beg: ptr = eback() + offset; break;
		case std::ios_base::cur: ptr = gptr() + offset; break;
		case std::ios_base::end: ptr = egptr() + offset; break;
		default: return pos_type(off_type(-1));
		}

		// check bounds
		if (ptr < eback() || ptr > egptr()) {
			return pos_type(off_type(-1));
		}

		setg(eback(), ptr, egptr());
		return pos_type(off_type(ptr - eback()));
	}
};

} // namespace util
} // namespace bia

#endif
