#include "disassembler.hpp"
#include "exception.hpp"
#include "link.hpp"
#include "member.hpp"

#include <cstdio>
#include <algorithm>

#define BIA_FUNCTION_ENTRY(x) { union { decltype(&x) function; const void * address; } _converter; _converter.function = &x; _function_map.emplace(_converter.address, std::string(#x "<") + typeid(&x).name() + ">"); }


namespace bia
{
namespace machine
{

disassembler::instruction_list disassembler::_instructions = disassembler::init_instructions();
disassembler::function_map disassembler::_function_map = disassembler::init_function_map();

disassembler::disassembler(const void * _context_address) noexcept
{
	this->_context_address = _context_address;
}

void disassembler::disassemble(const void * _code, size_t _size) const
{
	auto _buffer = static_cast<const uint8_t*>(_code);

	while (_size) {
		// Check all instruction
		for (auto & _instruction : _instructions) {
			if (_instruction.size <= _size) {
				uint64_t _op_code = 0;

				memcpy(&_op_code, _buffer, std::min<uint8_t>(8, _instruction.size));

				//This it the instruction
				if ((_op_code & _instruction.mask) == _instruction.op_code) {
					printf("%p: ", _buffer);

					_instruction.callback(this, _buffer);

					_buffer += _instruction.size;
					_size -= _instruction.size;

					goto gt_continue;
				}
			}
		}

		throw exception::bia_error();

		// throw exception::Exception("hi");

		break;

	gt_continue:;
	}
}

const char * disassembler::get_name(const void * _address) const noexcept
{
	// The context
	if (_address == _context_address) {
		return "this";
	}

	// Search function map
	auto _result = _function_map.find(_address);

	if (_result != _function_map.end()) {
		return _result->second.c_str();
	}

	///TODO: iterate through variables

	return nullptr;
}

disassembler::instruction_list disassembler::init_instructions()
{
	instruction_list _instructions;
	auto _byteswap = [](uint64_t _value) {
#if defined(BIA_COMPILER_MSVC)
		return _byteswap_uint64(_value);
#endif
	};
	auto _add_instruction = [&](uint64_t _op_code, uint8_t _first_bits, uint8_t _instruction_size, instruction::callback_function && _callback) {
		instruction _instruction{};

		_instruction.op_code = _byteswap(_op_code) >> (8 - _instruction_size) * 8;
		_instruction.mask = ~(~0ull << (_first_bits & 0xf8)) | (0xff00ull >> (_first_bits & 0x7) & 0xff) << (_first_bits & 0xf8);
		_instruction.callback = std::move(_callback);
		_instruction.size = _instruction_size;

		_instructions.emplace_back(std::move(_instruction));
	};

#if defined(BIA_ARCHITECTURE_X86)
	static auto _register_name = [](uint8_t _register) {
		switch (_register) {
		case 0:
			return "eax";
		case 1:
			return "ecx";
		case 4:
			return "esp";
		case 5:
			return "ebp";
		default:
			return "unkown";
		}
	};

	// Only opcode
	_add_instruction(0xc9, 8, 1, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		puts("leave");
	});
	_add_instruction(0xc3, 8, 1, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		puts("ret");
	});

