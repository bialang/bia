#pragma once

#include <cstdint>


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

private:
	/** The compiled pattern. */
	void * _code;
};

}
}