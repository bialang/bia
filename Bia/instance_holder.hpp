#pragma once

#include "share.hpp"
#include "allocator.hpp"
#include "machine_context.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename Type>
class instance_holder
{
public:
	typedef utility::share<std::pair<machine::memory::allocation<Type>, bool>> data_type;

	instance_holder(machine::memory::allocation<Type> _instance, bool _owner) noexcept : _data(_instance, _owner)
	{
	}
	~instance_holder()
	{
		if (_data.only_owner() && _data.get().second) {
			machine::machine_context::active_allocator()->destroy(_data.get().first);
		}
	}
	machine::memory::allocation<Type> & get() noexcept
	{
		return _data.get().first;
	}
	const machine::memory::allocation<Type> & get() const noexcept
	{
		return _data.get().first;
	}

private:
	data_type _data;
};

}
}
}