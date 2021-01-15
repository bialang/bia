#ifndef BIA_STRING_ENCODING_STANDARD_UTF8_HPP_
#define BIA_STRING_ENCODING_STANDARD_UTF8_HPP_

#include "../encoder.hpp"

namespace bia {
namespace string {
namespace encoding {
namespace standard {

class UTF8 final : public Encoder
{
public:
	void put(std::ostream& output, code_point_type cp) const override;
	code_point_type read(std::istream& input) const override;
};

} // namespace standard
} // namespace encoding
} // namespace string
} // namespace bia

#endif
