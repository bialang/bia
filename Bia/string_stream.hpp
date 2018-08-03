#pragma once

#include <cstring>

#include "allocator.hpp"
#include "encoder.hpp"
#include "ascii.hpp"
#include "utf8.hpp"


namespace bia
{
namespace stream
{

class string_stream
{
public:
	typedef decltype(machine::memory::allocator::universal_allocation::second) size_type;
	typedef size_t length_type;

	enum class CODEC
	{
		ASCII,
		UTF8,
		UTF16,
		UTF32
	};

	string_stream(machine::memory::allocator * _allocator)
	{
		this->_allocator = _allocator;
		_buffer = _allocator->prepare(offset() + 16);
		_cursor = static_cast<int8_t*>(_buffer.first) + offset();
		_end = static_cast<const int8_t*>(_buffer.first) + _buffer.second;
		_length = 0;
	}
	~string_stream()
	{
		_allocator->destroy(_encoder);
	}

	void set_codec(CODEC _codec)
	{
		switch (_codec) {
		case CODEC::ASCII:
			_encoder = _allocator->construct<encoding::encoder, encoding::ascii>();

			break;
		case CODEC::UTF8:
			_encoder = _allocator->construct<encoding::encoder, encoding::utf8>();

			break;
		case CODEC::UTF16:
		case CODEC::UTF32:
		default:
			BIA_COMPILER_DEV_INVALID;
		}
	}
	void append(encoding::code_point _code_point)
	{
		while (true) {
			try {
				_encoder->append(_code_point, _cursor, _end);
				++_length;

				break;
			} catch (const exception::encoding_error & e) {
				auto _cursor_pos = _cursor - _buffer.first;

				_buffer = _allocator->reallocate(_buffer, (_buffer.second + 4) * 2);
				_cursor = static_cast<int8_t*>(_buffer.first) + _cursor_pos;
				_end = static_cast<const int8_t*>(_buffer.first) + _buffer.second;
			}
		}
	}
	void finish()
	{
		append(encoding::encoder::eos);
		
		// Commit buffer
		_buffer = _allocator->commit(_buffer, _cursor - _buffer.first);

		std::memcpy(_buffer.first, &_buffer.second, sizeof(size_type));
		std::memcpy(static_cast<int8_t*>(_buffer.first) + sizeof(_buffer.second), &_length, sizeof(length_type));
	}
	bool codec_set() const noexcept
	{
		return _encoder;
	}
	size_t length() const noexcept
	{
		return _length;
	}
	int8_t * string() const noexcept
	{
		return static_cast<int8_t*>(_buffer.first);
	}
	constexpr static size_t offset() noexcept
	{
		return sizeof(size_type) + sizeof(length_type);
	}
	constexpr static size_t size_offset() noexcept
	{
		return 0;
	}
	constexpr static size_t length_offset() noexcept
	{
		return sizeof(size_type);
	}

private:
	machine::memory::allocator * _allocator;
	machine::memory::allocator::allocation<encoding::encoder> _encoder;
	machine::memory::allocator::universal_allocation _buffer;
	int8_t * _cursor;
	const int8_t * _end;
	length_type _length;
};

}
}