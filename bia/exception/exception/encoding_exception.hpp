#pragma once

#include "exception.hpp"

namespace bia {
namespace exception {

class encoding_exception : public exception
{
public:
    using exception::exception;
};

}
}