#pragma once

#include <utility>

#include "share_def.hpp"
#include "allocator.hpp"


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

	instance_holder(machine::memory::allocation<Type> _instance, bool _owner) noexcept;
	~instance_holder();
	machine::memory::allocation<Type> & get() noexcept;
	const machine::memory::allocation<Type> & get() const noexcept;

private:
	data_type _data;
};

}
}
}