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
	struct data_pair
	{
		machine::memory::allocation<Type> first;
		bool second;

		data_pair(machine::memory::allocation<Type> _first, bool _second);
		data_pair(const data_pair & _copy) = delete;
		data_pair(data_pair && _move) = delete;
		/**
		 * Destructor.
		 *
		 * @since 3.69.144.798
		 * @date 4-Dec-18
		 *
		 * @throws See machine::memory::allocator::destroy().
		*/
		~data_pair();
	};

	typedef utility::share<data_pair> data_type;

	instance_holder(machine::memory::allocation<Type> _instance, bool _owner) noexcept;
	/**
	 * Destructor.
	 *
	 * @since 3.69.144.798
	 * @date 4-Dec-18
	 *
	 * @throws See data_pair::~data_pair().
	*/
	~instance_holder() = default;
	machine::memory::allocation<Type> & get() noexcept;
	const machine::memory::allocation<Type> & get() const noexcept;

private:
	data_type _data;
};

}
}
}