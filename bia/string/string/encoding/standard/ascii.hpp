#ifndef BIA_STRING_ENCODING_STANDARD_ASCII_HPP_
#define BIA_STRING_ENCODING_STANDARD_ASCII_HPP_

#include "../encoder.hpp"

#include <exception/char_encoding_exception.hpp>

namespace bia {
namespace string {
namespace encoding {
namespace standard {

/**
 * The standard encoder for ASCII without any state. This class is thread safe.
 */
class ascii final : public encoder
{
public:
	virtual void put(std::ostream& output, code_point_type cp) const override
	{
		// invalid ascii
		if (cp & ~0x7f) {
		}

		output.put(static_cast<char>(cp));
	}
	virtual code_point_type read(std::istream& input) const override
	{
		auto cp = input.get();

		// no more input
		if (!input) {
			return eof;
		}

		// invalid ascii
		if (cp & ~0x7f) {
		}

		return cp;
	}
};

} // namespace standard
} // namespace encoding
} // namespace string
} // namespace bia

#endif