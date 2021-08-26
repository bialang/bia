#ifndef BIA_STRING_ENCODING_UNICODE_HPP_
#define BIA_STRING_ENCODING_UNICODE_HPP_

#include "encoder.hpp"

#include <cstdint>

namespace bia {
namespace string {
namespace encoding {

enum class Category : std::int8_t
{
	unassigned,
	Cc,
	Cf,
	Co,
	Cs,
	Ll,
	Lm,
	Lo,
	Lt,
	Lu,
	Mc,
	Me,
	Mn,
	Nd,
	Nl,
	No,
	Pc,
	Pd,
	Pe,
	Pf,
	Pi,
	Po,
	Ps,
	Sc,
	Sk,
	Sm,
	So,
	Zl,
	Zp,
	Zs
};

Category category_of(Code_point value) noexcept;

inline bool is_letter(Code_point value) noexcept
{
	const auto c = category_of(value);
	return c >= Category::Ll && c <= Category::Lu;
}

inline bool is_number(Code_point value) noexcept
{
	const auto c = category_of(value);
	return c >= Category::Nd && c <= Category::No;
}

inline bool is_valid_unicode(Code_point value) noexcept
{
	return value <= 0x10ffff && (value < 0xd800 || value > 0xdfff) && (value < 0xfdd0 || value > 0xfdef) &&
	       (value & 0xfffe) != 0xfffe && value != 0xfeff;
}

} // namespace encoding
} // namespace string
} // namespace bia

#endif
