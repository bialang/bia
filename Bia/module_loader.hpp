#pragma once

#include "module.hpp"


namespace bia
{
namespace machine
{
namespace modular
{

class module_loader
{
public:
  module_loader();
  ~module_loader();

  void unload_module(module * _module);
  module * load_module(const char * _name);

private:
  struct impl;

  impl * _impl;
};

}
}
}
