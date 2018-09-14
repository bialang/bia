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
  module * load_bs(const char * )
  module * load_bm(const char * _filepath, const char * _name);

private:
  struct impl;

  impl * _impl;
};

}
}
}
