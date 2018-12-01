#include "big_int.hpp"

namespace bia
{
namespace dependency
{

void big_int::free_int(type * _int)
{

}

big_int::type * big_int::new_int()
{
	constexpr auto int_size = sizeof(type) + sizeof(*type::_mp_d) * 2;

	auto _int = static_cast<type*>(_allocator->allocate(int_size).first);

	// Set
	memset(_int, 0, int_size);

	_int->_mp_alloc = 2;
	_int->_mp_d = reinterpret_cast<decltype(type::_mp_d)>(_int + 1);

	return _int;
}


}
}