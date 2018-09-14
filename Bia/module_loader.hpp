#pragma once

#include "module.hpp"
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
	module_loader(memory::allocator * _allocator);
	~module_loader();

	void unload_module(module * _module);
	module * load_bll(const char * _filepath, const char * _name);

private:
	struct impl;

	memory::allocator * _allocator;
	memory::allocation<impl> _impl;
};

}
}
}
