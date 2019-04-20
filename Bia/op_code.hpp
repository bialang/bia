#pragma once

#include <cstdint>
#include <type_traits>
#include <limits>
#include <typeinfo>

#include "exception.hpp"
#include "output_stream.hpp"
#include "string_manager.hpp"


namespace bia
{
namespace machine
{
namespace virtual_machine
{

typedef uint16_t op_code_t;
typedef int32_t member_index_t;
typedef int8_t tiny_member_index_t;

class virtual_translator;

struct index
{
	member_index_t value;
	virtual ~index() = default;
	bool operator==(const index & _right) const noexcept
	{
		return value == _right.value && typeid(this) == typeid(&_right);
	}
	bool operator!=(const index & _right) const noexcept
	{
		return !this->operator==(_right);
	}

protected:
	friend virtual_translator;

	index(member_index_t _value)
	{
		if (_value < 0) {
			BIA_IMPLEMENTATION_ERROR;
		}

		value = _value;
	}
};

/**
 * A member index. This is a permanent index with the positive range.
 *
 * @see @ref index
*/
struct member_index : index
{
private:
	friend virtual_translator;

	using index::index;
};

/**
 * A temporary member index. This is a temporary index with the positive range.
 *
 * @see @ref index
*/
struct temp_index : index
{
private:
	friend virtual_translator;

	using index::index;
};

/**
 * A local member index. This is a temporary index with the negative range.
 *
 * @see @ref index
*/
struct local_index : index
{
private:
	friend virtual_translator;

	using index::index;
};

struct invalid_index : index
{
	invalid_index() noexcept : index(0)
	{
	}
};

enum MEMBER_OP_CODE_OPTION
{
	MOCO_PERMANENT,
	MOCO_TEMPORARY,
	MOCO_TINY_PERMANENT,
	MOCO_TINY_TEMPORARY,

	MOCO_COUNT
};

enum IMMEDIATE_INT_OP_CODE_OPTION
{
	IIOCO_INT8,
	IIOCO_INT32,

	IIOCO_COUNT
};

enum IMMEDIATE_OP_CODE_OPTION
{
	IOCO_STRING,
	IOCO_FLOAT,
	IOCO_INT64,
	IOCO_INT8,
	IOCO_INT32,

	IOCO_COUNT
};

enum OP_CODE : op_code_t
{
	/** P-Type instructions */
	OC_RETURN_VOID,
	OC_PUSH_TEST,

	/** int-Type instructions */
	OC_JUMP = OC_PUSH_TEST + IIOCO_COUNT,
	OC_JUMP_TRUE = OC_JUMP + IIOCO_COUNT,
	OC_JUMP_FALSE = OC_JUMP_TRUE + IIOCO_COUNT,

	/** I-Type instructions */
	OC_RETURN_IMMEDIATE = OC_JUMP_FALSE + IOCO_COUNT,
	OC_PUSH_IMMEDIATE = OC_RETURN_IMMEDIATE + IOCO_COUNT,

	/** M-Type instructions */
	OC_RETURN = OC_PUSH_IMMEDIATE + MOCO_COUNT,
	OC_PUSH = OC_RETURN + MOCO_COUNT,
	OC_TEST = OC_PUSH + MOCO_COUNT,
	OC_UNDEFINE = OC_TEST + MOCO_COUNT,
	OC_EXECUTE_VOID = OC_UNDEFINE + MOCO_COUNT,
	OC_EXECUTE_COUNT_VOID = OC_EXECUTE_VOID + MOCO_COUNT,
	OC_EXECUTE_FORMAT_VOID = OC_EXECUTE_COUNT_VOID + MOCO_COUNT,

	/** Mint-Type instructions */
	OC_INSTANTIATE_REGEX = OC_EXECUTE_FORMAT_VOID + MOCO_COUNT * IIOCO_COUNT,
	OC_INSTANTIATE_FUNCTION = OC_INSTANTIATE_REGEX + MOCO_COUNT * IIOCO_COUNT,

