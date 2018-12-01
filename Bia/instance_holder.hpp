#pragma once

#include "instance_holder_def.hpp"
#include "share.hpp"
#include "machine_context.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename Type>
inline instance_holder<Type>::instance_holder(machine::memory::allocation<Type> _instance, bool _owner) noexcept : _data(_instance, _owner)
{
}

template<typename Type>
inline instance_holder<Type>::~instance_holder()
{
	if (_data.only_owner() && _data.get().second) {
		machine::machine_context::active_allocator()->destroy(_data.get().first);
	}
}

template<typename Type>
inline machine::memory::allocation<Type> & instance_holder<Type>::get() noexcept
{
	return _data.get().first;
}

template<typename Type>
inline const machine::memory::allocation<Type> & instance_holder<Type>::get() const noexcept
{
	return _data.get().first;
}

}
}
}