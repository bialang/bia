#pragma once

#include <cstddef>
#include <memory>

#include "config.hpp"
#include "allocator.hpp"
#include "big_int.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

class big_int_allocator
{
public:
	typedef allocation<dependency::big_int> int_type;

	BIA_EXPORT static void initialize(const std::shared_ptr<block_allocator0<sizeof(dependency::big_int)>> & _allocator);
	BIA_EXPORT static void free_int(int_type _int);
	BIA_EXPORT static int_type new_int();

private:
	static std::shared_ptr<block_allocator0<sizeof(dependency::big_int)>> _allocator;

	BIA_EXPORT static void free(void * _ptr, size_t _size);
	BIA_EXPORT static void * allocate(size_t _size);
	BIA_EXPORT static void * reallocate(void * _buffer, size_t _old_size, size_t _new_size);
};

}
}
}