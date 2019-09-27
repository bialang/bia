#pragma once

#include "encoding_exception.hpp"

namespace bia {
namespace exception {

class unknown_encoder_exception : public encoding_exception
{
public:
    using encoding_exception::encoding_exception;
};

}
}