	/** MM-Type instructions */
	OC_EXECUTE = OC_INSTANTIATE_FUNCTION + MOCO_COUNT * MOCO_COUNT,
	OC_EXECUTE_COUNT = OC_EXECUTE + MOCO_COUNT * MOCO_COUNT,
	OC_EXECUTE_FORMAT = OC_EXECUTE_COUNT + MOCO_COUNT * MOCO_COUNT,
	OC_CLONE = OC_EXECUTE_FORMAT + MOCO_COUNT * MOCO_COUNT,
	OC_REFER = OC_CLONE + MOCO_COUNT * MOCO_COUNT,
	OC_COPY = OC_REFER + MOCO_COUNT * MOCO_COUNT,
	OC_TEST_MEMBER = OC_COPY + MOCO_COUNT * MOCO_COUNT,
	OC_OPERATOR_CALL_VOID = OC_TEST_MEMBER + MOCO_COUNT * MOCO_COUNT,

	/** MI-Type instructions */
	OC_INSTANTIATE = OC_OPERATOR_CALL_VOID + MOCO_COUNT * IOCO_COUNT,
	OC_TEST_IMMEDIATE = OC_INSTANTIATE + MOCO_COUNT * IOCO_COUNT,
	OC_TEST_IMMEDIATE_REVERSE = OC_TEST_IMMEDIATE + MOCO_COUNT * IOCO_COUNT,
	OC_OPERATOR_CALL_IMMEDIATE_VOID = OC_TEST_IMMEDIATE_REVERSE + MOCO_COUNT * IOCO_COUNT,
	OC_OPERATOR_CALL_IMMEDIATE_REVERSE_VOID = OC_OPERATOR_CALL_IMMEDIATE_VOID + MOCO_COUNT * IOCO_COUNT,

	/*** MMint-Type instructions */
	OC_OBJECT_MEMBER = OC_OPERATOR_CALL_IMMEDIATE_REVERSE_VOID + MOCO_COUNT * MOCO_COUNT * IIOCO_COUNT,

	/** MMM-Type instructions */
	OC_OPERATOR_CALL = OC_OBJECT_MEMBER + MOCO_COUNT * MOCO_COUNT * MOCO_COUNT,