	// Opcode + register
	_add_instruction(0x50, 5, 1, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("push\t%s\n", _register_name(*_buffer & 07));
	});
	_add_instruction(0xff00 | 0320, 13, 2, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("call\t%s\n", _register_name(_buffer[1] & 07));
	});

	// Opcode + register + register
	_add_instruction(0x8900 | 0300, 10, 2, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("mov\t%s,%s\n", _register_name(_buffer[1] & 07), _register_name(_buffer[1] >> 3 & 07));
	});
	_add_instruction(0x8b0000 | 0100 << 8, 10, 3, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("mov\t%s,[%s%+hhi]\n", _register_name(_buffer[1] >> 3 & 07), _register_name(_buffer[1] & 07), _buffer[2]);
	});
	_add_instruction(0x8b0000000000 | 0200ll << 32, 10, 6, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("mov\t%s,[%s%+i]\n", _register_name(_buffer[1] >> 3 & 07), _register_name(_buffer[1] & 07), *reinterpret_cast<const int32_t*>(_buffer + 2));
	});
	_add_instruction(0x8400 | 0300, 10, 2, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("test_8\t%s,%s\n", _register_name(_buffer[1] & 07), _register_name(_buffer[1] >> 3 & 07));
	});
	_add_instruction(0x8500 | 0300, 10, 2, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("test\t%s,%s\n", _register_name(_buffer[1] & 07), _register_name(_buffer[1] >> 3 & 07));
	});
	_add_instruction(0x8d0000 | 0100 << 8, 10, 3, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("lea\t%s,[%s%+hhi]\n", _register_name(_buffer[1] >> 3 & 07), _register_name(_buffer[1] & 07), _buffer[2]);
	});
	_add_instruction(0x8d0000000000 | 0200ll << 32, 10, 6, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("lea\t%s,[%s%+i]\n", _register_name(_buffer[1] >> 3 & 07), _register_name(_buffer[1] & 07), *reinterpret_cast<const int32_t*>(_buffer + 2));
	});


	// Opcode + register + 32 bit constant
	_add_instruction(0xff0000000000 | 0260ll << 32, 13, 6, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("push\t[%s%+i]\n", _register_name(_buffer[1] & 07), *reinterpret_cast<const int32_t*>(_buffer + 2));
	});
	_add_instruction(0xb800000000, 5, 5, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		auto szName = _disassembler->get_name(*reinterpret_cast<void* const*>(_buffer + 1));

		if (szName)
			printf("mov\t%s,%s at 0x%x\n", _register_name(*_buffer & 07), szName, *reinterpret_cast<const int32_t*>(_buffer + 1));
		else
			printf("mov\t%s,%i\n", _register_name(*_buffer & 07), *reinterpret_cast<const int32_t*>(_buffer + 1));
	});
	_add_instruction(0x0500000000, 8, 5, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("add\teax,%i\n", *reinterpret_cast<const int32_t*>(_buffer + 1));
	});
	_add_instruction(0x810000000000 | 0300ll << 32, 13, 6, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("add\t%s,%i\n", _register_name(_buffer[1] & 07), *reinterpret_cast<const int32_t*>(_buffer + 2));
	});
	_add_instruction(0x2d00000000, 8, 5, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("sub\teax,%i\n", *reinterpret_cast<const int32_t*>(_buffer + 1));
	});
	_add_instruction(0x810000000000 | 0350ll << 32, 13, 6, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("sub\t%s,%i\n", _register_name(_buffer[1] & 07), *reinterpret_cast<const int32_t*>(_buffer + 2));
	});

	// Opcode + register + 8 bit constant
	_add_instruction(0xff0000 | 0160 << 8, 13, 3, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("push\t[%s%+hhi]\n", _register_name(_buffer[1] & 07), _buffer[2]);
	});
	_add_instruction(0x0400, 8, 2, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("add\teax,%hhi\n", _buffer[1]);
	});
	_add_instruction(0x830000 | 0300 << 8, 13, 3, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("add\t%s,%hhi\n", _register_name(_buffer[1] & 07), _buffer[2]);
	});
	_add_instruction(0x2c00, 8, 2, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("sub\teax,%hhi\n", _buffer[1]);
	});
	_add_instruction(0x830000 | 0350 << 8, 13, 3, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("sub\t%s,%hhi\n", _register_name(_buffer[1] & 07), _buffer[2]);
	});

	// Opcode + 32 bit constant
	_add_instruction(0x6800000000, 8, 5, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		auto szName = _disassembler->get_name(*reinterpret_cast<void* const*>(_buffer + 1));

		if (szName)
			printf("push\t%s at 0x%x\n", szName, *reinterpret_cast<const int32_t*>(_buffer + 1));
		else
			printf("push\t%i\n", *reinterpret_cast<const int32_t*>(_buffer + 1));
	});
	_add_instruction(0xe900000000, 8, 5, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("jmp\t%p\n", _buffer + 5 + *reinterpret_cast<const int32_t*>(_buffer + 1));
	});
	_add_instruction(0x0f8400000000, 16, 6, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("je\t%p\n", _buffer + 6 + *reinterpret_cast<const int32_t*>(_buffer + 2));
	});
	_add_instruction(0x0f8500000000, 16, 6, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("jne\t%p\n", _buffer + 6 + *reinterpret_cast<const int32_t*>(_buffer + 2));
	});

	// Opcode + 8 bit constant
	_add_instruction(0x6a00, 8, 2, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("push\t%hhi\n", static_cast<int8_t>(_buffer[1]));
	});
	_add_instruction(0xeb00, 8, 2, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("jmp\t%p\n", _buffer + 2 + static_cast<int8_t>(_buffer[1]));
	});
	_add_instruction(0x7400, 8, 2, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("je\t%p\n", _buffer + 2 + static_cast<int8_t>(_buffer[1]));
	});
	_add_instruction(0x7500, 8, 2, [](const disassembler * _disassembler, const uint8_t * _buffer) {
		printf("jne\t%p\n", _buffer + 2 + static_cast<int8_t>(_buffer[1]));
	});
