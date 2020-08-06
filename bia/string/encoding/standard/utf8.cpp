#include "utf8.hpp"

#include <bia/exception/invalid_code_point.hpp>

using namespace bia::string::encoding::standard;

void utf8::put(std::ostream& output, code_point_type cp) const
{
  if (~cp & 0x7f) {
    const auto data = static_cast<char>(cp);
    output.write()
  }
}

bia::string::encoding::code_point_type utf8::read(std::istream& input) const
{}
