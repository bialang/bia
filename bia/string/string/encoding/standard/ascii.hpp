#pragma once

#include "../encoder.hpp"

#include <exception/char_encoding_exception.hpp>

namespace bia {
namespace string {
namespace encoding {
namespace standard {

/*
 The standard encoder for ASCII without any state. This class is safe to use between threads.
*/
class ascii final : public encoder
{
public:
	virtual bool next(const std::int8_t*& begin, const std::int8_t* end, code_point& output) const override
	{
		if (begin >= end) {
			return false;
		}

		output = static_cast<code_point>(*begin++);

		if (output & ~0x7f) {
			BIA_THROW(exception::char_encoding_exception, u"invalid ASCII character");
		}

		return true;
	}

protected:
	virtual std::size_t min_size(std::size_t count) const noexcept override
	{
		return count;
	}
	virtual std::size_t max_size(std::size_t count) const noexcept override
	{
		return count;
	}
	virtual std::size_t min_code_points(std::size_t size) const noexcept override
	{
		return size;
	}
	virtual std::size_t max_code_points(std::size_t size) const noexcept override
	{
		return size;
	}
	virtual std::int8_t* encode(const code_point* input, std::size_t input_len, std::int8_t* output,
								std::size_t output_len) override
	{
		const auto end = input + input_len;

		while (input < end && output_len-- > 0) {
			// check character
			if (*input & ~0x7f) {
				BIA_THROW(exception::char_encoding_exception, u"invalid ASCII character");
			}

			*output++ = static_cast<std::int8_t>(*input++);
		}

		return output;
	}
	virtual code_point* decode(const std::int8_t* input, std::size_t input_len, code_point* output,
							   std::size_t output_len) override
	{
		const auto end = input + input_len;

		while (input < end && output_len-- > 0) {
			// check character
			if (*input & ~0x7f) {
				BIA_THROW(exception::char_encoding_exception, u"invalid ASCII character");
			}

			*output++ = *input++;
		}

		return output;
	}
};

} // namespace standard
} // namespace encoding
} // namespace string
} // namespace bia