#pragma once

#include <cstdint>

#include "member.hpp"
#include "operator.hpp"
#include "interpreter_string.hpp"


namespace bia
{
namespace grammar
{

/**
 * @brief A report from the interpreter.
 *
 * A report holding information about the structure of the Bia source code.
 *
 * @see @ref report_bundle
*/
struct report
{
	typedef uint32_t custom_type;
	typedef uint32_t rule_type;
	typedef uint16_t token_type;

	constexpr static int custom_bits = 27;
	constexpr static int rule_bits = 22;
	constexpr static int token_bits = 32 - rule_bits;

	enum class TYPE : uint32_t
	{
		STRING,
		INT_VALUE,
		FLOAT_VALUE,
		DOUBLE_VALUE,
		MEMBER,
		OPERATOR_CODE,
		KEYWORD,
		BEGIN,
		END,
		EMPTY_CHILD
	};

	TYPE type : 32 - custom_bits;
	uint32_t custom_parameter : custom_bits;
	uint32_t rule_id : rule_bits;
	uint32_t token_id : token_bits;
	union
	{
		const char * string;
		int64_t intValue;
		float floatValue;
		double doubleValue;
		const report *  end;
		framework::member * member;
		framework::OPERATOR operatorCode;
		INTERPRETER_STRING keyword;
	} content;
};

}
}