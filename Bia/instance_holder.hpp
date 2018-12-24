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
inline instance_holder<Type>::data_pair::data_pair(machine::memory::allocation<Type> _first, bool _second) : first(_first), second(_second)
{
}

template<typename Type>
inline instance_holder<Type>::data_pair::~data_pair()
{
	if (second) {
		machine::machine_context::active_allocator()->destroy(first);
	}
}

template<typename Type>
inline instance_holder<Type>::instance_holder(machine::memory::allocation<Type> _instance, bool _owner) noexcept : _data(_instance, _owner)
{
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