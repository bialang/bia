#include "biaMachineCode.hpp"
#include "biaException.hpp"

#include <cstring>


namespace bia
{
namespace machine
{

BiaMachineCode::BiaMachineCode(std::pair<const uint8_t*, size_t> p_machineCode, BiaMachineSchein p_machineSchein) : m_machineSchein(std::move(p_machineSchein))
{
	m_run = m_machineSchein.GetAllocator()->Allocate(p_machineCode.second, BiaAllocator::MEMORY_TYPE::EXECUTABLE_MEMORY);

	//Copy code
	if (m_run.pAddress)
	{
		memcpy(m_run.pAddress, p_machineCode.first, m_run.iSize);

		///Protect memory
	}
	else
		throw exception::AllocationException("Cannot allocate executable memory.");
	/*
#ifdef _WIN32
	//Allocate virtual memory
	if (auto pCode = VirtualAlloc(nullptr, p_machineCode.second, MEM_COMMIT, PAGE_READWRITE))
	{
		//Copy nachine code to executable memory
		memcpy(pCode, p_machineCode.first, p_machineCode.second);

		//Protect memory
		DWORD oldProtect = 0;

		if (VirtualProtect(pCode, p_machineCode.second, PAGE_EXECUTE, &oldProtect))
		{
			m_run = reinterpret_cast<entry_point>(pCode);
			m_iSize = p_machineCode.second;

			return;
		}

		VirtualFree(reinterpret_cast<void*>(m_run), 0, MEM_RELEASE);
	}
#else
	//Allocate virtual memory
	auto pCode = mmap(nullptr, p_machineCode.second, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if (pCode != reinterpret_cast<void*>(-1))
	{
		//Copy machine code to executable memory
		memcpy(pCode, p_machineCode.first, p_machineCode.second);

		//Protect memory
		if (!mprotect(pCode, p_machineCode.second, PROT_EXEC))
		{
			m_run = reinterpret_cast<entry_point>(pCode);
			m_iSize = p_machineCode.second;

			return;
		}

		munmap(pCode, m_iSize);
	}
#endif
*/
}

BiaMachineCode::BiaMachineCode(BiaMachineCode && p_move) : m_machineSchein(std::move(p_move.m_machineSchein))
{
	m_run = p_move.m_run;
	p_move.m_run = { nullptr, 0 };
}

BiaMachineCode::~BiaMachineCode()
{
	//Deallocate machine code
	m_machineSchein.GetAllocator()->Deallocate(m_run, BiaAllocator::MEMORY_TYPE::EXECUTABLE_MEMORY);
}

void BiaMachineCode::Execute() const
{
	try
	{
		static_cast<entry_point>(m_run.pAddress)();
	}
	catch (...)
	{
		//Clean up

		throw;
	}
}

bool BiaMachineCode::IsValid()
{
	return m_run.pAddress && m_run.iSize;
}

}
}