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

template<typename _Ty>
class instance_holder
{
public:
	typedef utility::share<std::pair<machine::memory::allocator::allocation<_Ty>, bool>> data_type;

	instance_holder(machine::memory::allocator::allocation<_Ty> _instance, bool _owner) noexcept : _data(_instance, _owner)
	{
	}
	~instance_holder()
	{
		if (_data.only_owner() && _data.get().second) {
			machine::machine_context::active_allocator()->destroy(_data.get().first);
		}
	}
	machine::memory::allocator::allocation<_Ty> & get() noexcept
	{
		return _data.get().first;
	}
	const machine::memory::allocator::allocation<_Ty> & get() const noexcept
	{
		return _data.get().first;
	}

private:
	data_type _data;
};

}
}
}