#pragma once

#include "share_def.hpp"
#include "machine_context.hpp"


namespace bia
{
namespace utility
{

template<typename Type>
template<typename... Arguments>
inline share<Type>::share(Arguments &&... _arguments)
{
	_data = machine::machine_context::active_allocator()->construct<data>();

	// Create object inplace
	new(_data->first) Type(std::forward<Arguments>(_arguments)...);
}

template<typename Type>
inline share<Type>::share(const share & _copy) noexcept
{
	_data = _copy._data;
	_data->second.fetch_add(1, std::memory_order_relaxed);
}

template<typename Type>
inline share<Type>::~share()
{
	if (!_data->second.fetch_sub(1, std::memory_order_acq_rel)) {
		// Destroy object
		reinterpret_cast<Type*>(_data->first)->~Type();

		machine::machine_context::active_allocator()->destroy(machine::memory::allocation<data>(_data, sizeof(data)));
	}
}

template<typename Type>
inline Type & share<Type>::get() noexcept
{
	return *reinterpret_cast<Type*>(_data->first);
}

template<typename Type>
inline const Type & share<Type>::get() const noexcept
{
	return *reinterpret_cast<const Type*>(_data->first);
}

}
}
