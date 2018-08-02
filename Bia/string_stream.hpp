#pragma once

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
		_buffer = _allocator->prepare(16);
		_cursor = static_cast<int8_t*>(_buffer.first);
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
	}
	bool codec_set() const noexcept
	{
		return _encoder;
	}
	size_t length() const noexcept
	{
		return _length;
	}
	machine::memory::allocator::allocation<char> string() const noexcept
	{
		return machine::memory::allocator::cast_allocation<char>(_buffer);
	}
	machine::memory::allocator::allocation<char16_t> string16() const noexcept
	{
		return machine::memory::allocator::cast_allocation<char16_t>(_buffer);
	}
	machine::memory::allocator::allocation<char32_t> string32() const noexcept
	{
		return machine::memory::allocator::cast_allocation<char32_t>(_buffer);
	}
	machine::memory::allocator::allocation<wchar_t> wstring() const noexcept
	{
		return machine::memory::allocator::cast_allocation<wchar_t>(_buffer);
	}

private:
	machine::memory::allocator * _allocator;
	machine::memory::allocator::allocation<encoding::encoder> _encoder;
	machine::memory::allocator::universal_allocation _buffer;
	int8_t * _cursor;
	const int8_t * _end;
	size_t _length;
};

}
}