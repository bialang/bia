#include "module_loader.hpp"

#include <string>

#if defined(BIA_OS_WINDOWS)
#include <Windows.h>
#elif defined(BIA_OS_LINUX)
#include <dlfcn.h>
#endif


namespace bia
{
namespace machine
{
namespace modular
{

struct module_loader::impl
{

};

module_loader::module_loader(memory::allocator * _allocator)
{
	this->_allocator = _allocator;
	_impl = _allocator->construct<impl>();
}

module_loader::~module_loader()
{
	_allocator->destroy(_impl);
}

void module_loader::unload_module(module_library * _module)
{
}

module_library * module_loader::load_bll(const char * _filepath, const char * _name)
{
#if defined(BIA_OS_WINDOWS)
	auto _library = LoadLibrary(_filepath);

	if (!_library) {
		return nullptr;
	}

	auto _module_loader = reinterpret_cast<modular::module_loader_signature>(GetProcAddress(_library, std::string(BIA_MODULE_LOAD_PREFIX).append(_name).c_str()));

	// Loader not defined
	if (!_module_loader) {
		return nullptr;
	}

	auto _module = _module_loader(_allocator);

	// Module could not be loaded
	if (!_module) {
		return nullptr;
	}

	// Unsupported loader version
	if (!_module->version()) {
		return nullptr;
	}

	return _module;
#endif
}

}
}
}