#endif

	return _instructions;
}

disassembler::function_map disassembler::init_function_map()
{
	function_map _function_map;

	BIA_FUNCTION_ENTRY(machine_context::create_on_stack);
	BIA_FUNCTION_ENTRY(machine_context::destroy_from_stack);

	BIA_FUNCTION_ENTRY(machine::link::instantiate_int32);
	BIA_FUNCTION_ENTRY(machine::link::instantiate_int64);
	BIA_FUNCTION_ENTRY(machine::link::instantiate_int_0);
	BIA_FUNCTION_ENTRY(machine::link::instantiate_int_1);
	BIA_FUNCTION_ENTRY(machine::link::instantiate_int_n1);
	BIA_FUNCTION_ENTRY(machine::link::instantiate_double);
	BIA_FUNCTION_ENTRY(machine::link::instantiate_string);

	BIA_FUNCTION_ENTRY(framework::member::print);
	BIA_FUNCTION_ENTRY(machine::link::print_int32);
	BIA_FUNCTION_ENTRY(machine::link::print_int64);
	BIA_FUNCTION_ENTRY(machine::link::print_true);
	BIA_FUNCTION_ENTRY(machine::link::print_false);
	BIA_FUNCTION_ENTRY(machine::link::print_bool);
	BIA_FUNCTION_ENTRY(machine::link::print_double);
	BIA_FUNCTION_ENTRY(machine::link::print_string);

	BIA_FUNCTION_ENTRY(framework::member::copy);
	BIA_FUNCTION_ENTRY(framework::member::refer);
	BIA_FUNCTION_ENTRY(framework::member::clone);

	BIA_FUNCTION_ENTRY(framework::member::execute);
	BIA_FUNCTION_ENTRY(framework::member::execute_count);
	BIA_FUNCTION_ENTRY(framework::member::execute_format);

	BIA_FUNCTION_ENTRY(framework::member::get_flags);

	/*BIA_FUNCTION_ENTRY(framework::member::Instantiate);
	BIA_FUNCTION_ENTRY(framework::member::InstantiateCount);
	BIA_FUNCTION_ENTRY(framework::member::InstantiateFormat);*/

	BIA_FUNCTION_ENTRY(framework::member::operator_call);
	BIA_FUNCTION_ENTRY(framework::member::operator_call_int32);
	BIA_FUNCTION_ENTRY(framework::member::operator_call_int64);
	BIA_FUNCTION_ENTRY(framework::member::operator_call_double);
	BIA_FUNCTION_ENTRY(machine::link::operation_int32);
	BIA_FUNCTION_ENTRY(machine::link::operation_int64);
	BIA_FUNCTION_ENTRY(machine::link::operation_double);

	/*BIA_FUNCTION_ENTRY(framework::member::);
	BIA_FUNCTION_ENTRY(framework::member::OperatorAssignCallInt_32);
	BIA_FUNCTION_ENTRY(framework::member::OperatorAssignCallInt_64);
	BIA_FUNCTION_ENTRY(framework::member::OperatorAssignCallFloat);
	BIA_FUNCTION_ENTRY(framework::member::OperatorAssignCallDouble);

	BIA_FUNCTION_ENTRY(framework::member::OperatorSelfCall);*/

	BIA_FUNCTION_ENTRY(framework::member::test);
	BIA_FUNCTION_ENTRY(framework::member::test_member);
	BIA_FUNCTION_ENTRY(framework::member::test_int32);
	BIA_FUNCTION_ENTRY(framework::member::test_int64);
	BIA_FUNCTION_ENTRY(framework::member::test_double);

	BIA_FUNCTION_ENTRY(framework::member::to_int);
	BIA_FUNCTION_ENTRY(framework::member::to_double);

	return _function_map;
}

}
}