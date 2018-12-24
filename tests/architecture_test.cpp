#include "architecture_test.hpp"

#include <cstdint>
#include <initializer_list>
#include <type_traits>
#include <buffer_output_stream.hpp>


using namespace bia::machine::platform;

BEGIN_DECLARE_TESTS
test::add("instruction", &architecture_test::instruction_test);
END_DECLARE_TESTS

template<typename Instruction_function, typename... Arguments>
inline bool compare_impl(std::initializer_list<uint8_t> _expected, Instruction_function _instruction, Arguments... _arguments)
{
	bia::stream::buffer_output_stream _tmp;

	_instruction(_tmp, _arguments...);

	for (int i = 0; i < _tmp.size(); ++i) {
		printf("%x", (uint8_t)_tmp.buffer()[i]);
	}
	puts("");

	// Compare
	if (_tmp.size() != _expected.size()) {
		return false;
	}

	return !std::memcmp(_tmp.buffer(), _expected.begin(), _expected.size());
}

template<OP_CODE Op_code>
inline bool compare(std::initializer_list<uint8_t> _expected)
{
	return compare_impl(_expected, &instruction<Op_code>);
}

template<OP_CODE Op_code, typename Register>
inline bool compare(std::initializer_list<uint8_t> _expected)
{
	return compare_impl(_expected, &instruction<Op_code, Register>);
}

template<OP_CODE Op_code, typename Register, typename Offset_type>
inline bool compare(Offset_type _offset, std::initializer_list<uint8_t> _expected)
{
	return compare_impl(_expected, [_offset](bia::stream::output_stream & _output) {
		instruction<Op_code, Register>(_output, _offset);
	});
}

template<OP_CODE Op_code, typename Destination, typename Source>
inline bool compare(std::initializer_list<uint8_t> _expected)
{
	return compare_impl(_expected, static_cast<size_t(*)(bia::stream::output_stream&)>(&instruction<Op_code, Destination, Source>));
}

/*template<OP_CODE Op_code, typename Destination, typename Source, typename Offset_type>
inline bool compare(Offset_type _offset, std::initializer_list<uint8_t> _expected)
{
	return compare_impl(_expected, static_cast<size_t(*)(bia::stream::output_stream&, Offset_type)>(&instruction<Op_code, Destination, Source, Offset_type>), _offset);
}*/

template<OP_CODE Op_code>
inline bool compare8(int8_t _immediate, std::initializer_list<uint8_t> _expected)
{
	return compare_impl(_expected, &instruction8<Op_code>, _immediate);
}

template<OP_CODE Op_code, typename Register>
inline bool compare8(int8_t _immediate, std::initializer_list<uint8_t> _expected)
{
	return compare_impl(_expected, &instruction8<Op_code, Register>, _immediate);
}

template<OP_CODE Op_code>
inline bool compare32(int32_t _immediate, std::initializer_list<uint8_t> _expected)
{
	return compare_impl(_expected, &instruction32<Op_code>, _immediate);
}

template<OP_CODE Op_code, typename Register>
inline bool compare32(int32_t _immediate, std::initializer_list<uint8_t> _expected)
{
	return compare_impl(_expected, &instruction32<Op_code, Register>, _immediate);
}


void architecture_test::instruction_test()
{
	test_move();
	test_add();
	test_sub();
	//test_jump();
	test_push();
	test_pop();
	test_function_call();
	test_other();
}

void architecture_test::test_move()
{
#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)
	test::assert_true(compare32<OP_CODE::MOVE, eax>(0x6549752, { 0xb8, 0x52, 0x97, 0x54, 0x06 }), "mov eax, imm32");
	test::assert_true(compare32<OP_CODE::MOVE, esp>(0x6549752, { 0xbc, 0x52, 0x97, 0x54, 0x06 }), "mov esp, imm32");
	test::assert_true(compare<OP_CODE::MOVE, eax, eax>({ 0x89, 0xc0 }), "mov eax, eax");
	test::assert_true(compare<OP_CODE::MOVE, eax, esp>({ 0x89, 0xe0 }), "mov eax, esp");
	test::assert_true(compare<OP_CODE::MOVE, esp, eax>({ 0x89, 0xc4 }), "mov esp, eax");
	test::assert_true(compare<OP_CODE::MOVE, esp, esp>({ 0x89, 0xe4 }), "mov esp, esp");
#endif

#if defined(BIA_ARCHITECTURE_X86_64)

#endif
}

