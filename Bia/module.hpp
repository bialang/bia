#pragma once

#include <cstdint>

#include "member.hpp"
#include "allocator.hpp"

#define BIA_MODLE_LOADER_PREFIX "bia_module_loader_"
#define BIA_REGISTER_MODULE_LOADER(loader, name) extern "C" bia::machine::memory::allocation<bia::machine::modular::module_loader> bia_module_loader_##name(bia::machine::memory::allocator * _allocator){ return _allocator->construct<bia::machine::modular::module_loader, loader>(); }


namespace bia
{
namespace machine
{
namespace modular
{

class module
{
public:
  virtual ~module() = default;
  virtual int32_t load_all(framework::member * _destination) = 0;
  virtual int32_t version() = 0;
};

typedef memory::allocation<module_loader>(*module_loader_signature)(memory::allocator*);

}
}
}
