#include "biaMachineDecoder.hpp"
#include "biaConfig.hpp"

#include <cstdio>


namespace bia
{
namespace machine
{
namespace disassembler
{

std::vector<BiaMachineDecoder::Instruction> BiaMachineDecoder::m_svInstructions;

void BiaMachineDecoder::Initialize()
{
#if defined(BIA_ARCHITECTURE_MG32)
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
		printf("push\t%s\n", RegisterName(p_pBuffer[1] & 07));
	});

	//Opcode + register + register
	AddInstruction(0x8900 | 0300, 10, 2, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("mov\t%s,%s\n", RegisterName(p_pBuffer[1] & 07), RegisterName(p_pBuffer[1] >> 3 & 07));
	});

	//Opcode + 32 bit constant
	AddInstruction(0x6800000000, 8, 5, [](BiaMachineDecoder * p_pDecoder, const uint8_t * p_pBuffer) {
		auto szName = p_pDecoder->GetVariableName(reinterpret_cast<const framework::BiaMember*>(*reinterpret_cast<const intptr_t*>(p_pBuffer + 1)));

		if (szName)
			printf("push\t%s\n", szName);
		else
			printf("push\t0x%x\n", *reinterpret_cast<const int32_t*>(p_pBuffer + 1));
	});

	//Opcode + 8 bit constant
	AddInstruction(0x6a00, 8, 2, [](BiaMachineDecoder * p_pDecoder, const uint8_t * p_pBuffer) {
		printf("push\t0x%hhx\n", static_cast<int8_t>(p_pBuffer[1]));
	});

	//Opcode + register + 32 bit constant
	AddInstruction(0xff0000000000 | 0260ll << 32, 13, 6, [](BiaMachineDecoder * p_pDecoder, const uint8_t * p_pBuffer) {
		auto szName = p_pDecoder->GetVariableName(reinterpret_cast<const framework::BiaMember*>(*reinterpret_cast<const intptr_t*>(p_pBuffer + 2)));

		if (szName)
			printf("push\t%s,%s\n", RegisterName(p_pBuffer[1] & 07), szName);
		else
			printf("push\t%s,0x%x\n", RegisterName(p_pBuffer[1] & 07), *reinterpret_cast<const int32_t*>(p_pBuffer + 2));
	});
	AddInstruction(0xb800000000, 5, 5, [](BiaMachineDecoder * p_pDecoder, const uint8_t * p_pBuffer) {
		auto szName = p_pDecoder->GetVariableName(reinterpret_cast<const framework::BiaMember*>(*reinterpret_cast<const intptr_t*>(p_pBuffer + 2)));

		if (szName)
			printf("mov\t%s,%s\n", RegisterName(*p_pBuffer & 07), szName);
		else
			printf("mov\t%s,0x%x\n", RegisterName(*p_pBuffer & 07), *reinterpret_cast<const int32_t*>(p_pBuffer + 1));
	});
	AddInstruction(0x0500000000, 8, 5, [](BiaMachineDecoder * p_pDecoder, const uint8_t * p_pBuffer) {
		printf("add\teax,0x%x\n", *reinterpret_cast<const int32_t*>(p_pBuffer + 1));
	});
	AddInstruction(0x8100000000 | 0300ll << 32, 13, 6, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("add\t%s,0x%x\n", RegisterName(p_pBuffer[1] & 07), *reinterpret_cast<const int32_t*>(p_pBuffer + 2));
	});
	AddInstruction(0x2d00000000, 8, 5, [](BiaMachineDecoder * p_pDecoder, const uint8_t * p_pBuffer) {
		printf("sub\teax,0x%x\n", *reinterpret_cast<const int32_t*>(p_pBuffer + 1));
	});
	AddInstruction(0x810000000000 | 0350ll << 32, 13, 6, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("sub\t%s,0x%x\n", RegisterName(p_pBuffer[1] & 07), *reinterpret_cast<const int32_t*>(p_pBuffer + 2));
	});

	//Opcode + register + 8 bit constant
	AddInstruction(0xff0000 | 0160 << 8, 13, 3, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("push\t[%s0x%+hhx]\n", RegisterName(p_pBuffer[1] & 07), p_pBuffer[2]);
	});
	AddInstruction(0x0400, 8, 2, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("add\teax,0x%hhx\n", p_pBuffer[1]);
	});
	AddInstruction(0x830000 | 0300 << 8, 13, 3, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("add\t%s,0x%hhx\n", RegisterName(p_pBuffer[1] & 07), p_pBuffer[2]);
	});
	AddInstruction(0x2c00, 8, 2, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("sub\teax,0x%hhx\n", p_pBuffer[1]);
	});
	AddInstruction(0x830000 | 0350 << 8, 13, 3, [](BiaMachineDecoder*, const uint8_t * p_pBuffer) {
		printf("sub\t%s,0x%hhx\n", RegisterName(p_pBuffer[1] & 07), p_pBuffer[2]);
	});
#endif
}

}
}
}