	/** MMI-Type instructions */
	OC_OPERATOR_CALL_IMMEDIATE = OC_OPERATOR_CALL + MOCO_COUNT * MOCO_COUNT * IOCO_COUNT,
	OC_OPERATOR_CALL_IMMEDIATE_REVERSE = OC_OPERATOR_CALL_IMMEDIATE + MOCO_COUNT * MOCO_COUNT * IOCO_COUNT,
};

class op_code
{
public:
	static void write_p_type(stream::output_stream & _output, OP_CODE _operation)
	{
		_output.write_all(_operation);
	}
	template<typename Type, bool Optimize = true>
	static void write_int_type(stream::output_stream & _output, OP_CODE _operation, Type _int)
	{
		auto _option = int_option<Optimize>(_int);

		_output.write_all(static_cast<op_code_t>(_operation - _option));

		write_int<Optimize>(_output, _int);
	}
	template<typename Type, bool Optimize = true>
	static void write_i_type(stream::output_stream & _output, OP_CODE _operation, Type _immediate)
	{
		auto _option = immediate_option<Optimize>(_immediate);

		_output.write_all(static_cast<op_code_t>(_operation - _option));

		write_immediate<Optimize>(_output, _immediate);
	}
	template<bool Optimize = true>
	static void write_m_type(stream::output_stream & _output, OP_CODE _operation, const index & _member)
	{
		auto _option = member_option<Optimize>(_member);

		_output.write_all(static_cast<op_code_t>(_operation - _option));

		write_member<Optimize>(_output, _member);
	}
	template<typename Type, bool Optimize = true>
	static void write_mint_type(stream::output_stream & _output, OP_CODE _operation, const index & _member, Type _int)
	{
		auto _option0 = member_option<Optimize>(_member);
		auto _option1 = int_option<Optimize>(_int);

		_output.write_all(static_cast<op_code_t>(_operation - (_option0 * IIOCO_COUNT + _option1)));

		write_member<Optimize>(_output, _member);
		write_int<Optimize>(_output, _int);
	}
	template<bool Optimize = true>
	static void write_mm_type(stream::output_stream & _output, OP_CODE _operation, const index & _member0, const index & _member1)
	{
		auto _option0 = member_option<Optimize>(_member0);
		auto _option1 = member_option<Optimize>(_member1);

		_output.write_all(static_cast<op_code_t>(_operation - (_option0 * MOCO_COUNT + _option1)));

		write_member<Optimize>(_output, _member0);
		write_member<Optimize>(_output, _member1);
	}
	template<typename Type, bool Optimize = true>
	static void write_mi_type(stream::output_stream & _output, OP_CODE _operation, const index & _member, Type _immediate)
	{
		auto _option0 = member_option<Optimize>(_member);
		auto _option1 = immediate_option<Optimize>(_immediate);

		_output.write_all(static_cast<op_code_t>(_operation - (_option0 * IOCO_COUNT + _option1)));

		write_member<Optimize>(_output, _member);
		write_immediate<Optimize>(_output, _immediate);
	}
	template<typename Type, bool Optimize = true>
	static void write_mmint_type(stream::output_stream & _output, OP_CODE _operation, const index & _member0, const index & _member1, Type _int)
	{
		auto _option0 = member_option<Optimize>(_member0);
		auto _option1 = member_option<Optimize>(_member1);
		auto _option2 = int_option<Optimize>(_int);

		_output.write_all(static_cast<op_code_t>(_operation - ((_option0 * MOCO_COUNT + _option1) * IIOCO_COUNT + _option2)));

		write_member<Optimize>(_output, _member0);
		write_member<Optimize>(_output, _member1);
		write_int<Optimize>(_output, _int);
	}
	template<bool Optimize = true>
	static void write_mmm_type(stream::output_stream & _output, OP_CODE _operation, const index & _member0, const index & _member1, const index & _member2)
	{
		auto _option0 = member_option<Optimize>(_member0);
		auto _option1 = member_option<Optimize>(_member1);
		auto _option2 = member_option<Optimize>(_member2);

		_output.write_all(static_cast<op_code_t>(_operation - ((_option0 * MOCO_COUNT + _option1) * MOCO_COUNT + _option2)));

		write_member<Optimize>(_output, _member0);
		write_member<Optimize>(_output, _member1);
		write_member<Optimize>(_output, _member2);
	}
	template<typename Type, bool Optimize = true>
	static void write_mmi_type(stream::output_stream & _output, OP_CODE _operation, const index & _member0, const index & _member1, Type _immediate)
	{
		auto _option0 = member_option<Optimize>(_member0);
		auto _option1 = member_option<Optimize>(_member1);
		auto _option2 = immediate_option<Optimize>(_immediate);

		_output.write_all(static_cast<op_code_t>(_operation - ((_option0 * MOCO_COUNT + _option1) * IOCO_COUNT + _option2)));

		write_member<Optimize>(_output, _member0);
		write_member<Optimize>(_output, _member1);
		write_immediate<Optimize>(_output, _immediate);
	}
	template<typename Type>
	constexpr static size_t jump_instruction_length()
	{
		static_assert(std::is_integral<Type>::value && (sizeof(Type) == 4 || sizeof(Type) == 1), "Unsupported int type.");

		return sizeof(Type) + 2;
	}

private:
	template<bool Optimize, typename Type>
	static typename std::enable_if<(std::is_integral<Type>::value && sizeof(Type) <= 4)>::type write_int(stream::output_stream & _output, Type _int)
	{
		if (int_option<Optimize, Type>(_int) == IIOCO_INT8) {
			_output.write_all(static_cast<int8_t>(_int));
		} else {
			_output.write_all(_int);
		}
	}
	template<bool Optimize>
	static void write_member(stream::output_stream & _output, const index & _member)
	{
		auto _index = _member.value;

		if (dynamic_cast<const local_index*>(&_member)) {
			_index = -_index - 1;
		}

		if (Optimize && _member.value <= std::numeric_limits<tiny_member_index_t>::max()) {
			_output.write_all(static_cast<tiny_member_index_t>(_index));
		} else {
			_output.write_all(_index);
		}
	}
	template<bool Optimize, typename Type>
	static typename std::enable_if<std::is_integral<Type>::value>::type write_immediate(stream::output_stream & _output, Type _immediate)
	{
		static_assert(std::is_same<Type, int32_t>::value || std::is_same<Type, int8_t>::value || std::is_same<Type, int64_t>::value, "Unsupported immediate type.");

		if (Optimize && _immediate >= std::numeric_limits<int8_t>::min() && _immediate <= std::numeric_limits<int8_t>::max()) {
			_output.write_all(static_cast<int8_t>(_immediate));
		} else if (Optimize && _immediate >= std::numeric_limits<int32_t>::min() && _immediate <= std::numeric_limits<int32_t>::max()) {
			_output.write_all(static_cast<int32_t>(_immediate));
		} else {
			_output.write_all(_immediate);
		}
	}
	template<bool Optimize>
	static void write_immediate(stream::output_stream & _output, double _immediate)
	{
		_output.write_all(_immediate);
	}
	template<bool Optimize>
	static void write_immediate(stream::output_stream & _output, string_manager::utf8_index_t _immediate)
	{
		_output.write_all(_immediate.index);
	}
	template<bool Optimize, typename Type>
	static typename std::enable_if<(std::is_integral<Type>::value && sizeof(Type) <= 4), IMMEDIATE_INT_OP_CODE_OPTION>::type int_option(Type _int)
	{
		return Optimize && (std::is_signed<Type>::value && _int >= std::numeric_limits<int8_t>::min() && _int <= std::numeric_limits<int8_t>::max() || _int <= std::numeric_limits<uint8_t>::max()) || sizeof(Type) == 1 ? IIOCO_INT8 : IIOCO_INT32;
	}
	template<bool Optimize>
	static MEMBER_OP_CODE_OPTION member_option(const index & _member)
	{
		int _option = Optimize && _member.value <= std::numeric_limits<tiny_member_index_t>::max() ? MOCO_TINY_PERMANENT : MOCO_PERMANENT;

		if (dynamic_cast<const member_index*>(&_member)) {
			_option += MOCO_PERMANENT;
		} else if (dynamic_cast<const temp_index*>(&_member) || dynamic_cast<const local_index*>(&_member)) {
			_option += MOCO_TEMPORARY;
		} else {
			BIA_IMPLEMENTATION_ERROR;
		}

		return static_cast<MEMBER_OP_CODE_OPTION>(_option);
	}
	template<bool Optimize, typename Type>
	static IMMEDIATE_OP_CODE_OPTION immediate_option(Type _immediate)
	{
		static_assert(std::is_same<Type, int32_t>::value || std::is_same<Type, int8_t>::value || std::is_same<Type, int64_t>::value || std::is_same<Type, double>::value, "Unsupported immediate type.");

		if (Optimize) {
			if (std::is_integral<Type>::value) {
				if (_immediate >= std::numeric_limits<int8_t>::min() && _immediate <= std::numeric_limits<int8_t>::max()) {
					return IOCO_INT8;
				} else if (_immediate >= std::numeric_limits<int32_t>::min() && _immediate <= std::numeric_limits<int32_t>::max()) {
					return IOCO_INT32;
				}

				return IOCO_INT64;
			}
		} else {
			if (std::is_same<Type, int32_t>::value) {
				return IOCO_INT32;
			} else if (std::is_same<Type, int8_t>::value) {
				return IOCO_INT8;
			} else if (std::is_same<Type, int64_t>::value) {
				return IOCO_INT64;
			}
		}

		return IOCO_FLOAT;
	}
	template<bool Optimize>
	static IMMEDIATE_OP_CODE_OPTION immediate_option(string_manager::utf8_index_t _immediate)
	{
		return IOCO_STRING;
	}
};

}
}
}