#pragma once

#include <cstddef>
#include <memory>
#include <type_traits>

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
	constexpr static auto big_int_allocation_size = sizeof(dependency::big_int);

	virtual ~big_int_allocator() = default;
	BIA_EXPORT static void initialize(const std::shared_ptr<allocator> & _allocator);
	virtual void deallocate_big_int(allocation<dependency::big_int> _allocation) = 0;
	BIA_EXPORT void destroy_big_int(allocation<dependency::big_int> _big_int);
	virtual allocation<dependency::big_int> allocate_big_int() = 0;
	template<typename Type>
	typename std::enable_if<std::is_integral<Type>::value, allocation<dependency::big_int>>::type construct_big_int(Type _value = 0)
	{
		auto _big_int = allocate_big_int();

		new(_big_int) dependency::big_int(_value);

		return _big_int;
	}


private:
	static std::shared_ptr<allocator> _allocator;

	BIA_EXPORT static void free(void * _ptr, size_t _size);
	BIA_EXPORT static void * allocate(size_t _size);
	BIA_EXPORT static void * reallocate(void * _buffer, size_t _old_size, size_t _new_size);
};

}
}
}