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
		this->enc = enc;
		next	  = 0;
		current   = begin;
		this->end = end;
	}
	input_iterator()
	{
		enc		= nullptr;
		next	= 0;
		current = nullptr;
		end		= nullptr;
	}
	bool operator==(const input_iterator& other) noexcept
	{
		auto e0 = is_end();
		auto e1 = other.is_end();

		if (e0 && e1) {
			return true;
		}

		// get next
		next = enc->next(current, end);

		// reached the end
		if (next == encoder::eof) {
			return e1;
		}
	}
	bool operator!=(const input_iterator& other) noexcept
	{
		return !this->operator==(other);
	}
	const std::int8_t* cursor() const noexcept
	{
		return current;
	}
	code_point operator*() const noexcept
	{
		return next;
	}
	input_iterator& operator++()
	{
		next = enc->next(current, end);

		return *this;
	}
	input_iterator operator++(int)
	{
		input_iterator copy(*this);

		this->operator++();

		return copy;
	}

private:
	encoder* enc;
	code_point next;
	const std::int8_t* current;
	const std::int8_t* end;

	bool is_end() const noexcept
	{
		return current == nullptr;
	}
};

} // namespace encoding
} // namespace string
} // namespace bia