#pragma once

#include <mpir/mpir.h>
#include <cstddef>
#include <memory>

#include "config.hpp"
#include "allocator.hpp"
#include "int_member.hpp"
#include "double_member.hpp"


namespace bia
{
namespace machine
{
namespace memory
{

class mpir_allocator
{
public:
	typedef framework::native::int_member::int_type int_type;
	typedef framework::native::double_member::double_type double_type;

	BIA_EXPORT static void initialize(const std::shared_ptr<allocator> & _allocator);
	BIA_EXPORT static void free(void * _ptr, size_t _size);
	BIA_EXPORT static void free_int(int_type * _int);
	BIA_EXPORT static void free_double(double_type * _double);
	BIA_EXPORT static void * allocate(size_t _size);
	BIA_EXPORT static void * reallocate(void * _buffer, size_t _old_size, size_t _new_size);
	BIA_EXPORT static int_type * new_int();
	BIA_EXPORT static double_type * new_double();

private:
	static std::shared_ptr<allocator> _allocator;
};

}
}
}