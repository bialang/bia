#include "biaMachineDecoder.hpp"
#include "biaConfig.hpp"
#include "biaLink.hpp"
#include "biaMachineContext.hpp"

#include <cstdio>

#define BIA_FUNCTION_ENTRY(x) { union { decltype(&x) pFunction; const void * pAddress; } converter; converter.pFunction = &x; m_sFunctions[converter.pAddress] = std::string(#x "<") + typeid(&x).name() + ">"; }


namespace bia
{
namespace machine
{
namespace disassembler
{

std::vector<BiaMachineDecoder::Instruction> BiaMachineDecoder::m_svInstructions;
std::map<const void*, std::string> BiaMachineDecoder::m_sFunctions;

void BiaMachineDecoder::Initialize()
{
#if defined(BIA_ARCHITECTURE_MG32)
	BIA_FUNCTION_ENTRY(machine::link::Print_M);
	BIA_FUNCTION_ENTRY(machine::link::Print_i);
	BIA_FUNCTION_ENTRY(machine::link::Print_I);
	BIA_FUNCTION_ENTRY(machine::link::Print_f);
	BIA_FUNCTION_ENTRY(machine::link::Print_d);

	BIA_FUNCTION_ENTRY(machine::link::InstantiateInt_32);
	BIA_FUNCTION_ENTRY(machine::link::InstantiateInt_64);
	BIA_FUNCTION_ENTRY(machine::link::InstantiateInt0);
	BIA_FUNCTION_ENTRY(machine::link::InstantiateIntP1);
	BIA_FUNCTION_ENTRY(machine::link::InstantiateIntN1);
	BIA_FUNCTION_ENTRY(machine::link::InstantiateFloat);
	BIA_FUNCTION_ENTRY(machine::link::InstantiateDouble);
	BIA_FUNCTION_ENTRY(machine::link::InstantiateCopy);

	BIA_FUNCTION_ENTRY(machine::link::OperatorCall_MM);
	BIA_FUNCTION_ENTRY(machine::link::OperatorCall_Mi);

	BIA_FUNCTION_ENTRY(BiaMachineContext::ConstructTemporaryAddresses);
	BIA_FUNCTION_ENTRY(BiaMachineContext::DestructTemporaryAddresses);


	static auto RegisterName = [](uint8_t p_ucRegister) {
		switch (p_ucRegister)
		{
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

	//Only opcode
	AddInstruction(0xc9, 8, 1, [](BiaMachineDecoder*, const uint8_t*) {
		puts("leave");
	});
	AddInstruction(0xc3, 8, 1, [](BiaMachineDecoder*, const uint8_t*) {
		puts("ret");
	});

	//Opcode + register
	AddInstruction(0x50, 5, 1, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("push\t%s\n", RegisterName(*p_pBuffer & 07));
	});
	AddInstruction(0xff00 | 0320, 13, 2, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("call\t%s\n", RegisterName(p_pBuffer[1] & 07));
	});

	//Opcode + register + register
	AddInstruction(0x8900 | 0300, 10, 2, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("mov\t%s,%s\n", RegisterName(p_pBuffer[1] & 07), RegisterName(p_pBuffer[1] >> 3 & 07));
	});
	AddInstruction(0x8d0000 | 0100 << 8, 10, 3, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("lea\t%s,[%s%+hhi]\n", RegisterName(p_pBuffer[1] >> 3 & 07), RegisterName(p_pBuffer[1] & 07), p_pBuffer[2]);
	});
	AddInstruction(0x8d0000000000 | 0200ll << 32, 10, 6, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("lea\t%s,[%s%+i]\n", RegisterName(p_pBuffer[1] >> 3 & 07), RegisterName(p_pBuffer[1] & 07), *reinterpret_cast<const int32_t*>(p_pBuffer + 2));
	});

	//Opcode + register + 32 bit constant
	AddInstruction(0xff0000000000 | 0260ll << 32, 13, 6, [](BiaMachineDecoder * p_pDecoder, const uint8_t * p_pBuffer) {
		printf("push\t[%s%+i]\n", RegisterName(p_pBuffer[1] & 07), *reinterpret_cast<const int32_t*>(p_pBuffer + 2));
	});
	AddInstruction(0xb800000000, 5, 5, [](BiaMachineDecoder * p_pDecoder, const uint8_t * p_pBuffer) {
		auto szName = p_pDecoder->GetVariableName(*reinterpret_cast<void* const*>(p_pBuffer + 1));

		if (szName)
			printf("mov\t%s,%s at 0x%x\n", RegisterName(*p_pBuffer & 07), szName, *reinterpret_cast<const int32_t*>(p_pBuffer + 1));
		else
			printf("mov\t%s,%i\n", RegisterName(*p_pBuffer & 07), *reinterpret_cast<const int32_t*>(p_pBuffer + 1));
	});
	AddInstruction(0x0500000000, 8, 5, [](BiaMachineDecoder * p_pDecoder, const uint8_t * p_pBuffer) {
		printf("add\teax,%i\n", *reinterpret_cast<const int32_t*>(p_pBuffer + 1));
	});
	AddInstruction(0x8100000000 | 0300ll << 32, 13, 6, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("add\t%s,%i\n", RegisterName(p_pBuffer[1] & 07), *reinterpret_cast<const int32_t*>(p_pBuffer + 2));
	});
	AddInstruction(0x2d00000000, 8, 5, [](BiaMachineDecoder * p_pDecoder, const uint8_t * p_pBuffer) {
		printf("sub\teax,%i\n", *reinterpret_cast<const int32_t*>(p_pBuffer + 1));
	});
	AddInstruction(0x810000000000 | 0350ll << 32, 13, 6, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("sub\t%s,%i\n", RegisterName(p_pBuffer[1] & 07), *reinterpret_cast<const int32_t*>(p_pBuffer + 2));
	});

	//Opcode + register + 8 bit constant
	AddInstruction(0xff0000 | 0160 << 8, 13, 3, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("push\t[%s%+hhi]\n", RegisterName(p_pBuffer[1] & 07), p_pBuffer[2]);
	});
	AddInstruction(0x0400, 8, 2, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("add\teax,%hhi\n", p_pBuffer[1]);
	});
	AddInstruction(0x830000 | 0300 << 8, 13, 3, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("add\t%s,%hhi\n", RegisterName(p_pBuffer[1] & 07), p_pBuffer[2]);
	});
	AddInstruction(0x2c00, 8, 2, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("sub\teax,%hhi\n", p_pBuffer[1]);
	});
	AddInstruction(0x830000 | 0350 << 8, 13, 3, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("sub\t%s,%hhi\n", RegisterName(p_pBuffer[1] & 07), p_pBuffer[2]);
	});

	//Opcode + 32 bit constant
	AddInstruction(0x6800000000, 8, 5, [](BiaMachineDecoder * p_pDecoder, const uint8_t * p_pBuffer) {
		auto szName = p_pDecoder->GetVariableName(*reinterpret_cast<void* const*>(p_pBuffer + 1));

		if (szName)
			printf("push\t%s at 0x%x\n", szName, *reinterpret_cast<const int32_t*>(p_pBuffer + 1));
		else
			printf("push\t%i\n", *reinterpret_cast<const int32_t*>(p_pBuffer + 1));
	});

	//Opcode + 8 bit constant
	AddInstruction(0x6a00, 8, 2, [](BiaMachineDecoder * p_pDecoder, const uint8_t * p_pBuffer) {
		printf("push\t%hhi\n", static_cast<int8_t>(p_pBuffer[1]));
	});
#endif
}

}
}
}