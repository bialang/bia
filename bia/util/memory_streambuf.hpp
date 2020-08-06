#ifndef BIA_UTIL_MEMORY_STREAMBUF_HPP_
#define BIA_UTIL_MEMORY_STREAMBUF_HPP_

#include "gsl.hpp"

#include <streambuf>

namespace bia {
namespace util {

class memory_streambuf : public std::streambuf
{
public:
	memory_streambuf(span<const byte*> buffer) noexcept
	{
		setg(reinterpret_cast<char*>(const_cast<byte*>(buffer.begin())),
		     reinterpret_cast<char*>(const_cast<byte*>(buffer.begin())),
		     reinterpret_cast<char*>(const_cast<byte*>(buffer.end())));
	}
};

} // namespace util
} // namespace bia

#endif
