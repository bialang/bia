#include "architecture_test.hpp"

#include <cstdint>
#include <initalizer_list>
#include <buffer_output_stream.hpp>
#include <cppunit/TestAssert.h>


using namespace CppUnit::Asserter;
using namespace bia::machine::platform;

CPPUNIT_TEST_SUITE_REGISTRATION(architecture_test);


template<OP_CODE _Op_code, REGISTER _Destination, REGISTER _Source>
inline bool compare(std::initalizer_list<int8_t> _expected)
{
	bia::stream::buffer_output_stream _output;

	instruction<_Op_code, _Destination, _Source>(_output);

	// Compare
}

void architecture_test::test_move()
{
#if defined(BIA_ARCHITECTURE_X86_32)
	CPPUNIT_ASSERT_MESSAGE("mov eax, imm32", compare32<OP_CODE::MOVE, eax>(0x6549752, { 0xB8, 0x52, 0x97, 0x54, 0x06 }));
	CPPUNIT_ASSERT_MESSAGE("mov esp, imm32", compare32<OP_CODE::MOVE, esp>(0x6549752, { 0xBC, 0x52, 0x97, 0x54, 0x06 }));
#endif
}

void architecture_test::test_xor()
{
#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)
	CPPUNIT_ASSERT_MESSAGE("xor eax, esp", compare<OP_CODE::XOR, eax, esp>({ 0x31, 0xE0 }));
	CPPUNIT_ASSERT_MESSAGE("xor esp, eax", compare<OP_CODE::XOR, esp, eax>({ 0x31, 0xC4 }));
	CPPUNIT_ASSERT_MESSAGE("xor eax, eax", compare<OP_CODE::XOR, eax, eax>({ 0x31, 0xC0 }));
	CPPUNIT_ASSERT_MESSAGE("xor esp, esp", compare<OP_CODE::XOR, esp, esp>({ 0x31, 0xE4 }));
#endif

#if defined(BIA_ARCHITECTURE_X86_64)
	CPPUNIT_ASSERT_MESSAGE("xor rax, rax", compare<OP_CODE::XOR, rax, rax>({ 0x48, 0x31, 0xC0 }));
	CPPUNIT_ASSERT_MESSAGE("xor r8, rax", compare<OP_CODE::XOR, r8, rax>({ 0x49, 0x31, 0xC0 }));
	CPPUNIT_ASSERT_MESSAGE("xor rax, r8", compare<OP_CODE::XOR, rax, r8>({ 0x4C, 0x31, 0xC0 }));
	CPPUNIT_ASSERT_MESSAGE("xor rsp, rsp", compare<OP_CODE::XOR, rsp, rsp>({ 0x48, 0x31, 0xE4 }));
	CPPUNIT_ASSERT_MESSAGE("xor r12, r12", compare<OP_CODE::XOR, r12, r12>({ 0x4D, 0x31, 0xE4 }));
#endif
}

void architecture_test::test_jump()
{
#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)
	CPPUNIT_ASSERT_MESSAGE("jmp 0x426464", compare32<OP_CODE::JUMP_RELATIVE>(0x426464, { 0xE9, 0x60, 0x64, 0x42, 0x00 }));
	CPPUNIT_ASSERT_MESSAGE("jmp -0x426464", compare32<OP_CODE::JUMP_RELATIVE>(-0x426464, { 0xE9, 0x98, 0x9B, 0xBD, 0xFF }));
	CPPUNIT_ASSERT_MESSAGE("je 0x426464", compare32<OP_CODE::JUMP_EQUAL>(0x426464, { 0x0F, 0x84, 0x60, 0x64, 0x42, 0x00 }));
	CPPUNIT_ASSERT_MESSAGE("je -0x426464", compare32<OP_CODE::JUMP_EQUAL>(-0x426464, { 0x0F, 0x84, 0x98, 0x9B, 0xBD, 0xFF }));
	CPPUNIT_ASSERT_MESSAGE("jne 0x426464", compare32<OP_CODE::JUMP_NOT_EQUAL>(0x426464, { 0x0F, 0x85, 0x60, 0x64, 0x42, 0x00 }));
	CPPUNIT_ASSERT_MESSAGE("jne -0x426464", compare32<OP_CODE::JUMP_NOT_EQUAL>(-0x426464, { 0x0F, 0x85, 0x98, 0x9B, 0xBD, 0xFF }));
#endif
}

