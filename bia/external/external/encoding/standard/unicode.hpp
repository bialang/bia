#pragma once

#include "../encoder.hpp"

namespace bia {
namespace external {
namespace encoding {
namespace standard {

inline bool is_valid_unicode(code_point value)
{
    return value <= 0x10ffff &&
        value < 0xd800 && value > 0xdfff;
}

}
}
}
}