#include "module_loader.hpp"

#include <vector>

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

module_loader::module_loader()
{
  _impl = new impl();
}

module_loader::~module_loader()
{
  delete _impl;
}

module * module_loader::load_bm(const char * _filepath, const char * _name)
{
#if defined(BIA_OS_WINDOWS)
  auto _library = LoadLibrary(_filepath);

  if (!_library) {

  }

  auto _module = static_cast<modular::module_loader_signature>(GetProcAddress(_library, (std::string(BIA_MODULE_LOADER_PREFIX) + _module).c_str()));

  // Loader not defined
  if (!_module) {
    return false;
  }

  auto _loader = _module_loader(allocator());

  // Loader could not be loaded
  if (!_loader) {
    return false;
  }

  // Unsupported loader version
  if (!_loader->version()) {
    return false;
  }

  auto _member = address_of_member(name_address(_module));
  auto _error = _module->load_all(_member);
}

}
}
}
