#pragma once

#include <exception>
#include <string>

#define BIA_THROW(name, message) throw name(message, __FILE__, __LINE__)

namespace bia {
namespace exception {

class throwable : public std::exception
{
public:
	throwable(const char16_t* message, const char* filename, int line) noexcept
	    : u16message(message), filename(filename), line(line)
	{}
	virtual const char* what() const noexcept final override
	{
		return u8message.c_str();
	}
	std::string debug_message() const
	{
		std::string msg;

		msg.reserve(16 + u8message.length());

		msg.append("[").append(filename).append(":").append(std::to_string(line)).append("] ").append(u8message);

		return msg;
	}

private:
	const char* filename;
	int line;
	std::string u8message;
	std::u16string u16message;
};

} // namespace exception
} // namespace bia