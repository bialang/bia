#pragma once

#include "../string.hpp"

#include <cstddef>
#include <cstdint>

namespace bia {
namespace string {
namespace encoding {

typedef std::uint32_t code_point;

/*
 Converts the from the specified encodig to the internal string encoding and vice versa.
*/
class encoder
{
public:
	enum class STANDARD_ENCODING
	{
		ASCII,
		UTF_8,
		UTF_16,
		UTF_16_LE,
		UTF_16_BE,
		UTF_32,
		UTF_32_LE,
		UTF_32_BE
	};

	/* the byte order mark */
	constexpr static code_point bom = 0xfeff;

	virtual ~encoder() = default;

	virtual void read_start(const std::int8_t*& begin, const std::int8_t* end) const = 0;
	/*
	 Reads the next code point from the buffer and advances the pointer.

	 @param[in,out] begin is the start of the buffer; will be advanced on a successful read
	 @param end is the end of the buffer
	 @param[out] output is the read code point
	 @return `true` if there were no errors and the code point was read to `output`, otherwise `false`
	 @throws exception::char_encoding_exception if the read code point is invalid
	*/
	virtual bool next(const std::int8_t*& begin, const std::int8_t* end, code_point& output) const = 0;
	/*
	 Converts the buffer `input` to UTF-16 encoded string.

	 @param input the input buffer
	 @param length the length of the input buffer
	 @return the UTF-16 encoded string
	*/
	string convert(const std::int8_t* input, std::size_t length);
	/*
	 Returns the standard encoder.

	 @param type is the standard encoding
	 @return a pointer to the instance that can **ONLY** be used in the current thread
	 @throws exception::unknown_encoder_exception if the standard type is not known
	*/
	static encoder* get_instance(STANDARD_ENCODING type);
	/*
	 Returns the encoder by name. This function can return more encoders than the one with standard encodings, depending
	 on the backend encoding library.

	 @param name is the name of the encoder
	 @return a pointer to the instance that can **ONLY** be used in the current thread
	 @throws exception::unknown_encoder_exception if the encoder is unknown
	*/
	static encoder* get_instance(string name);
	/*
	 Frees the instance returned by get_instance().

	 @param[in] enc the encoder
	*/
	static void free_instance(encoder* enc);

protected:
	/*
	 Returns the minimum size when `count` many code points should be encoded.

	 @param count the amount of code points
	 @return the minimum size
	*/
	virtual std::size_t min_size(std::size_t count) const noexcept = 0;
	/*
	 Returns the maximum size when `count` many code points should be encoded.

	 @param count the amount of code points
	 @return the maximum size
	*/
	virtual std::size_t max_size(std::size_t count) const noexcept = 0;
	/*
	 Returns the minimum amount of resulting code points when decoding a buffer with the size of `size`.

	 @param size the size of the buffer
	 @return the minimum count
	 @throws exception::char_encoding_exception if the size cannot be resolved into a valid output string
	*/
	virtual std::size_t min_code_points(std::size_t size) const = 0;
	/*
	 Returns the maximum amount of resulting code points when decoding a buffer with the size of `size`.

	 @param size the size of the buffer
	 @return the maximum count
	 @throws exception::char_encoding_exception if the size cannot be resolved into a valid output string
	*/
	virtual std::size_t max_code_points(std::size_t size) const = 0;
	virtual std::int8_t* encode(const code_point* input, std::size_t input_len, std::int8_t* output,
								std::size_t output_len)			= 0;
	virtual code_point* decode(const std::int8_t* input, std::size_t input_len, code_point* output,
							   std::size_t output_len)			= 0;
};

} // namespace encoding
} // namespace string
} // namespace bia