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