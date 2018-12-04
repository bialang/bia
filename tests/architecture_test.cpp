#include "architecture_test.hpp"

#include <cstdint>
#include <initializer_list>
#include <type_traits>
#include <buffer_output_stream.hpp>


using namespace bia::machine::platform;

BEGIN_DECLARE_TESTS
	test::add("instruction_test", &architecture_test::instruction_test);
END_DECLARE_TESTS

template<typename Instruction_function, typename... Arguments>
inline bool compare_impl(std::initializer_list<uint8_t> _expected, Instruction_function _instruction, Arguments... _arguments)
{
		bia::stream::buffer_output_stream _tmp;

		_instruction(_tmp, _arguments...);

		// Compare
		if (_tmp.size() != _expected.size()) {
			return false;
		}

		for(int i= 0; i < _expected.size(); ++i){
			printf("%x", (uint8_t)_tmp.buffer()[i]);
		}
		puts("");

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
}/*

template<OP_CODE Op_code, typename Register, typename Offset_type>
inline bool compare(Offset_type _offset, std::initializer_list<uint8_t> _expected)
{
	return compare_impl(_expected, &instruction<Op_code, Register, Offset_type>, _offset);
}
*/
template<OP_CODE Op_code, typename Destination, typename Source>
inline bool compare(std::initializer_list<uint8_t> _expected)
{
	return compare_impl(_expected, static_cast<size_t(*)(bia::stream::output_stream&)>(&instruction<Op_code, Destination, Source>));
}
/*
template<OP_CODE Op_code, typename Destination, typename Source, typename Offset_type>
inline typename std::enable_if<!std::is_integral<Source>::value, bool>::type compare(Offset_type _offset, std::initializer_list<uint8_t> _expected)
{
	return compare_impl(_expected, &instruction<Op_code, Destination, Source, Offset_type>, _offset);
}*/


void architecture_test::instruction_test()
{
	test_move();
	test_xor();
	test_jump();
	test_push();
	test_pop();
	test_function_call();
}

void architecture_test::test_move()
{
#if defined(BIA_ARCHITECTURE_X86_32)
	/*test::assert_true(compare32<OP_CODE::MOVE, eax>(0x6549752, { 0xB8, 0x52, 0x97, 0x54, 0x06 }), "mov eax, imm32");
	test::assert_true(compare32<OP_CODE::MOVE, esp>(0x6549752, { 0xBC, 0x52, 0x97, 0x54, 0x06 }), "mov esp, imm32");*/
#endif
}

void architecture_test::test_xor()
{
/*#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)
	test::assert_true(compare<OP_CODE::XOR, eax, esp>({ 0x31, 0xE0 }), "xor eax, esp");
	test::assert_true(compare<OP_CODE::XOR, esp, eax>({ 0x31, 0xC4 }), "xor esp, eax");
	test::assert_true(compare<OP_CODE::XOR, eax, eax>({ 0x31, 0xC0 }), "xor eax, eax");
	test::assert_true(compare<OP_CODE::XOR, esp, esp>({ 0x31, 0xE4 }), "xor esp, esp");
#endif

#if defined(BIA_ARCHITECTURE_X86_64)
	test::assert_true(compare<OP_CODE::XOR, rax, rax>({ 0x48, 0x31, 0xC0 }), "xor rax, rax");
	test::assert_true(compare<OP_CODE::XOR, r8, rax>({ 0x49, 0x31, 0xC0 }), "xor r8, rax");
	test::assert_true(compare<OP_CODE::XOR, rax, r8>({ 0x4C, 0x31, 0xC0 }), "xor rax, r8");
	test::assert_true(compare<OP_CODE::XOR, rsp, rsp>({ 0x48, 0x31, 0xE4 }), "xor rsp, rsp");
	//test::assert_true(compare<OP_CODE::XOR, r12, r12>({ 0x4D, 0x31, 0xE4 }), "xor r12, r12");
#endif*/
}

