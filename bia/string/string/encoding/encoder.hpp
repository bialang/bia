#ifndef BIA_STRING_ENCODING_ENCODER_HPP_
#define BIA_STRING_ENCODING_ENCODER_HPP_

#include <cstddef>
#include <cstdint>
#include <istream>
#include <ostream>

namespace bia {
namespace string {
namespace encoding {

typedef std::int32_t code_point_type;

/**
 * Interface for converting from and to a specific encoding.
 */
class encoder
{
public:
	/**
	 * The standard supported encodings.
	 */
	enum class standard_encoding
	{
		/** normal 7 bit ascii encoding */
		ascii,
		/** default UTF-8 ecoding */
		utf_8,
		/** UTF-16 encoding in CPU endianness */
		utf_16,
		/** UTF-16 encoding in little endianness */
		utf_16_le,
		/** UTF-16 encoding in big endianness */
		utf_16_be,
		/** UTF-32 encoding in CPU endianness */
		utf_32,
		/** UTF-32 encoding in little endianness */
		utf_32_le,
		/** UTF-32 encoding in big endianness */
		utf_32_be
	};

	/** the byte order mark */
	constexpr static code_point_type bom = 0xfeff;
	/** the end of the input */
	constexpr static code_point_type eof = -1;

	/**
	 * Destructor.
	 */
	virtual ~encoder() = default;

	virtual void put(std::ostream& output, code_point_type cp) const = 0;
	virtual code_point_type read(std::istream& input) const          = 0;
	/*
	 Returns the standard encoder.

	 @param type is the standard encoding
	 @return a pointer to the instance that can **ONLY** be used in the current thread
	 @throws exception::unknown_encoder_exception if the standard type is not known
	*/
	static encoder* get_instance(standard_encoding encoding);
	static void free_instance(encoder* enc);
};

} // namespace encoding
} // namespace string
} // namespace bia

#endif