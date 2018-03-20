#pragma once

#include <cstdint>
#include <functional>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

#include "biaConfig.hpp"
#include "biaInputStream.hpp"
#include "biaException.hpp"
#include "biaVariableHandler.hpp"
#include "biaMachineContext.hpp"


namespace bia
{
namespace machine
{
namespace disassembler
{

class BiaMachineDecoder
{
public:
	/**
	 * Constructor.
	 *
	 * @param	p_pMachineContextAddress	Defines the address of the machine context.
	 * @param	[in]	p_index	Defines the index for all known global variables.
	*/
	BiaMachineDecoder(const BiaMachineContext * p_pMachineContextAddress, variable_index & p_index);
	/**
	 * Disassembles the machine code and prints the assembly code.
	 *
	 * @since	3.53.114.661
	 * @date	10-Feb-18
	 *
	 * @param	p_pMachineCode	Defines the machine code.
	 * @param	p_iSize	Defines the size of the machine code.
	*/
	void Disassemble(const void * p_pMachineCode, size_t p_iSize);
	/**
	 * Returns the name of the variable matching the address.
	 *
	 * @since	3.53.114.661
	 * @date	10-Feb-18
	 *
	 * @return	The name of the variable if it succeeds, otherwise null.
	*/
	const char * GetVariableName(const void * p_pAddress);

private:
	struct Instruction
	{
		uint64_t ullInstruction;
		uint64_t ullMask;
		std::function<void(BiaMachineDecoder*, const uint8_t*)> callback;
		uint8_t ucSize;
	};

	const BiaMachineContext * m_pMachineContextAddress;	/**	Defines the address of the machine context.	*/
	variable_index & m_index;	/**	Defines the index holding all global variables.	*/

	static std::vector<Instruction> m_svInstructions;	/**	Defines all known machine instructions.	*/
	static std::map<const void*, std::string> m_sFunctions;	/**	Defines all known functions.	*/


	/**
	 * Initializes the disassembler.
	 *
	 * @since	3.53.114.661
	 * @date	10-Feb-18
	*/
	static void Initialize();
	/**
	 * Adds an instruction to the set.
	 *
	 * @since	3.53.114.661
	 * @date	10-Feb-18
	 *
	 * @param	p_ullInstruction	Defines the instruction code.
	 * @param	p_ucFirstBitCount	Defines how many of the first bit are constant.
	 * @param	p_ucInstructionSize	Defines the total instruction size in bytes.
	 * @param	p_callback	Defines the callback function that should be called upon recognition ot the instruction.
	*/
	static void AddInstruction(uint64_t p_ullInstruction, uint8_t p_ucFirstBitCount, uint8_t p_ucInstructionSize, std::function<void(BiaMachineDecoder*, const uint8_t*)> p_callback);
};

}
}
}