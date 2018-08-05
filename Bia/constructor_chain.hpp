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
	static _Ty * construct(machine::memory::allocator * _allocator, _Ty && _object)
	{
		return _allocator->construct<_Ty>(std::move(_object)).first;
	}
	static _Ty * construct(machine::memory::allocator * _allocator, const _Ty & _object)
	{
		return _allocator->construct<_Ty>(_object).first;
	}
};

template<typename _Ty>
struct constructor_chain<_Ty, true, false>
{
	static _Ty * construct(machine::memory::allocator * _allocator, _Ty && _object)
	{
		return _allocator->construct<_Ty>(std::move(_object)).first;
	}
	static _Ty * construct(machine::memory::allocator * _allocator, const _Ty & _object)
	{
		throw;
	}
};

template<typename _Ty>
struct constructor_chain<_Ty, false, true>
{
	static _Ty * construct(machine::memory::allocator * _allocator, _Ty && _object)
	{
		return _allocator->construct<_Ty>(_object).first;
	}
	static _Ty * construct(machine::memory::allocator * _allocator, const _Ty & _object)
	{
		return _allocator->construct<_Ty>(_object).first;
	}
};

template<typename _Ty>
struct constructor_chain<_Ty, false, false>
{
	static _Ty * construct(machine::memory::allocator * _allocator, _Ty && _object)
	{
		throw;
	}
	static _Ty * construct(machine::memory::allocator * _allocator, const _Ty & _object)
	{
		throw;
	}
};

template<typename _Ty>
_Ty * constructor_chain_wrapper(machine::memory::allocator * _allocator, _Ty && _object)
{
	return constructor_chain<_Ty, std::is_move_constructible<_Ty>::value, std::is_copy_constructible<_Ty>::value>::construct(_allocator, std::move(_object));
}

template<typename _Ty>
_Ty * constructor_chain_wrapper(machine::memory::allocator * _allocator, const _Ty & _object)
{
	return constructor_chain<_Ty, std::is_move_constructible<_Ty>::value, std::is_copy_constructible<_Ty>::value>::construct(_allocator, _object);
}

}
}
}