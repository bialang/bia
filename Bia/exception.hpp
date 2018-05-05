#pragma once

#include <string>
#include <cstdio>
#include <typeinfo>
#include <exception>

#define BIA_IMPLEMENTATION_EXCEPTION(msg) bia::exception::implementation_error(msg, __FILE__, __LINE__)
#define BIA_EM_UNSUPPORTED_TYPE "Type is not supported."
#define BIA_EM_UNEXPECTED_TYPE "Unexpected type."
#define BIA_EM_UNDEFINED_MEMBER "Undefined member."
#define BIA_EM_NULL_INSTANCE "Cannot access member without an instance."
#define BIA_EM_REPORT_LIMIT "Report bundle limit reached."
#define BIA_EM_LIMITATION_EXCEEDED "Limitation has been exceeded."
#define BIA_EM_INVALID_ARGUMENT "Invalid arguments."
#define BIA_EM_INVALID_ENCODING "Invalid encoding."
#define BIA_EM_NOT_ENOUGH_SPACE "Not enough space."
#define BIA_EM_INVALID_UNICODE "Invalid unicode character."
#define BIA_EM_UNSUPPORTED_EXECUTE "This type cannot be executed."
#define BIA_EM_UNSUPPORTED_TEST "This member cannot be tested."
#define BIA_EM_UNSUPPORTED_TEST_OPERATOR "Unsupported test operator."
#define BIA_EM_UNSUPPORTED_INSTANTIATION "Instantiation is not supported."
#define BIA_EM_FAILED_ALLOCATION "Allocation failed."
#define BIA_EM_FAILED_MEMORY_PROTECTION "Cannot change protection of the memory address."


namespace bia
{
namespace exception
{

/**
 * @brief A Bia error.
 *
 * Every thrown exception of Bia will inherit this.
*/
class bia_error
{
public:
	/**
	 * Destructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	*/
	virtual ~bia_error() noexcept = default;
};

/**
 * @brief A logical error.
 *
 * Every logical exception of Bia will inherit this.
 *
 * @see @ref runtime_error
*/
class logic_error : public bia_error, public std::logic_error
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit logic_error(const std::string & _message) : std::logic_error(_message)
	{
	}
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit logic_error(const char * _message) : std::logic_error(_message)
	{
	}
};

/**
 * @brief A runtime exception.
 *
 * Every runtime exception of Bia will inherit this.
 *
 * @see @ref logic_error
*/
class runtime_error : public bia_error, public std::runtime_error
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit runtime_error(const std::string & _message) : std::runtime_error(_message)
	{
	}
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit runtime_error(const char * _message) : std::runtime_error(_message)
	{
	}
};

/**
 * @brief Indicates an invalid cast.
 *
 * Indicates an invalid type cast.
*/
class invalid_type : public logic_error
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit invalid_type(const std::string & _message) : logic_error(_message)
	{
	}
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit invalid_type(const char * _message) : logic_error(_message)
	{
	}
};

/**
 * @brief Indicates an invalid encoding.
 *
 * Indicates an invalid encoding or an encoding error.
*/
class encoding_error : public logic_error
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit encoding_error(const std::string & _message) : logic_error(_message)
	{
	}
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit encoding_error(const char * _message) : logic_error(_message)
	{
	}
};

/**
 * @brief One or more argument errors.
 *
 * Invalid argument count, nullpoiter or invalid arguments.
*/
class argument_error : public logic_error
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit argument_error(const std::string & _message) : logic_error(_message)
	{
	}
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit argument_error(const char * _message) : logic_error(_message)
	{
	}
};

/**
 * @brief Unresolvable symbol.
 *
 * Symbol cannot be resolved or it is in an undefined state.
*/
class symbol_error final : public runtime_error
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit symbol_error(const std::string & _message) : runtime_error(_message)
	{
	}
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit symbol_error(const char * _message) : runtime_error(_message)
	{
	}
};

/**
 * @brief Limitation error.
 *
 * A limitiation has been exceeded.
*/
class limitation_error final : public runtime_error
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit limitation_error(const std::string & _message) : runtime_error(_message)
	{
	}
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit limitation_error(const char * _message) : runtime_error(_message)
	{
	}
};

/**
 * @brief Execution error.
 *
 * The performed call is invalid.
*/
class execution_error final : public runtime_error
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit execution_error(const std::string & _message) : runtime_error(_message)
	{
	}
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit execution_error(const char * _message) : runtime_error(_message)
	{
	}
};

/**
 * @brief Operator error.
 *
 * The operator is invalid or not supported.
*/
class operator_error final : public runtime_error
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit operator_error(const std::string & _message) : runtime_error(_message)
	{
	}
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit operator_error(const char * _message) : runtime_error(_message)
	{
	}
};

/**
 * @brief Memory error.
 *
 * Corrupted memory or allocation error.
*/
class memory_error final : public runtime_error
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit memory_error(const std::string & _message) : runtime_error(_message)
	{
	}
	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _message The message.
	*/
	explicit memory_error(const char * _message) : runtime_error(_message)
	{
	}
};

}
}