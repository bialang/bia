#pragma once

#include <cstdint>
#include <cstddef>


namespace bia
{
namespace dependency
{

class regex
{
public:
	regex(const uint8_t * _bytes, size_t _size);
	regex(const char * _string);
	regex(const char16_t * _string);
	regex(const char32_t * _string);
	regex(const regex & _copy) = delete;
	regex(regex && _move) = delete;
	~regex();

private:
	enum class TYPE
	{
		BYTE,
		UTF8,
		UTF16,
		UTF32
	};

	/** The compiled pattern. */
	void * _code;
	/** The type of the compiled pattern. */
	TYPE _type;
};

}
}