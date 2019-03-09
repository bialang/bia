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

inline const char * register_name32(int _register)
{
	switch (_register) {
	case 0:
		return "eax";
	case 1:
		return "ecx";
	case 2:
		return "edx";
	case 4:
		return "esp";
	case 5:
		return "ebp";
	default:
		return "unkown";
	}
}

#if defined(BIA_ARCHITECTURE_X86_32)
inline const char * register_name(int _register)
{
	return register_name32(_register);
}
#elif defined(BIA_ARCHITECTURE_X86_64)
inline const char * register_name64(int _register)
{
	switch (_register) {
	case 0:
		return "rax";
	case 1:
		return "rcx";
	case 4:
		return "rsp";
	case 5:
		return "rbp";
	default:
		return "unkown";
	}
}

inline const char * register_xmm(int _register)
{
	switch (_register) {
	case 0:
		return "xmm0";
	case 1:
		return "xmm1";
	case 2:
		return "xmm2";
	case 3:
		return "xmm3";
	default:
		return "unkown";
	}
}

inline const char * register_name(int _register)
{
	return register_name64(_register);
}
#endif


disassembler::instruction_list disassembler::_instructions = disassembler::init_instructions();
disassembler::function_map disassembler::_function_map = disassembler::init_function_map();

disassembler::disassembler(const void * _context_address) noexcept
{
	this->_context_address = _context_address;
}

void disassembler::disassemble(const void * _code, size_t _size) const
{
	/*auto _buffer = static_cast<const int8_t*>(_code);

	while (_size) {
		// Check all instruction
		for (auto & _instruction : _instructions) {
			if (_instruction.size <= _size) {
				uint64_t _op_code = 0;

				memcpy(&_op_code, _buffer, std::min<uint8_t>(8, _instruction.size));

				//This it the instruction
				if ((_op_code & _instruction.mask) == _instruction.op_code) {
					printf("%p:", _buffer);

					for (auto i = 0; i < 8; ++i) {
						if (i < _instruction.size) {
							printf(" %02x", static_cast<uint8_t>(_buffer[i]));
						} else {
							printf("   ");
						}
					}

					printf(" | ");

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
	}*/
}

const char * disassembler::name(const void * _address) const noexcept
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
#else
		_value = (_value & 0x00000000ffffffff) << 32 | (_value & 0xffffffff00000000) >> 32;
		_value = (_value & 0x0000ffff0000ffff) << 16 | (_value & 0xffff0000ffff0000) >> 16;
		_value = (_value & 0x00ff00ff00ff00ff) << 8 | (_value & 0xff00ff00ff00ff00) >> 8;

		return _value;
#endif
	};
	auto _instruction = [&](uint64_t _op_code, uint64_t _mask, uint8_t _instruction_size, instruction::callback_function && _callback) {
		instruction _instruction{};

		_instruction.op_code = _byteswap(_op_code) >> (8 - _instruction_size) * 8;
		_instruction.mask = _byteswap(_mask) >> (8 - _instruction_size) * 8;
		//_instruction.mask = ~(~0ull << (_first_bits & 0xf8)) | (0xff00ull >> (_first_bits & 0x7) & 0xff) << (_first_bits & 0xf8);
		_instruction.callback = std::move(_callback);
		_instruction.size = _instruction_size;

		_instructions.emplace_back(std::move(_instruction));
	};

