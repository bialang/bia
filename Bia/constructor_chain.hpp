#pragma once

#include <type_traits>
#include <utility>

#include "type_traits.hpp"
#include "allocator.hpp"
#include "exception.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename _Ty, bool _Movable, bool _Copyable>
struct constructor_chain;

template<typename _Ty>
struct constructor_chain<_Ty, true, true>
{
	static machine::memory::allocator::allocation<_Ty> construct(machine::memory::allocator * _allocator, _Ty && _object)
	{
		return _allocator->construct<_Ty>(std::move(_object));
	}
	static machine::memory::allocator::allocation<_Ty> construct(machine::memory::allocator * _allocator, const _Ty & _object)
	{
		return _allocator->construct<_Ty>(_object);
	}
};

template<typename _Ty>
struct constructor_chain<_Ty, true, false>
{
	static machine::memory::allocator::allocation<_Ty> construct(machine::memory::allocator * _allocator, _Ty && _object)
	{
		return _allocator->construct<_Ty>(std::move(_object));
	}
	static machine::memory::allocator::allocation<_Ty> construct(machine::memory::allocator * _allocator, const _Ty & _object)
	{
		throw;
	}
};

template<typename _Ty>
struct constructor_chain<_Ty, false, true>
{
	static machine::memory::allocator::allocation<_Ty> construct(machine::memory::allocator * _allocator, _Ty && _object)
	{
		return _allocator->construct<_Ty>(_object);
	}
	static machine::memory::allocator::allocation<_Ty> construct(machine::memory::allocator * _allocator, const _Ty & _object)
	{
		return _allocator->construct<_Ty>(_object);
	}
};

template<typename _Ty>
struct constructor_chain<_Ty, false, false>
{
	static machine::memory::allocator::allocation<_Ty> construct(machine::memory::allocator * _allocator, _Ty && _object)
	{
		throw;
	}
	static machine::memory::allocator::allocation<_Ty> construct(machine::memory::allocator * _allocator, const _Ty & _object)
	{
		throw;
	}
};

template<typename _Ty>
machine::memory::allocator::allocation<_Ty> constructor_chain_wrapper(machine::memory::allocator * _allocator, _Ty && _object)
{
	return constructor_chain<_Ty, std::is_move_constructible<_Ty>::value, std::is_copy_constructible<_Ty>::value>::construct(_allocator, std::move(_object));
}

template<typename _Ty>
machine::memory::allocator::allocation<_Ty> constructor_chain_wrapper(machine::memory::allocator * _allocator, const _Ty & _object)
{
	return constructor_chain<_Ty, std::is_move_constructible<_Ty>::value, std::is_copy_constructible<_Ty>::value>::construct(_allocator, _object);
}

}
}
}