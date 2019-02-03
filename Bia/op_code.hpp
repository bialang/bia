#pragma once

#include <cstdint>
#include <type_traits>
#include <limits>

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
	MOCO_LOCAL,
	MOCO_TEMP,

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
	IOCO_INT32,
	IOCO_INT8,
	IOCO_INT64,
	IOCO_FLOAT,

	IOCO_COUNT
};

enum OP_CODE : op_code_t
{
	/** P-Type instructions: */
	OC_RETURN,

	/** I-Type instructions: */
	OC_SETUP,
	OC_JUMP,
	OC_JUMP_TRUE,
	OC_JUMP_FALSE,
	OC_PUSH_IMMEDIATE,

	/** M-Type instructions: */
	OC_PUSH,
	OC_TEST,
	OC_UNDEFINE,
	OC_EXECUTE_VOID,

	/** MM-Type instructions: */
	OC_EXECUTE,
	OC_CLONE,
	OC_REFER,
	OC_COPY,
	
	/** MI-Type instructions: */
	OC_INSTANTIATE,
};

class op_code
{
public:
	constexpr static auto op_code_mask = 0xff;
	constexpr static auto immediate_mask = 0;
	constexpr static auto member_mask = 0x03;
	constexpr static auto parameter_offset = 8;
	constexpr static auto immediate_offset = 0;
	constexpr static auto member_offset = 4;
	constexpr static auto immediate_bit_count = 0;
	constexpr static auto member_bit_count = 4;
	constexpr static auto tiny_bit = 0x80;

	static bool tiny_member(const index & _index) noexcept
	{
		return _index.value <= std::numeric_limits<tiny_member_index_t>::max();
	}
	static void write_return(stream::output_stream & _output) noexcept
	{
		_output.write_all(OC_RETURN);
	}
	static void write_setup(stream::output_stream & _output, uint32_t _count) noexcept
	{
		_output.write_all(OC_SETUP, _count);
	}
	static void write_m_type(stream::output_stream & _output, op_code_t _operation, const index & _index) noexcept
	{
		auto _tiny = tiny_member(_index);
		op_code_t _op_code = (_tiny ? tiny_bit << parameter_offset : 0) | _operation;

		if (dynamic_cast<const member_index*>(&_index)) {
			_op_code |= MOCO_MEMBER << member_offset + parameter_offset;
		} else if (dynamic_cast<const temp_index*>(&_index)) {
			_op_code |= MOCO_TEMP << member_offset + parameter_offset;
		} else if (dynamic_cast<const local_index*>(&_index)) {
			_op_code |= MOCO_LOCAL << member_offset + parameter_offset;
		} else {
			BIA_IMPLEMENTATION_ERROR;
		}

		_output.write_all(_op_code);

		if (_tiny) {
			_output.write_all(static_cast<tiny_member_index_t>(_index.value));
		} else {
			_output.write_all(_index.value);
		}
	}
};

}
}
}