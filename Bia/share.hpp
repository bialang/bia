#pragma once

#include <utility>

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
	_data = machine::machine_context::active_allocator()->construct<data>(Type(std::forward<Arguments>(_arguments)...)).first;
}

template<typename Type>
inline share<Type>::share(const share & _copy) noexcept
{
	_data = _copy._data;
	_data->ref_counter.fetch_add(1, std::memory_order_relaxed);
}

template<typename Type>
inline share<Type>::~share()
{
		atomic_thread_fence(std::memory_order_acquire);

		machine::machine_context::active_allocator()->destroy(machine::memory::allocation<data>(_data, sizeof(data)));
	}
}

template<typename Type>
inline bool share<Type>::only_owner() const noexcept
{
	return _data->ref_counter.load() == 1;
}

template<typename Type>
inline Type & share<Type>::get() noexcept
{
	return _data->object;
}

template<typename Type>
inline const Type & share<Type>::get() const noexcept
{
	return _data->object;
}

template<typename Type>
inline share<Type>::data::data(Type && _object) : object(std::forward<Type>(_object)), ref_counter{ 1 }
{
}

}
}