/*#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)
	// Only opcode
	_instruction(0xc3, 0xff, 1, [](const disassembler * _disassembler, const int8_t * _buffer) {
		puts("ret");
	});

	// Opcode + register
	_instruction(0x50, 0xf8, 1, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("push\t%s\n", register_name(*_buffer & 07));
	});
	_instruction(0x58, 0xf8, 1, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("pop\t%s\n", register_name(*_buffer & 07));
	});
	_instruction(0xff00 | 0320, 0xfff8, 2, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("call\t%s\n", register_name(_buffer[1] & 07));
	});

	// Opcode + register + offset
	_instruction(0xff002400 | 0164 << 16, 0xffffff00, 4, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("push\t[esp%+hhi]\n", _buffer[3]);
	});
	_instruction((0xff0024LL | 0264 << 8) << 32, 0xffffffLL << 32, 7, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("push\t[%s%+i]\n", register_name(_buffer[1] & 07), *reinterpret_cast<const int32_t*>(_buffer + 3));
	});
	_instruction((0xff00 | 0160) << 8, 0xfff800, 3, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("push\t[%s%+hhi]\n", register_name(_buffer[1] & 07), _buffer[2]);
	});
	_instruction((0xff00LL | 0260) << 32, 0xfff8LL << 32, 6, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("push\t[%s%+i]\n", register_name(_buffer[1] & 07), *reinterpret_cast<const int32_t*>(_buffer + 2));
	});

	// Opcode + register + register
#if defined(BIA_ARCHITECTURE_X86_64)
	_instruction(0x488900 | 0300, 0xffffc0, 3, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("mov\t%s,%s\n", register_name64(_buffer[2] & 07), register_name64(_buffer[2] >> 3 & 07));
	});
#endif
	_instruction(0x8900 | 0300, 0xffc0, 2, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("mov\t%s,%s\n", register_name32(_buffer[1] & 07), register_name32(_buffer[1] >> 3 & 07));
	});
#if defined(BIA_ARCHITECTURE_X86_64)
	_instruction(0x483100 | 0300, 0xffffc0, 3, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("xor\t%s,%s\n", register_name64(_buffer[2] & 07), register_name64(_buffer[2] >> 3 & 07));
	});
#endif
	_instruction(0x3100 | 0300, 0xffc0, 2, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("xor\t%s,%s\n", register_name32(_buffer[1] & 07), register_name32(_buffer[1] >> 3 & 07));
	});

	// Opcode + destination + source + source offset
#if defined(BIA_ARCHITECTURE_X86_64)
	_instruction(0xf20f100000 | 0100 << 8, 0xffffffc000, 5, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("movsd\t%s,[%s%+hhi]\n", register_xmm(_buffer[3] >> 3 & 07), register_name64(_buffer[3] & 07), _buffer[4]);
	});
	_instruction((0xf20f1000LL | 0200) << 32, 0xffffffc0LL << 32, 8, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("movsd\t%s,[%s%+i]\n", register_xmm(_buffer[3] >> 3 & 07), register_name64(_buffer[3] & 07), *reinterpret_cast<const int32_t*>(_buffer + 4));
	});
	_instruction(0x488b002400 | 0104 << 16, 0xffffc7ff00, 5, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("mov\t%s,[rsp%+hhi]\n", register_name64(_buffer[2] >> 3 & 07), _buffer[4]);
	});
	_instruction((0x488b0024LL | 0204 << 8) << 32, 0xffffc7ffLL << 32, 8, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("mov\t%s,[rsp%+i]\n", register_name64(_buffer[2] >> 3 & 07), *reinterpret_cast<const int32_t*>(_buffer + 4));
	});
	_instruction((0x488b00 | 0100) << 8, 0xffffc000, 4, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("mov\t%s,[%s%+hhi]\n", register_name64(_buffer[2] >> 3 & 07), register_name64(_buffer[2] & 07), _buffer[3]);
	});
	_instruction((0x488b00LL | 0200) << 32, 0xffffc0LL << 32, 7, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("mov\t%s,[%s%+i]\n", register_name64(_buffer[2] >> 3 & 07), register_name64(_buffer[2] & 07), *reinterpret_cast<const int32_t*>(_buffer + 3));
	});
#endif
	_instruction(0x8b002400 | 0104 << 16, 0xffc7ff00, 4, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("mov\t%s,[%s%+hhi]\n", register_name32(_buffer[1] >> 3 & 07), register_name(_buffer[1] & 07), _buffer[3]);
	});
	_instruction((0x8b0024LL | 0204 << 8) << 32, 0xffc7ffLL << 32, 7, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("mov\t%s,[%s%+i]\n", register_name32(_buffer[1] >> 3 & 07), register_name(_buffer[1] & 07), *reinterpret_cast<const int32_t*>(_buffer + 3));
	});
	_instruction((0x8b00 | 0100) << 8, 0xffc000, 3, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("mov\t%s,[%s%+hhi]\n", register_name32(_buffer[1] >> 3 & 07), register_name(_buffer[1] & 07), _buffer[2]);
	});
	_instruction((0x8b00LL | 0200) << 32, 0xffc0LL << 32, 6, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("mov\t%s,[%s%+i]\n", register_name32(_buffer[1] >> 3 & 07), register_name(_buffer[1] & 07), *reinterpret_cast<const int32_t*>(_buffer + 2));
	});
#if defined(BIA_ARCHITECTURE_X86_64)
	_instruction(0x488d002400 | 0104 << 16, 0xffffc7ff00, 5, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("lea\t%s,[rsp%+hhi]\n", register_name64(_buffer[2] >> 3 & 07), _buffer[4]);
	});
	_instruction((0x488d0024LL | 0204 << 8) << 32, 0xffffc7ffLL << 32, 8, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("lea\t%s,[rsp%+i]\n", register_name64(_buffer[2] >> 3 & 07), *reinterpret_cast<const int32_t*>(_buffer + 4));
	});
	_instruction((0x488d00 | 0100) << 8, 0xffffc000, 4, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("lea\t%s,[%s%+hhi]\n", register_name64(_buffer[2] >> 3 & 07), register_name64(_buffer[2] & 07), _buffer[3]);
	});
	_instruction((0x488d00LL | 0200) << 32, 0xffffc0LL << 32, 7, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("lea\t%s,[%s%+i]\n", register_name64(_buffer[2] >> 3 & 07), register_name64(_buffer[2] & 07), *reinterpret_cast<const int32_t*>(_buffer + 3));
	});
#endif
	_instruction(0x8d002400 | 0104 << 16, 0xffc7ff00, 4, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("lea\t%s,[%s%+hhi]\n", register_name32(_buffer[1] >> 3 & 07), register_name(_buffer[1] & 07), _buffer[3]);
	});
	_instruction((0x8d0024LL | 0204 << 8) << 32, 0xffc7ffLL << 32, 7, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("lea\t%s,[%s%+i]\n", register_name32(_buffer[1] >> 3 & 07), register_name(_buffer[1] & 07), *reinterpret_cast<const int32_t*>(_buffer + 3));
	});
	_instruction((0x8d00 | 0100) << 8, 0xffc000, 3, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("lea\t%s,[%s%+hhi]\n", register_name32(_buffer[1] >> 3 & 07), register_name(_buffer[1] & 07), _buffer[2]);
	});
	_instruction((0x8d00LL | 0200) << 32, 0xffc0LL << 32, 6, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("lea\t%s,[%s%+i]\n", register_name32(_buffer[1] >> 3 & 07), register_name(_buffer[1] & 07), *reinterpret_cast<const int32_t*>(_buffer + 2));
	});

	// Opcode + register + imm8
#if defined(BIA_ARCHITECTURE_X86_64)
	_instruction((0x488300 | 0300) << 8, 0xfffff800, 4, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("add\t%s,%hhi\n", register_name64(_buffer[2] & 07), _buffer[3]);
	});
#endif
	_instruction((0x8300 | 0300) << 8, 0xfff800, 3, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("add\t%s,%hhi\n", register_name32(_buffer[1] & 07), _buffer[2]);
	});
#if defined(BIA_ARCHITECTURE_X86_64)
	_instruction((0x488300 | 0350) << 8, 0xfffff800, 4, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("sub\t%s,%hhi\n", register_name64(_buffer[2] & 07), _buffer[3]);
	});
#endif
	_instruction((0x8300 | 0350) << 8, 0xfff800, 3, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("sub\t%s,%hhi\n", register_name32(_buffer[1] & 07), _buffer[2]);
	});

	// Opcode + register + imm32
#if defined(BIA_ARCHITECTURE_X86_64)
	_instruction((0x48c700LL | 0300) << 32, 0xfffff8LL << 32, 7, [](const disassembler * _disassembler, const int8_t * _buffer) {
		if (auto _name = _disassembler->name(*reinterpret_cast<void* const*>(_buffer + 3))) {
			printf("mov\t%s, %s at 0x%x\n", register_name64(_buffer[2] & 07), _name, *reinterpret_cast<const int32_t*>(_buffer + 3));
		} else {
			printf("mov\t%s,%i\n", register_name64(_buffer[2] & 07), *reinterpret_cast<const int32_t*>(_buffer + 3));
		}
	});
#endif
	_instruction(0xb8LL << 32, 0xf8LL << 32, 5, [](const disassembler * _disassembler, const int8_t * _buffer) {
		if (auto _name = _disassembler->name(*reinterpret_cast<void* const*>(_buffer + 1))) {
			printf("mov\t%s, %s at 0x%x\n", register_name32(*_buffer & 07), _name, *reinterpret_cast<const int32_t*>(_buffer + 1));
		} else {
			printf("mov\t%s,%i\n", register_name32(*_buffer & 07), *reinterpret_cast<const int32_t*>(_buffer + 1));
	}
	});
#if defined(BIA_ARCHITECTURE_X86_64)
	_instruction((0x488100LL | 0300) << 32, 0xfffff8LL << 32, 7, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("add\t%s,%i\n", register_name64(_buffer[2] & 07), *reinterpret_cast<const int32_t*>(_buffer + 3));
	});
#endif
	_instruction(0x05LL << 32, 0xffLL << 32, 5, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("add\tesp,%i\n", *reinterpret_cast<const int32_t*>(_buffer + 1));
	});
	_instruction((0x8100LL | 0300) << 32, 0xfff8LL << 32, 6, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("add\t%s,%i\n", register_name32(_buffer[1] & 07), *reinterpret_cast<const int32_t*>(_buffer + 2));
	});
#if defined(BIA_ARCHITECTURE_X86_64)
	_instruction((0x488100LL | 0350) << 32, 0xfffff8LL << 32, 7, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("sub\t%s,%i\n", register_name64(_buffer[2] & 07), *reinterpret_cast<const int32_t*>(_buffer + 3));
	});
#endif
	_instruction(0x2dLL << 32, 0xffLL << 32, 5, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("sub\tesp,%i\n", *reinterpret_cast<const int32_t*>(_buffer + 1));
	});
	_instruction((0x8100LL | 0350) << 32, 0xfff8LL << 32, 6, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("sub\t%s,%i\n", register_name32(_buffer[1] & 07), *reinterpret_cast<const int32_t*>(_buffer + 2));
	});

	// Opcode + register + imm64
#if defined(BIA_ARCHITECTURE_X86_64)
//#error "fix me"
	_instruction(0x48b8LL << 64, 0xfff8LL << 64, 10, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("mov\t%s,%lli\n", register_name64(_buffer[1] & 07), *reinterpret_cast<const int64_t*>(_buffer + 2));
	});
#endif

	// Opcode + imm8
	_instruction(0x6a00, 0xff00, 2, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("push\t%hhi\n", _buffer[1]);
	});

	// Opcode + imm32
	_instruction(0x68LL << 32, 0xffLL << 32, 5, [](const disassembler * _disassembler, const int8_t * _buffer) {
		if (auto _name = _disassembler->name(*reinterpret_cast<void* const*>(_buffer + 1))) {
			printf("push\t%s at 0x%x\n", _name, *reinterpret_cast<const int32_t*>(_buffer + 1));
		} else {
			printf("push\t%i\n", *reinterpret_cast<const int32_t*>(_buffer + 1));
		}
	});
	_instruction(0xe9LL << 32, 0xffLL << 32, 5, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("jmp\t%i\n", _buffer + 5 + *reinterpret_cast<const int32_t*>(_buffer + 1));
	});
	_instruction(0x0f84LL << 32, 0xffffLL << 32, 6, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("je\t%p\n", _buffer + 6 + *reinterpret_cast<const int32_t*>(_buffer + 2));
	});
	_instruction(0x0f85LL << 32, 0xffffLL << 32, 6, [](const disassembler * _disassembler, const int8_t * _buffer) {
		printf("jne\t%p\n", _buffer + 6 + *reinterpret_cast<const int32_t*>(_buffer + 2));
	});
#endif
*/
	return _instructions;
	}