void architecture_test::test_add()
{
#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)
	test::assert_true(compare8<OP_CODE::ADD, eax>(0x64, { 0x83, 0xc0, 0x64 }), "add eax, 0x64");
	test::assert_true(compare8<OP_CODE::ADD, esp>(0x64, { 0x83, 0xc4, 0x64 }), "add esp, 0x64");
	test::assert_true(compare32<OP_CODE::ADD, eax>(0x64095344, { 0x05, 0x44, 0x53, 0x09, 0x64 }), "add eax, 0x64095344");
	test::assert_true(compare32<OP_CODE::ADD, esp>(0x64095344, { 0x81, 0xc4, 0x44, 0x53, 0x09, 0x64 }), "add esp, 0x64095344");
#endif

#if defined(BIA_ARCHITECTURE_X86_64)
	test::assert_true(compare8<OP_CODE::ADD, rax>(0x64, { 0x48, 0x83, 0xc0, 0x64 }), "add eax, 0x64");
	test::assert_true(compare8<OP_CODE::ADD, rsp>(0x64, { 0x48, 0x83, 0xc4, 0x64 }), "add rsp, 0x64");
	test::assert_true(compare8<OP_CODE::ADD, r8>(0x64, { 0x49, 0x83, 0xc0, 0x64 }), "add r8, 0x64");
	test::assert_true(compare32<OP_CODE::ADD, rax>(0x64095344, { 0x48, 0x05, 0x44, 0x53, 0x09, 0x64 }), "add eax, 0x64095344");
	test::assert_true(compare32<OP_CODE::ADD, rsp>(0x64095344, { 0x48, 0x81, 0xc4, 0x44, 0x53, 0x09, 0x64 }), "add rsp, 0x64095344");
	test::assert_true(compare32<OP_CODE::ADD, r8>(0x64095344, { 0x49, 0x81, 0xc0, 0x44, 0x53, 0x09, 0x64 }), "add r8, 0x64095344");
#endif
}

void architecture_test::test_sub()
{
#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)
	test::assert_true(compare8<OP_CODE::SUB, eax>(0x64, { 0x83, 0xe8, 0x64 }), "sub eax, 0x64");
	test::assert_true(compare8<OP_CODE::SUB, esp>(0x64, { 0x83, 0xec, 0x64 }), "sub esp, 0x64");
	test::assert_true(compare32<OP_CODE::SUB, eax>(0x64095344, { 0x2d, 0x44, 0x53, 0x09, 0x64 }), "sub eax, 0x64095344");
	test::assert_true(compare32<OP_CODE::SUB, esp>(0x64095344, { 0x81, 0xec, 0x44, 0x53, 0x09, 0x64 }), "sub esp, 0x64095344");
#endif

#if defined(BIA_ARCHITECTURE_X86_64)
	test::assert_true(compare8<OP_CODE::SUB, rax>(0x64, { 0x48, 0x83, 0xe8, 0x64 }), "sub eax, 0x64");
	test::assert_true(compare8<OP_CODE::SUB, rsp>(0x64, { 0x48, 0x83, 0xec, 0x64 }), "sub rsp, 0x64");
	test::assert_true(compare8<OP_CODE::SUB, r8>(0x64, { 0x49, 0x83, 0xe8, 0x64 }), "sub r8, 0x64");
	test::assert_true(compare32<OP_CODE::SUB, rax>(0x64095344, { 0x48, 0x2d, 0x44, 0x53, 0x09, 0x64 }), "sub eax, 0x64095344");
	test::assert_true(compare32<OP_CODE::SUB, rsp>(0x64095344, { 0x48, 0x81, 0xec, 0x44, 0x53, 0x09, 0x64 }), "sub rsp, 0x64095344");
	test::assert_true(compare32<OP_CODE::SUB, r8>(0x64095344, { 0x49, 0x81, 0xe8, 0x44, 0x53, 0x09, 0x64 }), "sub r8, 0x64095344");
#endif
}

void architecture_test::test_jump()
{
#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)
	test::assert_true(compare32<OP_CODE::JUMP_RELATIVE>(0x426464, { 0xE9, 0x60, 0x64, 0x42, 0x00 }), "jmp 0x426464");
	test::assert_true(compare32<OP_CODE::JUMP_RELATIVE>(-0x426464, { 0xE9, 0x98, 0x9B, 0xBD, 0xFF }), "jmp -0x426464");
	test::assert_true(compare32<OP_CODE::JUMP_EQUAL>(0x426464, { 0x0F, 0x84, 0x60, 0x64, 0x42, 0x00 }), "je 0x426464");
	test::assert_true(compare32<OP_CODE::JUMP_EQUAL>(-0x426464, { 0x0F, 0x84, 0x98, 0x9B, 0xBD, 0xFF }), "je -0x426464");
	test::assert_true(compare32<OP_CODE::JUMP_NOT_EQUAL>(0x426464, { 0x0F, 0x85, 0x60, 0x64, 0x42, 0x00 }), "jne 0x426464");
	test::assert_true(compare32<OP_CODE::JUMP_NOT_EQUAL>(-0x426464, { 0x0F, 0x85, 0x98, 0x9B, 0xBD, 0xFF }), "jne -0x426464");
#endif
}

