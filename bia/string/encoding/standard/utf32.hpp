#ifndef BIA_STRING_ENCODING_STANDARD_UTF32_HPP_
#define BIA_STRING_ENCODING_STANDARD_UTF32_HPP_

#include "../encoder.hpp"

#include <bia/util/config.hpp>

namespace bia {
namespace string {
namespace encoding {
namespace standard {

template<bool Little_endian>
class UTF32 : public Encoder
{
public:
	void put(std::ostream& output, Code_point cp) const override;
	Code_point read(std::istream& input) const override;
};

typedef UTF32<true> UTF32LE;
typedef UTF32<false> UTF32BE;

#if BIA_BIG_ENDIAN
typedef UTF32<false> UTF32_host;
#else
typedef UTF32<true> UTF32_host;
#endif

} // namespace standard
} // namespace encoding
} // namespace string
} // namespace bia

#endif
