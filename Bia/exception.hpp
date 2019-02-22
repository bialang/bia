#pragma once

#include <string>
#include <cstdio>
#include <typeinfo>
#include <exception>
#include <stdexcept>

#define BIA_IMPLEMENTATION_EXCEPTION(msg) bia::exception::implementation_error(msg, __FILE__, __LINE__)
#define BIA_IMPLEMENTATION_ERROR throw BIA_IMPLEMENTATION_EXCEPTION("Implementation error.")
#define BIA_NOT_IMPLEMENTED throw BIA_IMPLEMENTATION_EXCEPTION("Not implemented.")
#define BIA_EM_UNSUPPORTED_TYPE "Type is not supported."
#define BIA_EM_UNEXPECTED_TYPE "Unexpected type."
#define BIA_EM_UNDEFINED_MEMBER "Undefined member."
#define BIA_EM_UNKNOWN_MEMBER "Unknown member."
#define BIA_EM_UNKNOWN_SCRIPT "Unknown script."
#define BIA_EM_NULL_INSTANCE "Cannot access member without an instance."
#define BIA_EM_REPORT_LIMIT "Report bundle limit reached."
#define BIA_EM_LIMITATION_EXCEEDED "Limitation has been exceeded."
#define BIA_EM_INVALID_ARGUMENT "Invalid arguments."
#define BIA_EM_INVALID_ENCODING "Invalid encoding."
#define BIA_EM_NOT_ENOUGH_SPACE "Not enough space."
#define BIA_EM_INVALID_UNICODE "Invalid unicode character."
#define BIA_EM_INVALID_ASCII "Invalid ascii character."
#define BIA_EM_INVALID_INSTANCE_TYPE "The type of the instance is invalid."
#define BIA_EM_UNSUPPORTED_EXECUTE "This type cannot be executed."
#define BIA_EM_UNSUPPORTED_TEST "This member cannot be tested."
#define BIA_EM_UNSUPPORTED_OPERATION "This operation is not supported."
#define BIA_EM_UNSUPPORTED_OPERATOR "Unsupported operator."
#define BIA_EM_UNSUPPORTED_INSTANTIATION "Instantiation is not supported."
#define BIA_EM_UNSUPPORTED_COPY "Cannot be copied."
#define BIA_EM_FAILED_ALLOCATION "Allocation failed."
#define BIA_EM_FAILED_MEMORY_PROTECTION "Cannot change protection of the memory address."
#define BIA_EM_ASSIGN_ON_CONST "Assigns on constant variable are disallowed."
#define BIA_EM_SYMBOL_ALREADY_EXISTS "Symbol already exists."
#define BIA_EM_MODULE_NOT_FOUND "Specified module not found."
#define BIA_EM_DOUBLE_OVERFLOW "Double value overflow."
#define BIA_EM_DOUBLE_UNDERFLOW "Double value underflow."
#define BIA_EM_INT_OVERFLOW "Integer value overflows as native int64."
#define BIA_EM_INT_UNDERFLOW "Integer value underflows as native int64."
#define BIA_EM_DIVISION_BY_ZERO "Division or modulo by zero."


namespace bia
{
namespace exception
{

/**
 * @brief A Bia error.
 *
 * Every thrown exception of Bia will inherit this.
*/
class bia_error : public std::exception
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.71.149.809
	 * @date 28-Dec-18
	 *
	 * @param _message The message of the exception.
	*/
	explicit bia_error(const char * _message) noexcept : _message(_message)
	{
	}
	/**
	 * Constructor.
	 *
	 * @since 3.71.149.809
	 * @date 28-Dec-18
	 *
	 * @param _message The message of the exception.
	*/
	explicit bia_error(const std::string & _message) noexcept : _message(_message)
	{
	}
	/**
	 * Destructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	*/
	virtual ~bia_error() noexcept = default;
	virtual const char * what() const noexcept override
	{
		return _message.c_str();
	}
	
protected:
	std::string _message;
};

/**
 * @brief A logical error.
 *
 * Every logical exception of Bia will inherit this.
 *
 * @see @ref runtime_error
*/
class logic_error : public bia_error
{
public:
	using bia_error::bia_error;
};

/**
 * @brief An implementation error.
*/
class implementation_error : public bia_error
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	 * @param _file The file.
	 * @param _line The line.
	*/
	implementation_error(const std::string & _message, const char * _file, int _line) noexcept : bia_error(_message)
	{
		this->_message.append(_file).append(":").append(std::to_string(_line)).append(":").append(_message);
	}
};

/**
 * @brief A runtime exception.
 *
 * Every runtime exception of Bia will inherit this.
 *
 * @see @ref logic_error
*/
class runtime_error : public bia_error
{
public:
	using bia_error::bia_error;
};

/**
 * @brief Indicates an invalid cast.
 *
 * Indicates an invalid type cast.
*/
class type_error : public logic_error
{
public:
	using logic_error::logic_error;
};

/**
 * @brief Indicates an invalid encoding.
 *
 * Indicates an invalid encoding or an encoding error.
*/
class encoding_error : public logic_error
{
public:
	using logic_error::logic_error;
};

/**
 * @brief One or more argument errors.
 *
 * Invalid argument count, nullpoiter or invalid arguments.
*/
class argument_error : public logic_error
{
public:
	using logic_error::logic_error;
};

/**
 * @brief Unresolvable symbol.
 *
 * Symbol cannot be resolved or it is in an undefined state.
*/
class symbol_error : public runtime_error
{
public:
	using runtime_error::runtime_error;
};

/**
 * @brief Limitation error.
 *
 * A limitiation has been exceeded.
*/
class limitation_error : public runtime_error
{
public:
	using runtime_error::runtime_error;
};

/**
 * @brief Execution error.
 *
 * The performed call is invalid.
*/
class execution_error : public runtime_error
{
public:
	using runtime_error::runtime_error;
};

/**
 * @brief Operator error.
 *
 * The operator is invalid or not supported.
*/
class operator_error : public runtime_error
{
public:
	using runtime_error::runtime_error;
};

/**
 * @brief Memory error.
 *
 * Corrupted memory or allocation error.
*/
class memory_error : public runtime_error
{
public:
	using runtime_error::runtime_error;
};

/**
 * @brief An access violation.
*/
class access_violation : public runtime_error
{
public:
	using runtime_error::runtime_error;
};

/**
 * @brief The base class for arithmetic errors.
*/
class arithmetic_error : public runtime_error
{
public:
	using runtime_error::runtime_error;
};

/**
 * @brief An invalid division or modulo by zero.
*/
class zero_division_error : public arithmetic_error
{
public:
	using arithmetic_error::arithmetic_error;
};

/**
 * @brief An arithmetic operation overflowed.
*/
class overflow_error : public arithmetic_error
{
public:
	using arithmetic_error::arithmetic_error;
};

}
}