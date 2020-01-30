#pragma once

#include "encoding_exception.hpp"

namespace bia {
namespace exception {

/*
 An exception describing that a character has an invalid value for the specified encoding.
*/
class char_encoding_exception : public encoding_exception
{
public:
	using encoding_exception::encoding_exception;
};

} // namespace exception
} // namespace bia