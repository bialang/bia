#pragma once

#include <cstdint>
#include <functional>
#include <vector>
#include <map>
#include <string>

#include "machine_context.hpp"


namespace bia
{
namespace machine
{

class disassembler
{
public:
	disassembler(const void * _context_address) noexcept;
	void disassemble(const void * _code, size_t _size) const;
	/**
	 * Returns the name for the given address.
	 *
	 * @since 3.64.127.718
	 * @date 16-May-18
	 *
	 * @param _address The address.
	 *
	 * @return The name if available, otherwise null.
	*/
	const char * get_name(const void * _address) const noexcept;

private:
	struct instruction
	{
		typedef std::function<void(const disassembler*, const uint8_t*)> callback_function;

		uint64_t op_code;
		uint64_t mask;
		callback_function callback;
		uint8_t size;
	};

	typedef std::vector<instruction> instruction_list;
	typedef std::map<const void*, std::string> function_map;

	//const BiaMachineContext * m_pMachineContextAddress;	/**	Defines the address of the machine context.	*/
	//variable_index & m_index;	/**	Defines the index holding all global variables.	*/

	const void * _context_address;

	/** Holds all used machine instructions. */
	static instruction_list _instructions;
	/** Holds all addresses of all Bia functions. */
	static function_map _function_map;


	static instruction_list init_instructions();
	static function_map init_function_map();
};

}
}