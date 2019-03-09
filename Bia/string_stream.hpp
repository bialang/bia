#pragma once

#include <cstring>

#include "allocator.hpp"
#include "encoder.hpp"
#include "ascii.hpp"
#include "utf8.hpp"
#include "virtual_object.hpp"


namespace bia
{
namespace stream
{

/**
 * @brief A string stream.
 *
 * A string stream for creating string with the right encoding and format for internal use.
 *
 * @see @ref machine::string_manager, @ref grammar::interpreter_token::string
*/
class string_stream
{
public:
	/** The type of the size variable. */
	typedef decltype(machine::memory::universal_allocation::second) size_t;
	/** The type of the length variable. */
	typedef size_t length_t;

	/** Supported string encodings. */
	enum class CODEC
	{
		/** The normal 7 bit ascii encoding. */
		ASCII,
		/** UTF-8. */
		UTF8,
		/** UTF-16. */
		UTF16,
		/** UFT-32. */
		UTF32
	};

	/**
	 * Constructor.
	 *
	 * @remarks The returned string by buffer() must be deallocated manually.
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @param [in] _allocator The memory allocator.
	 *
	 * @throws See machine::memory::allocator::prepare().
	*/
	string_stream(machine::memory::allocator * _allocator)
	{
		this->_allocator = _allocator;
		_buffer = _allocator->prepare(offset() + 16);
		_cursor = static_cast<int8_t*>(_buffer.first) + offset();
		_end = static_cast<const int8_t*>(_buffer.first) + _buffer.second;
		_length = 0;
	}
	/**
	 * Destructor.
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @throws See machine::memory::allocator::destroy().
	 * @throws See utility::virtual_object::~virtual_object().
	*/
	~string_stream()
	{
		// Deallocate buffer
		if (_buffer) {
			_allocator->deallocate(_buffer);
		}
	}
	/**
	 * Sets the encoding.
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @param _codec One of the supported string encodings.
	 *
	 * @throws See utility::virtual_object::reconstruct().
	*/
	void set_codec(CODEC _codec)
	{
		switch (_codec) {
		case CODEC::ASCII:
			_encoder.template reconstruct<encoding::ascii>();

			break;
		case CODEC::UTF8:
			_encoder.template reconstruct<encoding::utf8>();

			break;
		case CODEC::UTF16:
		case CODEC::UTF32:
		default:
			BIA_IMPLEMENTATION_ERROR;
		}
	}
	/**
	 * Appends a character to the stream.
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @param _code_point The character.
	 *
	 * @throws See machine::memory::allocator::reallocate().
	 * @throws See encoding::encoder::append().
	*/
	void append(encoding::code_point _code_point)
	{
		while (true) {
			try {
				_encoder->append(_code_point, _cursor, _end);

				++_length;

				break;
			} catch (const exception::encoding_error&) {
				auto _cursor_pos = _cursor - static_cast<int8_t*>(_buffer.first);

				_buffer = _allocator->reallocate(_buffer, (_buffer.second + 4) * 2);
				_cursor = static_cast<int8_t*>(_buffer.first) + _cursor_pos;
				_end = static_cast<const int8_t*>(_buffer.first) + _buffer.second;
			}
		}
	}
	/**
	 * Appends the end of string character and finishes the buffer for use.
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @throws See append().
	 * @throws See machine::memory::allocator::commit().
	*/
	void finish()
	{
		append(encoding::encoder::eos);
		
		// Don't count terminator
		--_length;

		// Commit buffer
		_buffer = _allocator->commit(_buffer, _cursor - static_cast<int8_t*>(_buffer.first));

		std::memcpy(_buffer.first, &_buffer.second, sizeof(size_t));
		std::memcpy(static_cast<int8_t*>(_buffer.first) + sizeof(_buffer.second), &_length, sizeof(length_t));
	}
	/**
	 * Checks if an encoder was set.
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @return true if an encoder was set, otherwise false.
	*/
	bool codec_set() const noexcept
	{
		return _encoder;
	}
	/**
	 * Returns the length of the string.
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @return The length of the string.
	*/
	length_t length() const noexcept
	{
		return _length;
	}
	/**
	 * Returns the formatted string buffer.
	 *
	 * @remarks If the buffer is moved, ownership of the buffer will be transfered and the string buffer will be cleared. This string stream should not be used after a buffer ownership transfer. The string is formatted as follows: (size) + (length) + (zero-terminated string)
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @return The formatted string buffer.
	*/
	machine::memory::universal_allocation & buffer() noexcept
	{
		return _buffer;
	}
	/**
	 * The total offset until the start of the string.
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @return The offset.
	*/
	constexpr static size_t offset() noexcept
	{
		return sizeof(size_t) + sizeof(length_t);
	}
	/**
	 * The total offset until the start of the size parameter.
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @return The offset.
	*/
	constexpr static size_t size_offset() noexcept
	{
		return 0;
	}
	/**
	 * The total offset until the start of the length parameter.
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @return The offset.
	*/
	constexpr static size_t length_offset() noexcept
	{
		return sizeof(size_t);
	}
	/**
	 * Returns the size of the buffer.
	 *
	 * @remarks The @a _buffer must be from buffer(), otherwise the behavior is undefined.
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @param _buffer The buffer retrieved by buffer().
	 *
	 * @return The size.
	*/
	static size_t size(const void * _buffer) noexcept
	{
		return *reinterpret_cast<const size_t*>(static_cast<const int8_t*>(_buffer) + size_offset());
	}
	/**
	 * Returns the length of the string.
	 *
	 * @remarks The @a _buffer must be from buffer(), otherwise the behavior is undefined.
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @param _buffer The buffer retrieved by buffer().
	 *
	 * @return The length.
	*/
	static length_t length(const void * _buffer) noexcept
	{
		return *reinterpret_cast<const length_t*>(static_cast<const int8_t*>(_buffer) + length_offset());
	}
	/**
	 * Returns the string.
	 *
	 * @remarks The @a _buffer must be from buffer(), otherwise the behavior is undefined.
	 *
	 * @since 3.66.135.743
	 * @date 3-Aug-18
	 *
	 * @tparam Char_type The desired char type.
	 *
	 * @param _buffer The buffer retrieved by buffer().
	 *
	 * @return The string.
	*/
	template<typename Char_type>
	static const Char_type * string(const void * _buffer) noexcept
	{
		return reinterpret_cast<const Char_type*>(static_cast<const int8_t*>(_buffer) + offset());
	}

private:
	/** The memory allocator. */
	machine::memory::allocator * _allocator;
	/** The allocated space. */
	machine::memory::universal_allocation _buffer;
	/** The string encoder. */
	utility::virtual_object<encoding::encoder, encoding::ascii, encoding::utf8> _encoder;
	/** The current position. */
	int8_t * _cursor;
	/** The end of the buffer. */
	const int8_t * _end;
	/** The length of the string. */
	length_t _length;
};

}
}