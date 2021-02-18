#include "root.hpp"

#include "gc.hpp"

#include <bia/util/gsl.hpp>

using namespace bia::memory::gc;

Root::~Root() noexcept
{
	_parent->allocator()->deallocate(_data.data());
}

void* Root::at(std::size_t index)
{
	std::lock_guard<std::mutex> _{ _mutex };
	return _data.at(index);
}

void Root::put(std::size_t index, void* ptr)
{
	std::lock_guard<std::mutex> _{ _mutex };
	_data.at(index) = ptr;
}

Root::Root(GC* parent, std::size_t size) noexcept
{
	_parent = parent;
	_data   = { static_cast<void**>(parent->allocator()->allocate(size * sizeof(void*))), size };
}