void architecture_test::test_push()
{
#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)
	test::assert_true(compare8<OP_CODE::PUSH>(0x05, { 0x6a, 0x05 }), "push 0x05");
	test::assert_true(compare32<OP_CODE::PUSH>(0x00056985, { 0x68, 0x85, 0x69, 0x05, 0x00 }), "push 0x00056985");
#endif

#if defined(BIA_ARCHITECTURE_X86_32)
	test::assert_true(compare<OP_CODE::PUSH, eax>({ 0x50 }), "push eax");
	test::assert_true(compare<OP_CODE::PUSH, esp>({ 0x54 }), "push esp");
	/*test::assert_true(compare<OP_CODE::PUSH, eax, int8_t>(0x35, { 0xFF, 0x70, 0x35 }), "push [eax+0x35]");
	test::assert_true(compare<OP_CODE::PUSH, esp, int8_t>(-0x35, { 0xFF, 0x74, 0x24, 0xCB }), "push [esp-0x35]");
	test::assert_true(compare<OP_CODE::PUSH, eax, int32_t>(-0x398655, { 0xFF, 0xB0, 0xAB, 0x79, 0xC6, 0xFF }), "push [eax-0x398655]");
	test::assert_true(compare<OP_CODE::PUSH, esp, int32_t>(0x398655, { 0xFF, 0xB4, 0x24, 0x55, 0x86, 0x39, 0x00 }), "push [esp+0x398655]");*/
#endif

#if defined(BIA_ARCHITECTURE_X86_64)
	test::assert_true(compare<OP_CODE::PUSH, rax>({ 0x50 }), "push rax");
	test::assert_true(compare<OP_CODE::PUSH, rsp>({ 0x54 }), "push rsp");
	test::assert_true(compare<OP_CODE::PUSH, r8>({ 0x41, 0x50 }), "push r8");
	test::assert_true(compare<OP_CODE::PUSH, rax, int8_t>(0x35, { 0xff, 0x70, 0x35 }), "push [rax+0x35]");
	test::assert_true(compare<OP_CODE::PUSH, rsp, int8_t>(-0x35, { 0xff, 0x74, 0x24, 0xcb }), "push [rsp-0x35]");
	test::assert_true(compare<OP_CODE::PUSH, r8, int8_t>(-0x35, { 0x41, 0xff, 0x70, 0xcb }), "push [r8-0x35]");
	test::assert_true(compare<OP_CODE::PUSH, rax, int32_t>(-0x398655, { 0xff, 0xb0, 0xab, 0x79, 0xc6, 0xff }), "push [rax-0x398655]");
	test::assert_true(compare<OP_CODE::PUSH, rsp, int32_t>(0x398655, { 0xff, 0xb4, 0x24, 0x55, 0x86, 0x39, 0x00 }), "push [rsp+0x398655]");
	test::assert_true(compare<OP_CODE::PUSH, r8, int32_t>(0x398655, { 0x41, 0xff, 0xb0, 0x55, 0x86, 0x39, 0x00 }), "push [r8+0x398655]");
#endif
}

void architecture_test::test_pop()
{
#if defined(BIA_ARCHITECTURE_X86_32)
	test::assert_true(compare<OP_CODE::POP, eax>({ 0x58 }), "pop eax");
	test::assert_true(compare<OP_CODE::POP, esp>({ 0x5C }), "pop esp");
#endif

#if defined(BIA_ARCHITECTURE_X86_64)
	test::assert_true(compare<OP_CODE::POP, rax>({ 0x58 }), "pop rax");
	test::assert_true(compare<OP_CODE::POP, rsp>({ 0x5C }), "pop rsp");
	test::assert_true(compare<OP_CODE::POP, r8>({ 0x41, 0x58 }), "pop r8");
#endif
}

