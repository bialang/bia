#pragma once

#include "encoder.hpp"

#include <cstdint>

namespace bia {
namespace string {
namespace encoding {

enum class CATEGORY : std::int8_t
{
	UNASSIGNED,
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

CATEGORY category_of(code_point value) noexcept;

inline bool is_letter(code_point value) noexcept
{
	auto category = category_of(value);

	return category == CATEGORY::Ll || category == CATEGORY::Lm || category == CATEGORY::Lo ||
		   category == CATEGORY::Lt || category == CATEGORY::Lu;
}

inline bool is_number(code_point value) noexcept
{
	auto category = category_of(value);

	return category == CATEGORY::Nd || category == CATEGORY::Nl || category == CATEGORY::No;
}

inline bool is_valid_unicode(code_point value)
{
	return value <= 0x10ffff && (value < 0xd800 || value > 0xdfff) && (value < 0xfdd0 || value > 0xfdef) &&
		   (value & 0xfffe) != 0xfffe && value != 0xfeff;
}

} // namespace encoding
} // namespace string
} // namespace bia