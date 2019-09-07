#pragma once

#include <exception>
#include <string>

namespace bia {
namespace exception {

class throwable : public std::exception
{
public:
	explicit throwable(const char16_t* message) noexcept : u16message(message)
	{}
	explicit throwable(const std::u16string& message) noexcept
		: u16message(message)
	{}
	virtual const char* what() const final override
	{
		return u8message.c_str();
	}

private:
	std::string u8message;
	std::u16string u16message;
};

} // namespace exception
} // namespace bia