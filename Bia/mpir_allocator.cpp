#include "mpir_allocator.hpp"

#include <type_traits>
#include <cstdint>
#include <cstring>


namespace bia
{
namespace machine
{
namespace memory
{

std::shared_ptr<allocator> mpir_allocator::_allocator;


void mpir_allocator::int_destructor_function(universal_allocation _int)
{
	mpz_clear(cast_allocation<int_type>(_int));
}

void bia::machine::memory::mpir_allocator::initialize(const std::shared_ptr<allocator>& _allocator)
{
	mpir_allocator::_allocator = _allocator;

	mp_set_memory_functions(&mpir_allocator::allocate, &mpir_allocator::reallocate, &mpir_allocator::free);
}

void mpir_allocator::free(void * _ptr, size_t _size)
{
	_allocator->deallocate(universal_allocation(_ptr, _size));
}

void mpir_allocator::free_int(int_type * _int)
{
	mpz_clear(_int);

	_allocator->deallocate(universal_allocation(_int, sizeof(int_type) + sizeof(*int_type::_mp_d) * 2));
}

void mpir_allocator::free_double(double_type * _double)
{
	mpf_clear(_double);

	_allocator->deallocate(universal_allocation(_double, sizeof(double_type) + sizeof(*double_type::_mp_d) * 2));
}

void * mpir_allocator::allocate(size_t _size)
{
	return _allocator->allocate(_size);
}

void * mpir_allocator::reallocate(void * _buffer, size_t _old_size, size_t _new_size)
{
	// Memory is preallocated from int_type / double_type
	if (_old_size == sizeof(*int_type::_mp_d) * 2) {
		// Copy buffer
		auto _new = _allocator->allocate(_new_size);

		memcpy(_new, _buffer, _old_size);

		return _new;
	}

	return _allocator->reallocate(universal_allocation(_buffer, _old_size), _new_size);
}

allocation<mpir_allocator::int_type> mpir_allocator::new_int()
{
	auto _int = cast_allocation<int_type>(_allocator->allocate(sizeof(int_type) + sizeof(*int_type::_mp_d) * 2));
	
	// Set
	memset(_int, 0, sizeof(int_type));

	_int->_mp_alloc = 2;
	_int->_mp_d = reinterpret_cast<decltype(int_type::_mp_d)>(_int.first + 1);

	return _int;
}

mpir_allocator::double_type * mpir_allocator::new_double()
{
	///TODO
	throw;
	auto _double = static_cast<double_type*>(_allocator->allocate(sizeof(double_type) + sizeof(*double_type::_mp_d) * 2).first);
	
	// Set
	memset(_double, 0, sizeof(int_type));

	//_double->_mp_alloc = 2;
	//_double->_mp_d = reinterpret_cast<decltype(int_type::_mp_d)>(_int + 1);

	return _double;
}

}
}
}