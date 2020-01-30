#ifndef BIA_EXCEPTION_BIA_ERROR_HPP_
#define BIA_EXCEPTION_BIA_ERROR_HPP_

#include <stdexcept>

#define BIA_THROW(name, message) throw name(message, __FILE__, __LINE__)

namespace bia {
namespace exception {

/**
 * The base class for all exceptions thrown by the Bia library.
*/
class bia_error : public std::runtime_error
{
public:
	/**
	 * Constructor.
	 * 
	 * @param message the error message
	 * @param filename the filename
	 * @param line the source code line number
	 * @throw see std::runtime_error::runtime_error()
	*/
	bia_error(const char* message, const char* filename, int line) : runtime_error(message)
	{
		_filename = filename;
		_line     = line;
	}
	/**
	 * Returns the filename.
	 * 
	 * @returns the filename
	*/
	const char* filename() const noexcept
	{
		return _filename;
	}
	/**
	 * Returns the line number.
	 * 
	 * @returns the line number
	*/
	int line() const noexcept
	{
		return _line;
	}

private:
	const char* _filename;
	int _line;
};

} // namespace exception
} // namespace bia

#endif