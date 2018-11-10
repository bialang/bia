#pragma once

#include <mpir/mpir.h>
#include <cstdint>
#include <type_traits>

#include "operator.hpp"
#include "interpreter_string.hpp"
#include "output_stream.hpp"
#include "input_stream.hpp"


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
		BIG_INT_VALUE,
		DOUBLE_VALUE,
		BIG_DOUBLE_VALUE,
		MEMBER,
		OPERATOR_CODE,
		KEYWORD,
		BEGIN,
		END,
		EMPTY_CHILD
	};

	enum STRING_TYPE
	{
		ASCII = 1,
		UTF8,
		UTF16,
		UTF32
	};

	TYPE type : 32 - custom_bits;
	uint32_t custom_parameter : custom_bits;
	uint32_t rule_id : rule_bits;
	uint32_t token_id : token_bits;
	union
	{
		/** A string buffer with a specific format. See @ref stream::string_stream for more information. */
		void * string;
		int64_t int_value;
		typename std::remove_extent<mpz_t>::type * big_int_value;
		double double_value;
		typename std::remove_extent<mpf_t>::type * * big_float_value;
		const report *  end;
		const char * member;
		framework::operator_type operator_code;
		INTERPRETER_STRING keyword;
	} content;
	
	/*void serialize(stream::output_stream & _output)
	{
		_output.write_all<uint32_t, uint32_t>(static_cast<uint32_t>(type) << custom_bits | custom_parameter, rule_id << token_bits | token_id);

		switch (type) {
		case TYPE::STRING:
		case TYPE::INT_VALUE:
			_output.write_all(content.int_value);

			break;
		case TYPE::DOUBLE_VALUE:
			_output.write_all(content.double_value);

			break;
		case TYPE::MEMBER:
		case TYPE::OPERATOR_CODE:
			_output.write_all(content.operator_code);

			break;
		case TYPE::KEYWORD:
			_output.write_all(content.keyword);

			break;
		case TYPE::BEGIN:
		case TYPE::END:
		case TYPE::EMPTY_CHILD:
		default:
			throw;
		}
	}
	void deserialize(stream::input_stream & _input)
	{
		auto _tmp = _input.read<uint32_t>();

		type = static_cast<TYPE>(_tmp >> custom_bits);
		custom_parameter = _tmp & ~uint32_t(0) << custom_bits;

		_tmp = _input.read<uint32_t>();

		rule_id = _tmp >> token_bits;
		token_id = _tmp & ~uint32_t(0) << token_bits;

		switch (type) {
		case TYPE::STRING:
		case TYPE::INT_VALUE:
			content.int_value = _input.read<int64_t>();

			break;
		case TYPE::DOUBLE_VALUE:
			content.double_value = _input.read<double>();

			break;
		case TYPE::MEMBER:
		case TYPE::OPERATOR_CODE:
			content.operator_code = _input.read<framework::operator_type>();

			break;
		case TYPE::KEYWORD:
			content.keyword = _input.read<INTERPRETER_STRING>();

			break;
		case TYPE::BEGIN:
		case TYPE::END:
		case TYPE::EMPTY_CHILD:
		default:
			throw;
		}
	}*/
};

}
}
