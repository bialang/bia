#pragma once

#include "../encoder.hpp"
#include "../unicode.hpp"

#include <exception/char_encoding_exception.hpp>
#include <exception/length_encoding_exception.hpp>

namespace bia {
namespace string {
namespace encoding {
namespace standard {

template<bool Big_endian>
class utf16 final : public encoder
{
public:
	virtual bool next(const std::int8_t*& begin, const std::int8_t* end, code_point& output) const override
	{
		constexpr auto i0 = Big_endian ? 0 : 1;
		constexpr auto i1 = Big_endian ? 1 : 0;
		constexpr auto i2 = Big_endian ? 2 : 3;
		constexpr auto i3 = Big_endian ? 3 : 2;

		if (begin + 1 >= end) {
			return false;
		}

		// with surrogates
		if ((begin[i0] & 0xfc) == 0xd8) {
			if (begin + 3 >= end) {
				return false;
			}

			// check low surrogate
			if ((begin[i2] & 0xfc) == 0xdc) {
				output =
					(((begin[i0] & 0x03) << 18) | (begin[i1] << 10) | ((begin[i2] & 0x03) << 8) | begin[i3]) + 0x10000;
				begin += 4;
			} else {
				BIA_THROW(exception::char_encoding_exception, u"missing UTF-16 low surrogate");
			}
		} else {
			output = (begin[i0] << 8) | begin[i1];
			begin += 2;
		}

		if (!is_valid_unicode(output)) {
			BIA_THROW(exception::char_encoding_exception, error_msg);
		}

		return true;
	}

protected:
	virtual std::size_t min_size(std::size_t count) const noexcept override
	{
		return count * 2;
	}
	virtual std::size_t max_size(std::size_t count) const noexcept override
	{
		return count * 4;
	}
	virtual std::size_t min_code_points(std::size_t size) const override
	{
		if (size & 1) {
			BIA_THROW(exception::char_encoding_exception, u"the length for UTF-16 must be even");
		}

		return size / 4 + static_cast<bool>(size % 4);
	}
	virtual std::size_t max_code_points(std::size_t size) const override
	{
		if (size & 1) {
			BIA_THROW(exception::char_encoding_exception, u"the length for UTF-16 must be even");
		}

		return size / 2;
	}
	virtual std::int8_t* encode(const code_point* input, std::size_t input_len, std::int8_t* output,
								std::size_t output_len) override
	{
		const auto end	= input + input_len;
		constexpr auto i0 = Big_endian ? 0 : 1;
		constexpr auto i1 = Big_endian ? 1 : 0;
		constexpr auto i2 = Big_endian ? 2 : 3;
		constexpr auto i3 = Big_endian ? 3 : 2;

		while (input < end) {
			// check character
			if (!is_valid_unicode(*input)) {
				BIA_THROW(exception::char_encoding_exception, error_msg);
			}

			// two bytes required
			if (!(*input & ~0xffff)) {
				output[i0] = static_cast<std::int8_t>(*input >> 8);
				output[i1] = static_cast<std::int8_t>(*input & 0xff);
			} // four bytes
			else {
				auto tmp = *input - 0x10000;

				// high surrogate
				output[i0] = static_cast<std::int8_t>((tmp >> 18) | 0xd8);
				output[i1] = static_cast<std::int8_t>((tmp >> 10) & 0xff);

				// low surrogate
				output[i2] = static_cast<std::int8_t>(((tmp >> 8) & 0x03) | 0xdc);
				output[i3] = static_cast<std::int8_t>(tmp & 0xff);
			}

			++input;
		}

		return output;
	}
	virtual code_point* decode(const std::int8_t* input, std::size_t input_len, code_point* output,
							   std::size_t output_len) override
	{
		const auto end	= input + input_len;
		constexpr auto i0 = Big_endian ? 0 : 1;
		constexpr auto i1 = Big_endian ? 1 : 0;
		constexpr auto i2 = Big_endian ? 2 : 3;
		constexpr auto i3 = Big_endian ? 3 : 2;

		while (input + 1 < end) {
			// with surrogates
			if ((input[i0] & 0xfc) == 0xd8) {
				// check low surrogate
				if (input + 3 < end && (input[i2] & 0xfc) == 0xdc) {
					*output = (((input[i0] & 0x03) << 18) | (input[i1] << 10) | ((input[i2] & 0x03) << 8) | input[i3]) +
							  0x10000;
					input += 4;
				} else {
					BIA_THROW(exception::char_encoding_exception, u"missing UTF-16 low surrogate");
				}
			} else {
				*output = (input[i0] << 8) | input[i1];
				input += 2;
			}

			if (!is_valid_unicode(*output++)) {
				BIA_THROW(exception::char_encoding_exception, error_msg);
			}
		}

		return output;
	}

private:
	constexpr static auto error_msg = u"invalid UTF-16 character";
};

} // namespace standard
} // namespace encoding
} // namespace string
} // namespace bia