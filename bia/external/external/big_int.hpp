#pragma once

#include <cstdint>

#include <gc/memory_allocator.hpp>


namespace bia
{
namespace external
{

class big_int
{
public:
	/*
	 Creates a big integer from the largest available integer.

	 @param value is the initial value
	*/
	big_int(intmax_t value);
	/*
	 Creates a big integer from a string with a base.

	 @param value is a null terminated number in ASCII format
	 @param base is the base of the number; allowed values range from 2 to 32 included
	*/
	big_int(const char* value, int base);
	big_int(const big_int& copy);
	~big_int();

	/*
	 Initializes the underlying big integer library.

	 @param[in] allocator is the default memory allocator
	*/
	static void initialize(bia::gc::memory_allocator* allocator);

private:

};

}
}