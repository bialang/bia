#pragma once

#include "encoder.hpp"

#include <cstdint>

namespace bia {
namespace string {
namespace encoding {

enum class category : std::int8_t
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

category category_of(code_point_type value) noexcept;

inline bool is_letter(code_point_type value) noexcept
{
	auto c = category_of(value);

	return c >= category::Ll && c <= category::Lu;
}

inline bool is_number(code_point_type value) noexcept
{
	auto c = category_of(value);

	return c >= category::Nd && c <= category::No;
}

inline bool is_valid_unicode(code_point_type value)
{
	return value <= 0x10ffff && (value < 0xd800 || value > 0xdfff) && (value < 0xfdd0 || value > 0xfdef) &&
	       (value & 0xfffe) != 0xfffe && value != 0xfeff;
}

} // namespace encoding
} // namespace string
} // namespace bia