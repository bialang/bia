#pragma once

#include "encoder.hpp"

namespace bia {
namespace string {
namespace encoding {

class input_iterator
{
public:
	input_iterator(encoder* enc, const std::int8_t* begin, const std::int8_t* end)
	{
		hn		  = true;
		this->enc = enc;
		n		  = 0;
		current   = begin;
		this->end = end;
	}
	bool has_next()
	{
		return hn && (hn = enc->next(current, end, n));
	}
	code_point next()
	{
		return n;
	}
	const std::int8_t* cursor() const noexcept
	{
		return current;
	}

private:
	bool hn;
	encoder* enc;
	code_point n;
	const std::int8_t* current;
	const std::int8_t* end;
};

} // namespace encoding
} // namespace string
} // namespace bia