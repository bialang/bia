#ifndef BIA_STRING_ENCODING_STANDARD_UTF8_HPP_
#define BIA_STRING_ENCODING_STANDARD_UTF8_HPP_

#include "../encoder.hpp"
#include "../unicode.hpp"

namespace bia {
namespace string {
namespace encoding {
namespace standard {

class utf8 final : public encoder
{
public:
	void put(std::ostream& output, code_point_type cp) const override;
	code_point_type read(std::istream& input) const override;
	virtual void read_start(const std::int8_t*& begin, const std::int8_t* end) const override
	{
		auto tmp      = begin;
		code_point cp = 0;

		if (next_unchecked(tmp, end, cp)) {
			// is bom
			if (cp == bom) {
				begin = tmp;
			}
		}
	}
	virtual bool next(const std::int8_t*& begin, const std::int8_t* end, code_point& output) const override
	{
		if (next_unchecked(begin, end, output)) {
			if (!is_valid_unicode(output)) {
				BIA_THROW(exception::char_encoding_exception, error_msg);
			}

			return true;
		}

		return false;
	}

protected:
	virtual std::size_t min_size(std::size_t count) const noexcept override
	{
		return count;
	}
	virtual std::size_t max_size(std::size_t count) const noexcept override
	{
		return count * 4;
	}
	virtual std::size_t min_code_points(std::size_t size) const noexcept override
	{
		return size / 4 + static_cast<bool>(size % 4);
	}
	virtual std::size_t max_code_points(std::size_t size) const noexcept override
	{
		return size;
	}
	virtual std::int8_t* encode(const code_point* input, std::size_t input_len, std::int8_t* output,
	                            std::size_t output_len) override
	{
		const auto end   = input + input_len;
		const auto o_end = output + output_len;

		while (input < end) {
			// check character
			if (!is_valid_unicode(*input)) {
				BIA_THROW(exception::char_encoding_exception, error_msg);
			}

			// only one byte required (7 bits)
			if (!(*input & ~0x7f)) {
				if (output >= o_end) {
					break;
				}

				*output++ = static_cast<std::int8_t>(*input);
			} // two bytes required (11 bits)
			else if (!(*input & ~0x7ff)) {
				if (output + 1 >= o_end) {
					break;
				}

				*output++ = static_cast<std::int8_t>((*input >> 6) | 0xc0);
				*output++ = static_cast<std::int8_t>((*input & 0x3f) | 0x80);
			} // three bytes required (16 bits)
			else if (!(*input & ~0xffff)) {
				if (output + 2 >= o_end) {
					break;
				}

				*output++ = static_cast<std::int8_t>((*input >> 12) | 0xe0);
				*output++ = static_cast<std::int8_t>(((*input >> 6) & 0x3f) | 0x80);
				*output++ = static_cast<std::int8_t>((*input & 0x3f) | 0x80);
			} // four bytes required (21 bits)
			else {
				if (output + 3 >= o_end) {
					break;
				}

				*output++ = static_cast<std::int8_t>((*input >> 18) | 0xf0);
				*output++ = static_cast<std::int8_t>(((*input >> 12) & 0x3f) | 0x80);
				*output++ = static_cast<std::int8_t>(((*input >> 6) & 0x3f) | 0x80);
				*output++ = static_cast<std::int8_t>((*input & 0x3f) | 0x80);
			}

			++input;
		}

		return output;
	}
	virtual code_point* decode(const std::int8_t* input, std::size_t input_len, code_point* output,
	                           std::size_t output_len) override
	{
		const auto end   = input + input_len;
		const auto o_end = output + output_len;

		while (input < end && output < o_end) {
			// only one byte
			if (!(*input & 0x80)) {
				*output = *input++;
			} // two bytes
			else if ((*input & 0xe0) == 0xc0) {
				if (input + 2 > end) {
					BIA_THROW(exception::char_encoding_exception, error_msg);
				}

				*output = ((input[0] & 0x1f) << 6) | (input[1] & 0x3f);
				input += 2;
			} // three bytes
			else if ((*input & 0xf0) == 0xe0) {
				if (input + 3 > end) {
					BIA_THROW(exception::char_encoding_exception, error_msg);
				}

				*output = ((input[0] & 0x0f) << 12) | ((input[1] & 0x3f) << 6) | (input[2] & 0x3f);
				input += 3;
			} // four bytes
			else if ((*input & 0xf8) == 0xf0) {
				if (input + 4 > end) {
					BIA_THROW(exception::char_encoding_exception, error_msg);
				}

				*output = ((input[0] & 0x07) << 18) | ((input[1] & 0x3f) << 12) | ((input[2] & 0x3f) << 6) |
				          (input[3] & 0x3f);
				input += 4;
			} else {
				BIA_THROW(exception::char_encoding_exception, error_msg);
			}

			if (!is_valid_unicode(*output++)) {
				BIA_THROW(exception::char_encoding_exception, error_msg);
			}
		}

		return output;
	}

private:
	constexpr static auto error_msg = u"invalid UTF-8 character";

	bool next_unchecked(const std::int8_t*& begin, const std::int8_t* end, code_point& output) const
	{
		if (begin >= end) {
			return false;
		}

		// only one byte
		if (!(*begin & 0x80)) {
			output = static_cast<code_point>(*begin++);
		} // two bytes
		else if ((*begin & 0xe0) == 0xc0) {
			if (begin + 2 > end) {
				return false;
			}

			output = ((begin[0] & 0x1f) << 6) | (begin[1] & 0x3f);
			begin += 2;
		} // three bytes
		else if ((*begin & 0xf0) == 0xe0) {
			if (begin + 3 > end) {
				return false;
			}

			output = ((begin[0] & 0x0f) << 12) | ((begin[1] & 0x3f) << 6) | (begin[2] & 0x3f);
			begin += 3;
		} // four bytes
		else if ((*begin & 0xf8) == 0xf0) {
			if (begin + 4 > end) {
				return false;
			}

			output = ((begin[0] & 0x07) << 18) | ((begin[1] & 0x3f) << 12) | ((begin[2] & 0x3f) << 6) |
			         (begin[3] & 0x3f);
			begin += 4;
		} else {
			BIA_THROW(exception::char_encoding_exception, error_msg);
		}

		return true;
	}
};

} // namespace standard
} // namespace encoding
} // namespace string
} // namespace bia

#endif
