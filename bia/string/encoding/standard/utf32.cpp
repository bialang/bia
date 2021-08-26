#include "utf32.hpp"

#include "../unicode.hpp"

#include <algorithm>
#include <bia/error/exception.hpp>
#include <bia/util/config.hpp>

using namespace bia::string::encoding::standard;

template<>
void UTF32<false>::put(std::ostream& output, Code_point cp) const
{
	if (!is_valid_unicode(cp)) {
		BIA_THROW(error::Code::bad_unicode);
	}
#if !BIA_BIG_ENDIAN
	std::reverse(reinterpret_cast<char*>(&cp), reinterpret_cast<char*>(&cp) + sizeof(cp));
#endif
	output.write(reinterpret_cast<char*>(&cp), sizeof(cp));
}

template<>
void UTF32<true>::put(std::ostream& output, Code_point cp) const
{
	if (!is_valid_unicode(cp)) {
		BIA_THROW(error::Code::bad_unicode);
	}
#if BIA_BIG_ENDIAN
	std::reverse(reinterpret_cast<char*>(&cp), reinterpret_cast<char*>(&cp) + sizeof(cp));
#endif
	output.write(reinterpret_cast<char*>(&cp), sizeof(cp));
}

template<>
bia::string::encoding::Code_point UTF32<false>::read(std::istream& input) const
{
	Code_point cp{};
	input.read(reinterpret_cast<char*>(&cp), sizeof(cp));
	if (!input) {
		BIA_THROW(error::Code::unfinished_utf_sequence);
	}
#if !BIA_BIG_ENDIAN
	std::reverse(reinterpret_cast<char*>(&cp), reinterpret_cast<char*>(&cp) + sizeof(cp));
#endif
	return cp;
}

template<>
bia::string::encoding::Code_point UTF32<true>::read(std::istream& input) const
{
	Code_point cp{};
	input.read(reinterpret_cast<char*>(&cp), sizeof(cp));
	if (!input) {
		BIA_THROW(error::Code::unfinished_utf_sequence);
	}
#if BIA_BIG_ENDIAN
	std::reverse(reinterpret_cast<char*>(&cp), reinterpret_cast<char*>(&cp) + sizeof(cp));
#endif
	return cp;
}
