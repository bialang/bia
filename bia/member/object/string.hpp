#ifndef BIA_MEMBER_OBJECT_STRING_HPP_
#define BIA_MEMBER_OBJECT_STRING_HPP_

#include "base.hpp"

#include <bia/primitives.hpp>
#include <bia/util/gsl.hpp>
#include <string>
#include <utility>

namespace bia {
namespace member {
namespace object {

class String : public Base
{
public:
	String(const std::string& value) : _value{ value }, _length{ util::narrow<Int>(_value.length()) }
	{}
	String(std::string&& value) : _value{ std::move(value) }, _length{ util::narrow<Int>(_value.length()) }
	{}
	memory::Frame<true> frame() noexcept override
	{
		return { { reinterpret_cast<util::Byte*>(&_length), sizeof(_length) }, nullptr };
	}
	const std::string& value() const noexcept
	{
		return _value;
	}

private:
	std::string _value;
	Int _length;
};

} // namespace object
} // namespace member
} // namespace bia

#endif
