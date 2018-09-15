#pragma once

#include <cstdint>

#include "config.hpp"
#include "member.hpp"
#include "allocator.hpp"

#if defined(BIA_OS_WINDOWS)
#define BIA_MODULE_EXPORT __declspec(dllexport)
#else
#define BIA_MODULE_EXPORT
#endif

#define BIA_MODULE_LOAD_PREFIX "bia_module_load_"
#define BIA_MODULE_UNLOAD_PREFIX "bia_module_unload_"
#define BIA_REGISTER_MODULE_LOADER(_module_, _name_) extern "C" BIA_MODULE_EXPORT bia::machine::modular::module_library * bia_module_load_##_name_(bia::machine::memory::allocator * _allocator){ return _allocator->construct<bia::machine::modular::module_library, _module_>(); } \
	extern "C" BIA_MODULE_EXPORT void bia_module_unload_##_name_(bia::machine::memory::allocator * _allocator, bia::machine::modular::module_library * _module) { _allocator->destroy<_module_>({ static_cast<_module_*>(_module), sizeof(_module_) }); }


namespace bia
{
namespace machine
{
namespace modular
{

class module_library
{
public:
  virtual ~module_library() = default;
  virtual int32_t load_all(bia::framework::member * _destination) = 0;
  virtual int32_t version() = 0;
};

typedef module_library*(*module_loader_signature)(memory::allocator*);
typedef void(*module_unloader_signature)(memory::allocator*, module_library*);

}
}
}
