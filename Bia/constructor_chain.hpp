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

template<typename Type, bool Is_movable, bool Is_copyable>
struct constructor_chain;

template<typename Type>
struct constructor_chain<Type, true, true>
{
	static machine::memory::allocation<Type> construct(machine::memory::allocator * _allocator, Type && _object)
	{
		return _allocator->construct<Type>(std::move(_object));
	}
	static machine::memory::allocation<Type> construct(machine::memory::allocator * _allocator, const Type & _object)
	{
		return _allocator->construct<Type>(_object);
	}
};

template<typename Type>
struct constructor_chain<Type, true, false>
{
	static machine::memory::allocation<Type> construct(machine::memory::allocator * _allocator, Type && _object)
	{
		return _allocator->construct<Type>(std::move(_object));
	}
	static machine::memory::allocation<Type> construct(machine::memory::allocator * _allocator, const Type & _object)
	{
		throw;
	}
};

template<typename Type>
struct constructor_chain<Type, false, true>
{
	static machine::memory::allocation<Type> construct(machine::memory::allocator * _allocator, Type && _object)
	{
		return _allocator->construct<Type>(_object);
	}
	static machine::memory::allocation<Type> construct(machine::memory::allocator * _allocator, const Type & _object)
	{
		return _allocator->construct<Type>(_object);
	}
};

template<typename Type>
struct constructor_chain<Type, false, false>
{
	static machine::memory::allocation<Type> construct(machine::memory::allocator * _allocator, Type && _object)
	{
		throw;
	}
	static machine::memory::allocation<Type> construct(machine::memory::allocator * _allocator, const Type & _object)
	{
		throw;
	}
};

template<typename Type>
machine::memory::allocation<Type> constructor_chain_wrapper(machine::memory::allocator * _allocator, Type && _object)
{
	return constructor_chain<Type, std::is_move_constructible<Type>::value, std::is_copy_constructible<Type>::value>::construct(_allocator, std::move(_object));
}

template<typename Type>
machine::memory::allocation<Type> constructor_chain_wrapper(machine::memory::allocator * _allocator, const Type & _object)
{
	return constructor_chain<Type, std::is_move_constructible<Type>::value, std::is_copy_constructible<Type>::value>::construct(_allocator, _object);
}

}
}
}
