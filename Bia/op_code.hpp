#pragma once

#include <cstdint>
#include <type_traits>
#include <limits>
#include <typeinfo>

#include "exception.hpp"
#include "output_stream.hpp"


namespace bia
{
namespace machine
{
namespace virtual_machine
{

typedef uint16_t op_code_t;
typedef uint32_t member_index_t;
typedef uint8_t tiny_member_index_t;

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

	index(member_index_t _value) noexcept
	{
		value = _value;
	}
};

struct member_index : index
{
private:
	friend virtual_translator;

	using index::index;
};

struct temp_index : index
{
private:
	friend virtual_translator;

	using index::index;
};

struct local_index : index
{
private:
	friend virtual_translator;

	using index::index;
};

struct invalid_index : index
{
	invalid_index() noexcept : index(~member_index_t(0))
	{
	}
};

enum MEMBER_OP_CODE_OPTION
{
	MOCO_MEMBER,
	//MOCO_LOCAL,
	MOCO_TEMP,
	MOCO_TINY_MEMBER,
	//MOCO_TINY_LOCAL,
	MOCO_TINY_TEMP,

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
	IOCO_FLOAT,
	IOCO_INT64,
	IOCO_INT8,
	IOCO_INT32,

	IOCO_COUNT
};

enum OP_CODE : op_code_t
{
	/** P-Type instructions */
	OC_RETURN,
	OC_PUSH_TEST,

	/** int-Type instructions */
	OC_SETUP = OC_PUSH_TEST + IIOCO_COUNT,
	OC_JUMP = OC_SETUP + IIOCO_COUNT,
	OC_JUMP_TRUE = OC_JUMP + IIOCO_COUNT,
	OC_JUMP_FALSE = OC_JUMP_TRUE + IIOCO_COUNT,

	/** I-Type instructions */
	OC_PUSH_IMMEDIATE = OC_JUMP_FALSE + IOCO_COUNT,

	/** M-Type instructions */
	OC_PUSH = OC_PUSH_IMMEDIATE + MOCO_COUNT,
	OC_TEST = OC_PUSH + MOCO_COUNT,
	OC_UNDEFINE = OC_TEST + MOCO_COUNT,
	OC_EXECUTE_VOID = OC_UNDEFINE + MOCO_COUNT,
	OC_EXECUTE_COUNT_VOID = OC_EXECUTE_VOID + MOCO_COUNT,
	OC_EXECUTE_FORMAT_VOID = OC_EXECUTE_COUNT_VOID + MOCO_COUNT,

	/** MM-Type instructions */
	OC_EXECUTE = OC_EXECUTE_FORMAT_VOID + MOCO_COUNT * MOCO_COUNT,
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

