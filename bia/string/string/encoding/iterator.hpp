#pragma once

#include "encoder.hpp"

#include <iostream>

namespace bia {
namespace string {
namespace encoding {

class input_iterator
{
public:
	input_iterator(encoder* enc, const std::int8_t* begin, const std::int8_t* end) noexcept
	{
		nt        = true;
		this->enc = enc;
		n         = 0;
		current   = begin;
		this->end = end;
	}
	bool has_next()
	{
		if (nt) {
			nt = false;

			return enc->next(current, end, n);
		}

		return true;
	}
	code_point next() noexcept
	{
		nt = true;

		return n;
	}
	const std::int8_t* cursor() const noexcept
	{
		return current;
	}

private:
	bool nt;
	encoder* enc;
	code_point n;
	const std::int8_t* current;
	const std::int8_t* end;
};

} // namespace encoding
} // namespace string
} // namespace bia