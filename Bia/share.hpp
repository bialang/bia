#pragma once

#include "share_def.hpp"
#include "machine_context.hpp"
#include "scope_exit.hpp"


namespace bia
{
namespace utility
{

template<typename Type>
template<typename... Arguments>
inline share<Type>::share(Arguments &&... _arguments)
{
	create(0, std::forward<Arguments>(_arguments)...);
}

template<typename Type>
inline share<Type>::share(const share & _copy) noexcept
{
	_data = _copy._data;
	_data->reference_count.fetch_add(1, std::memory_order_relaxed);
}

template<typename Type>
inline share<Type>::share(share && _move) noexcept
{
	_data = _move._data;

	_move._data = nullptr;
}

template<typename Type>
inline share<Type>::~share()
{
	if (_data && !_data->reference_count.fetch_sub(1, std::memory_order_acq_rel)) {
		scope_exit _exit([this]() { 
			auto _tmp = _data;

			_data = nullptr;

			machine::machine_context::active_allocator()->destroy(machine::memory::allocation<data>(_tmp, data_size() + _tmp->extra_size)); 
		});

		// Destroy object
		get().~Type();
	}
}

template<typename Type>
inline Type & share<Type>::get() noexcept
{
	return *reinterpret_cast<Type*>(_data + 1);
}

template<typename Type>
inline const Type & share<Type>::get() const noexcept
{
	return *reinterpret_cast<const Type*>(_data + 1);
}

template<typename Type>
inline Type * share<Type>::operator->() noexcept
{
	return &get();
}

template<typename Type>
inline const Type * share<Type>::operator->() const noexcept
{
	return &get();
}

template<typename Type>
inline share<Type> & share<Type>::operator=(const share & _copy)
{
	this->~share();

	return *new(this) share<Type>(_copy);
}

template<typename Type>
inline share<Type> & share<Type>::operator=(share && _move)
{
	this->~share();

	return *new(this) share<Type>(std::move(_move));
}

template<typename Type>
template<typename... Arguments>
inline share<Type> share<Type>::factory_make(uint8_t _extra_size, Arguments &&... _arguments)
{
	return share<Type>(_extra_size, std::forward<Arguments>(_arguments)...);
}

template<typename Type>
template<typename ...Arguments>
inline share<Type>::share(uint8_t _extra_size, Arguments &&... _arguments)
{
	create(_extra_size, std::forward<Arguments>(_arguments)...);
}

template<typename Type>
template<typename ...Arguments>
inline void share<Type>::create(uint8_t _extra_size, Arguments && ..._arguments)
{
	auto _tmp = machine::machine_context::active_allocator()->allocate(data_size() + _extra_size);

	// Create data object
	_data = new(_tmp) data{};
	_data->extra_size = _extra_size;

	new(_data + 1) Type(std::forward<Arguments>(_arguments)...);
}

template<typename Type>
inline constexpr size_t share<Type>::data_size()
{
	return sizeof(data) + sizeof(Type);
}

}
}