void architecture_test::test_function_call()
{
#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)
	test::assert_true(compare<OP_CODE::RETURN_NEAR>({ 0xC3 }), "ret");
#endif

#if defined(BIA_ARCHITECTURE_X86_32)
	test::assert_true(compare<OP_CODE::CALL, eax>({ 0xFF, 0xD0 }), "call eax");
	test::assert_true(compare<OP_CODE::CALL, esp>({ 0xFF, 0xD4 }), "call esp");
	/*test::assert_true(compare<OP_CODE::CALL, eax, int8_t>(0x66, { 0xFF, 0x50, 0x66 }), "call [eax+0x66]");
	test::assert_true(compare<OP_CODE::CALL, esp, int8_t>(-0x18, { 0xFF, 0x54, 0x24, 0xE8 }), "call [esp-0x18]");
	test::assert_true(compare<OP_CODE::CALL, eax, int32_t>(-0x65381, { 0xFF, 0x90, 0x7F, 0xAC, 0xF9, 0xFF }), "call [eax-0x65381]");
	test::assert_true(compare<OP_CODE::CALL, esp, int32_t>(0x481235, { 0xFF, 0x94, 0x24, 0x35, 0x12, 0x48, 0x00 }), "call [esp+0x481235]");*/
#elif defined(BIA_ARCHITECTURE_X86_64)
	test::assert_true(compare<OP_CODE::CALL, rax>({ 0xFF, 0xD0 }), "call rax");
	test::assert_true(compare<OP_CODE::CALL, rsp>({ 0xFF, 0xD4 }), "call rsp");
	test::assert_true(compare<OP_CODE::CALL, r8>({ 0x41, 0xFF, 0xD0 }), "call r8");
	//test::assert_true(compare<OP_CODE::CALL, r12>({ 0x41, 0xFF, 0xD4 }), "call r12");
	/*test::assert_true(compare<OP_CODE::CALL, rax, int8_t>(0x65, { 0xFF, 0x50, 0x65 }), "call [rax+0x65]");
	test::assert_true(compare<OP_CODE::CALL, rsp, int8_t>(0x65, { 0xFF, 0x54, 0x24, 0x65 }), "call [rsp+0x65]");
	test::assert_true(compare<OP_CODE::CALL, r8, int8_t>(0x65, { 0x41, 0xFF, 0x50, 0x65 }), "call [r8+0x65]");
	//test::assert_true(compare<OP_CODE::CALL, r12, int8_t>(0x65, { 0x41, 0xFF, 0x54, 0x24, 0x65 }), "call [r12+0x65]");
	test::assert_true(compare<OP_CODE::CALL, rax, int32_t>(-0x653215, { 0xFF, 0x90, 0xEB, 0xCD, 0x9A, 0xFF }), "call [rax-0x653215]");
	test::assert_true(compare<OP_CODE::CALL, rsp, int32_t>(-0x653215, { 0xFF, 0x94, 0x24, 0xEB, 0xCD, 0x9A, 0xFF }), "call [rsp-0x653215]");
	test::assert_true(compare<OP_CODE::CALL, r8, int32_t>(-0x653215, { 0x41, 0xFF, 0x90, 0xEB, 0xCD, 0x9A, 0xFF }), "call [r8-0x653215]");
	//test::assert_true(compare<OP_CODE::CALL, r12, int32_t>(-0x653215, { 0x41, 0xFF, 0x94, 0x24, 0xEB, 0xCD, 0x9A, 0xFF }), "call [r12-0x653215]");*/
#endif
}

void architecture_test::test_other()
{
#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)
	test::assert_true(compare<OP_CODE::TEST, eax, eax>({ 0x85, 0xc0 }), "test eax, eax");
	test::assert_true(compare<OP_CODE::TEST, eax, esp>({ 0x85, 0xe0 }), "test eax, esp");
	test::assert_true(compare<OP_CODE::TEST, esp, eax>({ 0x85, 0xc4 }), "test esp, eax");
	test::assert_true(compare<OP_CODE::TEST, esp, esp>({ 0x85, 0xe4 }), "test esp, esp");
#endif

#if defined(BIA_ARCHITECTURE_X86_64)
	test::assert_true(compare<OP_CODE::TEST, rax, rax>({ 0x48, 0x85, 0xc0 }), "test rax, rax");
	test::assert_true(compare<OP_CODE::TEST, rax, rsp>({ 0x48, 0x85, 0xe0 }), "test rax, rsp");
	test::assert_true(compare<OP_CODE::TEST, rax, r8>({ 0x4c, 0x85, 0xc0 }), "test rax, r8");
	test::assert_true(compare<OP_CODE::TEST, rsp, rsp>({ 0x48, 0x85, 0xe4 }), "test rsp, rsp");
	test::assert_true(compare<OP_CODE::TEST, rsp, rax>({ 0x48, 0x85, 0xc4 }), "test rsp, rax");
	test::assert_true(compare<OP_CODE::TEST, rsp, r8>({ 0x4c, 0x85, 0xc4 }), "test rsp, r8");
	test::assert_true(compare<OP_CODE::TEST, r8, r8>({ 0x4d, 0x85, 0xc0 }), "test r8, r8");
	test::assert_true(compare<OP_CODE::TEST, r8, rax>({ 0x49, 0x85, 0xc0 }), "test r8, rax");
	test::assert_true(compare<OP_CODE::TEST, r8, rsp>({ 0x49, 0x85, 0xe0 }), "test r8, rsp");
#endif
}
