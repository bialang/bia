#pragma once

#include <cstdint>
#include <type_traits>

#include "operator.hpp"
#include "keyword.hpp"
#include "output_stream.hpp"
#include "input_stream.hpp"
#include "big_int.hpp"
#include "schein.hpp"
#include "string_manager.hpp"


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
	typedef uint16_t custom_t;
	typedef uint8_t rule_t;
	typedef uint8_t token_t;
	typedef const char* member_t;

	constexpr static auto type_bits = 4;
	constexpr static auto custom_bits = 12;
	constexpr static auto rule_bits = 8;
	constexpr static auto token_bits = 8;

	enum class TYPE : uint32_t
	{
		INT_VALUE,
		DOUBLE_VALUE,
		BIG_INT_VALUE,
		STRING,
		REGEX,
		MEMBER,
		KEYWORD,
		OPERATOR_CODE,
		BEGIN,
		END,
		RULE_TOKEN,
		EMPTY_CHILD
	};

	enum STRING_TYPE
	{
		ASCII = 1,
		UTF8,
		UTF16,
		UTF32
	};

	TYPE type : type_bits;
	uint32_t custom_parameter : custom_bits;
	uint32_t rule_id : rule_bits;
	uint32_t token_id : token_bits;
	//uint32_t size;
	union
	{
		int64_t int_value;
		double double_value;
		detail::big_int * big_int_value;
		machine::string_manager::utf8_index_t string;
		machine::schein::regex_index_t regex;
		/** The non-zero terminated name of the member. See @a size for the length. */
		member_t member;
		KEYWORD_ID keyword;
		framework::operator_t operator_code;
		const report * end;
	} content;
};

}
}