void architecture_test::test_function_call()
{
#if defined(BIA_ARCHITECTURE_X86_32) || defined(BIA_ARCHITECTURE_X86_64)
	CPPUNIT_ASSERT_MESSAGE("ret", compare<OP_CODE::RETURN_NEAR>({ 0xC3 }));
#endif

#if defined(BIA_ARCHITECTURE_X86_32)
	CPPUNIT_ASSERT_MESSAGE("call eax", compare<OP_CODE::CALL, eax>({ 0xFF, 0xD0 }));
	CPPUNIT_ASSERT_MESSAGE("call esp", compare<OP_CODE::CALL, esp>({ 0xFF, 0xD4 }));
	CPPUNIT_ASSERT_MESSAGE("call [eax+0x66]", compare<OP_CODE::CALL, eax, int8_t>(0x66, { 0xFF, 0x50, 0x66 }));
	CPPUNIT_ASSERT_MESSAGE("call [esp-0x18]", compare<OP_CODE::CALL, esp, int8_t>(-0x18, { 0xFF, 0x54, 0x24, 0xE8 }));
	CPPUNIT_ASSERT_MESSAGE("call [eax-0x65381]", compare<OP_CODE::CALL, eax, int32_t>(-0x65381, { 0xFF, 0x90, 0x7F, 0xAC, 0xF9, 0xFF }));
	CPPUNIT_ASSERT_MESSAGE("call [esp+0x481235]", compare<OP_CODE::CALL, esp, int32_t>(0x481235, { 0xFF, 0x94, 0x24, 0x35, 0x12, 0x48, 0x00 }));
#elif defined(BIA_ARCHITECTURE_X86_64)
	CPPUNIT_ASSERT_MESSAGE("call rax", compare<OP_CODE::CALL, rax>({ 0xFF, 0xD0 }));
	CPPUNIT_ASSERT_MESSAGE("call rsp", compare<OP_CODE::CALL, rsp>({ 0xFF, 0xD4 }));
	CPPUNIT_ASSERT_MESSAGE("call r8", compare<OP_CODE::CALL, r8>({ 0x41, 0xFF, 0xD0 }));
	CPPUNIT_ASSERT_MESSAGE("call r12", compare<OP_CODE::CALL, r12>({ 0x41, 0xFF, 0xD4 }));
	CPPUNIT_ASSERT_MESSAGE("call [rax+0x65]", compare<OP_CODE::CALL, rax, int8_t>(0x65, { 0xFF, 0x50, 0x65 }));
	CPPUNIT_ASSERT_MESSAGE("call [rsp+0x65]", compare<OP_CODE::CALL, rsp, int8_t>(0x65, { 0xFF, 0x54, 0x24, 0x65 }));
	CPPUNIT_ASSERT_MESSAGE("call [r8+0x65]", compare<OP_CODE::CALL, r8, int8_t>(0x65, { 0x41, 0xFF, 0x50, 0x65 }));
	CPPUNIT_ASSERT_MESSAGE("call [r12+0x65]", compare<OP_CODE::CALL, r12, int8_t>(0x65, { 0x41, 0xFF, 0x54, 0x24, 0x65 }));
	CPPUNIT_ASSERT_MESSAGE("call [rax-0x653215]", compare<OP_CODE::CALL, rax, int32_t>(-0x653215, { 0xFF, 0x90, 0xEB, 0xCD, 0x9A, 0xFF }));
	CPPUNIT_ASSERT_MESSAGE("call [rsp-0x653215]", compare<OP_CODE::CALL, rsp, int32_t>(-0x653215, { 0xFF, 0x94, 0x24, 0xEB, 0xCD, 0x9A, 0xFF }));
	CPPUNIT_ASSERT_MESSAGE("call [r8-0x653215]", compare<OP_CODE::CALL, r8, int32_t>(-0x653215, { 0x41, 0xFF, 0x90, 0xEB, 0xCD, 0x9A, 0xFF }));
	CPPUNIT_ASSERT_MESSAGE("call [r12-0x653215]", compare<OP_CODE::CALL, r12, int32_t>(-0x653215, { 0x41, 0xFF, 0x94, 0x24, 0xEB, 0xCD, 0x9A, 0xFF }));
#endif
}