void architecture_test::test_jump()
{
#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)
	/*test::assert_true(compare32<OP_CODE::JUMP_RELATIVE>(0x426464, { 0xE9, 0x60, 0x64, 0x42, 0x00 }), "jmp 0x426464");
	test::assert_true(compare32<OP_CODE::JUMP_RELATIVE>(-0x426464, { 0xE9, 0x98, 0x9B, 0xBD, 0xFF }), "jmp -0x426464");
	test::assert_true(compare32<OP_CODE::JUMP_EQUAL>(0x426464, { 0x0F, 0x84, 0x60, 0x64, 0x42, 0x00 }), "je 0x426464");
	test::assert_true(compare32<OP_CODE::JUMP_EQUAL>(-0x426464, { 0x0F, 0x84, 0x98, 0x9B, 0xBD, 0xFF }), "je -0x426464");
	test::assert_true(compare32<OP_CODE::JUMP_NOT_EQUAL>(0x426464, { 0x0F, 0x85, 0x60, 0x64, 0x42, 0x00 }), "jne 0x426464");
	test::assert_true(compare32<OP_CODE::JUMP_NOT_EQUAL>(-0x426464, { 0x0F, 0x85, 0x98, 0x9B, 0xBD, 0xFF }), "jne -0x426464");*/
#endif
}

void architecture_test::test_push()
{
#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)
	/*test::assert_true(compare8<OP_CODE::PUSH>(0x5, { 0x6A, 0x05 }), "push 0x5");
	test::assert_true(compare8<OP_CODE::PUSH>(-0x5, { 0x6A, 0xFB }), "push -0x5");
	test::assert_true(compare32<OP_CODE::PUSH>(0x56985, { 0x68, 0x85, 0x69, 0x05, 0x00 }), "push 0x56985");
	test::assert_true(compare32<OP_CODE::PUSH>(-0x56985, { 0x68, 0x7B, 0x96, 0xFA, 0xFF }), "push -0x56985");*/
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
	/*//test::assert_true(compare<OP_CODE::PUSH, r12>({ 0x41, 0x54 }), "push r12");
	test::assert_true(compare<OP_CODE::PUSH, rax, int8_t>(0x35, { 0xFF, 0x70, 0x35 }), "push [rax+0x35]");
	test::assert_true(compare<OP_CODE::PUSH, rsp, int8_t>(-0x35, { 0xFF, 0x74, 0x24, 0xCB }), "push [rsp-0x35]");
	test::assert_true(compare<OP_CODE::PUSH, r8, int8_t>(-0x35, { 0x41, 0xFF, 0x70, 0xCB }), "push [r8-0x35]");
	//test::assert_true(compare<OP_CODE::PUSH, r12, int8_t>(0x35, { 0x41, 0xFF, 0x74, 0x24, 0x35 }), "push [r12+0x35]");
	test::assert_true(compare<OP_CODE::PUSH, rax, int32_t>(-0x398655, { 0xFF, 0xB0, 0xAB, 0x79, 0xC6, 0xFF }), "push [rax-0x398655]");
	test::assert_true(compare<OP_CODE::PUSH, rsp, int32_t>(0x398655, { 0xFF, 0xB4, 0x24, 0x55, 0x86, 0x39, 0x00 }), "push [rsp+0x398655]");
	test::assert_true(compare<OP_CODE::PUSH, r8, int32_t>(0x398655, { 0x41, 0xFF, 0xB0, 0x55, 0x86, 0x39, 0x00 }), "push [r8+0x398655]");
	//test::assert_true(compare<OP_CODE::PUSH, r12, int32_t>(-0x398655, { 0x41, 0xFF, 0xB4, 0x24, 0xAB, 0x79, 0xC6, 0xFF }), "push [r12-0x398655]");*/
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
	//test::assert_true(compare<OP_CODE::POP, r12>({ 0x41, 0x5C }), "pop r12");
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