	/** MMM-Type instructions */
	OC_OPERATOR_CALL = OC_OPERATOR_CALL_IMMEDIATE_REVERSE_VOID + MOCO_COUNT * MOCO_COUNT * MOCO_COUNT,

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
	template<typename Type>
	static void write_int_type(stream::output_stream & _output, OP_CODE _operation, Type _int)
	{
		static_assert(std::is_integral<Type>::value && (sizeof(Type) == 4 || sizeof(Type) == 1), "Unsupported int type.");

		_output.write_all(static_cast<op_code_t>(_operation - (sizeof(Type) == 4 ? IIOCO_INT32 : IIOCO_INT8)), _int);
	}
	template<typename Type>
	static void write_i_type(stream::output_stream & _output, OP_CODE _operation, Type _immediate)
	{
		auto _option = immediate_option<Type>();

		_output.write_all(static_cast<op_code_t>(_operation - _option));

		write_immediate(_immediate);
	}
	static void write_m_type(stream::output_stream & _output, OP_CODE _operation, const index & _member)
	{
		auto _option = member_option(_member);

		_output.write_all(static_cast<op_code_t>(_operation - _option));

		write_member(_output, _member);
	}
	static void write_mm_type(stream::output_stream & _output, OP_CODE _operation, const index & _member0, const index & _member1)
	{
		auto _option0 = member_option(_member0);
		auto _option1 = member_option(_member1);

		_output.write_all(static_cast<op_code_t>(_operation - (_option0 * MOCO_COUNT + _option1)));
		
		write_member(_output, _member0);
		write_member(_output, _member1);
	}
	template<typename Type>
	static void write_mi_type(stream::output_stream & _output, OP_CODE _operation, const index & _member, Type _immediate)
	{
		auto _option0 = member_option(_member);
		auto _option1 = immediate_option<Type>();

		_output.write_all(static_cast<op_code_t>(_operation - (_option0 * IOCO_COUNT + _option1)));

		write_member(_output, _member);
		write_immediate(_immediate);
	}
	static void write_mmm_type(stream::output_stream & _output, OP_CODE _operation, const index & _member0, const index & _member1, const index & _member2)
	{
		auto _option0 = member_option(_member0);
		auto _option1 = member_option(_member1);
		auto _option2 = member_option(_member2);

		_output.write_all(static_cast<op_code_t>(_operation - ((_option0 * MOCO_COUNT + _option1) * MOCO_COUNT + _option2)));

		write_member(_output, _member0);
		write_member(_output, _member1);
		write_member(_output, _member2);
	}
	template<typename Type>
	static void write_mmi_type(stream::output_stream & _output, OP_CODE _operation, const index & _member0, const index & _member1, Type _immediate)
	{
		auto _option0 = member_option(_member0);
		auto _option1 = member_option(_member1);
		auto _option2 = immediate_option<Type>();

		_output.write_all(static_cast<op_code_t>(_operation - ((_option0 * MOCO_COUNT + _option1) * IOCO_COUNT + _option2)));

		write_member(_output, _member0);
		write_member(_output, _member1);
		write_immediate(_immediate);
	}
	template<typename Type>
	constexpr static size_t jump_instruction_length()
	{
		static_assert(std::is_integral<Type>::value && (sizeof(Type) == 4 || sizeof(Type) == 1), "Unsupported int type.");

		return sizeof(Type) + 2;
	}

private:
	static void write_member(stream::output_stream & _output, const index & _member)
	{
		if (_member.value <= std::numeric_limits<tiny_member_index_t>::max()) {
			_output.write_all(static_cast<tiny_member_index_t>(_member.value));
		} else {
			_output.write_all(_member.value);
		}
	}
	template<typename Type>
	static typename std::enable_if<std::is_integral<Type>::value>::type write_immediate(stream::output_stream & _output, Type _immediate)
	{
		static_assert(std::is_same<Type, int32_t>::value || std::is_same<Type, int8_t>::value || std::is_same<Type, int64_t>::value, "Unsupported immediate type.");

		if (_immediate >= std::numeric_limits<int8_t>::min() && _immediate <= std::numeric_limits<int8_t>::max()) {
			_output.write_all(static_cast<int8_t>(_immediate));
		} else if (_immediate >= std::numeric_limits<int32_t>::min() && _immediate <= std::numeric_limits<int32_t>::max()) {
			_output.write_all(static_cast<int32_t>(_immediate));
		} else {
			_output.write_all(_immediate);
		}
	}
	template<typename Type>
	static typename std::enable_if<std::is_same<Type, double>::value>::type write_immediate(stream::output_stream & _output, Type _immediate)
	{
		_output.write_all(_immediate);
	}
	static MEMBER_OP_CODE_OPTION member_option(const index & _member)
	{
		int _option = _member.value <= std::numeric_limits<tiny_member_index_t>::max() ? MOCO_TINY_MEMBER : MOCO_MEMBER;

		if (dynamic_cast<const member_index*>(&_member)) {
			_option += MOCO_MEMBER;
		} else if (dynamic_cast<const temp_index*>(&_member)) {
			_option += MOCO_TEMP;
		} else {
			BIA_IMPLEMENTATION_ERROR;
		}

		return static_cast<MEMBER_OP_CODE_OPTION>(_option);
	}
	template<typename Type>
	static IMMEDIATE_OP_CODE_OPTION immediate_option()
	{
		static_assert(std::is_same<Type, int32_t>::value || std::is_same<Type, int8_t>::value || std::is_same<Type, int64_t>::value || std::is_same<Type, double>::value, "Unsupported immediate type.");

		if (std::is_same<Type, int32_t>::value) {
			return IOCO_INT32;
		} else if (std::is_same<Type, int8_t>::value) {
			return IOCO_INT8;
		} else if (std::is_same<Type, int64_t>::value) {
			return IOCO_INT64;
		} else {
			return IOCO_FLOAT;
		}
	}
};

}
}
}