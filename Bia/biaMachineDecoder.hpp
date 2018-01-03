#pragma once

#include <cstdint>
#include <functional>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

#include "biaInputStream.hpp"
#include "biaException.hpp"
#include "biaVariableHandler.hpp"


namespace bia
{
namespace machine
{
namespace disassembler
{

class BiaMachineDecoder
{
public:
	BiaMachineDecoder(const void * p_pMachineContextAddress, variable_index & p_index) : m_index(p_index)
	{
		m_pMachineContextAddress = p_pMachineContextAddress;

		if (m_svInstructions.empty())
			Initialize();
	}
	void Disassemble(const void * p_pMachineCode, size_t p_iSize)
	{
		auto pBuffer = static_cast<const uint8_t*>(p_pMachineCode);

		while (p_iSize)
		{
			//Check all instruction
			for (auto & instruction : m_svInstructions)
			{
				if (instruction.ucSize <= p_iSize)
				{
					uint64_t ullCode = 0;

					memcpy(&ullCode, pBuffer, std::min<uint8_t>(8, instruction.ucSize));

					//This it the instruction
					if ((ullCode & instruction.ullMask) == instruction.ullInstruction)
					{
						instruction.callback(this, pBuffer);

						pBuffer += instruction.ucSize;
						p_iSize -= instruction.ucSize;

						goto gt_continue;
					}
				}
			}

			throw exception::Exception("hi");

			break;

		gt_continue:;
		}
	}
	const char * GetVariableName(const void * p_pAddress)
	{
		if (p_pAddress == m_pMachineContextAddress)
			return "this";

		auto pResult = m_sFunctions.find(p_pAddress);

		if (pResult != m_sFunctions.end())
			return pResult->second.c_str();

		for (auto & element : m_index)
		{
			if (element.second == p_pAddress)
				return element.first.data();
		}

		return nullptr;
	}
private:
	struct Instruction
	{
		uint64_t ullInstruction;
		uint64_t ullMask;
		std::function<void(BiaMachineDecoder*, const uint8_t*)> callback;
		uint8_t ucSize;
	};

	const void * m_pMachineContextAddress;
	variable_index & m_index;

	static std::vector<Instruction> m_svInstructions;
	static std::map<const void*, std::string> m_sFunctions;


	static void Initialize();
	static void AddInstruction(uint64_t p_ullInstruction, uint8_t p_ucFirstBitCount, uint8_t p_ucInstructionSize, std::function<void(BiaMachineDecoder*, const uint8_t*)> p_callback)
	{
		m_svInstructions.push_back({ _byteswap_uint64(p_ullInstruction) >> (8 - p_ucInstructionSize) * 8, ~(~0ull << (p_ucFirstBitCount & 0xf8)) | (0xff00ull >> (p_ucFirstBitCount & 0x7) & 0xff) << (p_ucFirstBitCount & 0xf8), p_callback, p_ucInstructionSize });
	}
};

}
}
}