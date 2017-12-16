#include "biaMachineCode.hpp"

#include <sys/mman.h>
#include <cstring>


namespace bia
{
namespace machine
{

BiaMachineCode::BiaMachineCode(std::pair<const uint8_t*, size_t> p_machineCode)
{
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

	m_run = nullptr;
	m_iSize = 0;
}

BiaMachineCode::BiaMachineCode(BiaMachineCode && p_move)
{
	m_run = p_move.m_run;
	m_iSize = p_move.m_iSize;

	p_move.m_run = nullptr;
	p_move.m_iSize = 0;
}

BiaMachineCode::~BiaMachineCode()
{
	if (m_run)
		munmap(reinterpret_cast<void*>(m_run), m_iSize);
}

void BiaMachineCode::Execute() const
{
	m_run();
}

bool BiaMachineCode::IsValid()
{
	return m_run && m_iSize;
}

}
}