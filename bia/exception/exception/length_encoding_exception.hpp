#pragma once

#include "encoding_exception.hpp"

namespace bia {
namespace exception {

class length_encoding_exception : public encoding_exception
{
public:
	using encoding_exception::encoding_exception;
};

} // namespace exception
} // namespace bia