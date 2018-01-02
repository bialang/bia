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
	BiaMachineDecoder(variable_index & p_index) : m_index(p_index)
	{

	}
	void AddInstruction(std::function<uint8_t(const void*)> p_callback, uint64_t p_ullMask, uint8_t p_ucSize)
	{
		m_vInstructions.push_back({ p_ullMask, p_callback, p_ucSize });
	}
	void Disassemble(const void * p_pMachineCode, size_t p_iSize)
	{
		auto pBuffer = static_cast<const uint8_t*>(p_pMachineCode);

		while (p_iSize)
		{
			//Check all instruction
			for (auto & instruction : m_vInstructions)
			{
				if (instruction.ucSize <= p_iSize)
				{
					uint64_t ullCode = 0;

					memcpy(&ullCode, pBuffer, std::min<size_t>(instruction.ucSize, 8));

					//This it the instruction
					if ((ullCode & instruction.ullMask) == instruction.ullMask)
					{
						auto ucOffset = instruction.callback(pBuffer);

						pBuffer += ucOffset;
						p_iSize -= ucOffset;

						goto gt_continue;
					}
				}
			}

			throw exception::Exception("hi");

			break;

		gt_continue:;
		}
	}
	const char * GetVariableName(variable_index::mapped_type p_value)
	{
		for (auto & element : m_index)
		{
			if (element.second == p_value)
				return element.first.data();
		}

		return nullptr;
	}
private:
	struct Instruction
	{
		uint64_t ullMask;
		std::function<uint8_t(const void*)> callback;
		uint8_t ucSize;
	};

	variable_index & m_index;
	std::vector<Instruction> m_vInstructions;
};

}
}
}