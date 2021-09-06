#ifndef BIA_STRING_ENCODING_STANDARD_ASCII_HPP_
#define BIA_STRING_ENCODING_STANDARD_ASCII_HPP_

#include "../encoder.hpp"

namespace bia {
namespace string {
namespace encoding {
namespace standard {

/// The standard encoder for ASCII without any state. This class is thread safe.
class ASCII : public Encoder
{
public:
	void put(std::ostream& output, Code_point cp) const override;
	Code_point read(std::istream& input) const override;
};

} // namespace standard
} // namespace encoding
} // namespace string
} // namespace bia

#endif