disassembler::function_map disassembler::init_function_map()
{
	function_map _function_map;

	BIA_FUNCTION_ENTRY(machine::link::instantiate_int32);
	BIA_FUNCTION_ENTRY(machine::link::instantiate_int64);
	BIA_FUNCTION_ENTRY(machine::link::instantiate_int_0);
	BIA_FUNCTION_ENTRY(machine::link::instantiate_int_1);
	BIA_FUNCTION_ENTRY(machine::link::instantiate_int_n1);
	BIA_FUNCTION_ENTRY(machine::link::instantiate_double);

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

	BIA_FUNCTION_ENTRY(framework::member::flags);

	BIA_FUNCTION_ENTRY(framework::member::operator_call);
	BIA_FUNCTION_ENTRY(framework::member::operator_call_int32);
	BIA_FUNCTION_ENTRY(framework::member::operator_call_int64);
	BIA_FUNCTION_ENTRY(framework::member::operator_call_double);
	BIA_FUNCTION_ENTRY(machine::link::operation_int32);
	BIA_FUNCTION_ENTRY(machine::link::operation_int64);
	BIA_FUNCTION_ENTRY(machine::link::operation_double);

	BIA_FUNCTION_ENTRY(framework::member::test);
	BIA_FUNCTION_ENTRY(framework::member::test_member);
	BIA_FUNCTION_ENTRY(framework::member::test_int32);
	BIA_FUNCTION_ENTRY(framework::member::test_int64);
	BIA_FUNCTION_ENTRY(framework::member::test_double);

	BIA_FUNCTION_ENTRY(framework::member::to_int);
	BIA_FUNCTION_ENTRY(framework::member::to_double);

	BIA_FUNCTION_ENTRY(framework::member::object_member);

	return _function_map;
}

		}
}
