#pragma once

#include "config.hpp"
#include "module_library.hpp"
#include "allocator.hpp"


namespace bia
{
namespace machine
{
namespace modular
{

class module_loader
{
public:
	BIA_EXPORT module_loader(memory::allocator * _allocator);
	module_loader(const module_loader & _copy) = delete;
	BIA_EXPORT module_loader(module_loader && _move) noexcept;
	BIA_EXPORT ~module_loader();

	BIA_EXPORT void unload_module(module_library * _module);
	BIA_EXPORT module_library * load_bll(const char * _filepath, const char * _name);

private:
	memory::allocator * _allocator;
};

}
}
}
