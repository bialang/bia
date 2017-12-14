#include "biaMachineCode.h"

#include <sys/mman.h>


namespace bia
{
namespace machine
{

BiaMachineCode::BiaMachineCode(stream::BiaByteStream p_machineCode)
{
	m_iSize = p_machineCode.GetSize();

	//Allocate virtual memory
	auto pCode = mmap(nullptr, m_iSize, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if (pCode != reinterpret_cast<void*>(-1))
	{
		//Copy machine code to executable memory
		memcpy(pCode, p_machineCode.GetBase(), m_iSize);

		//Protect memory
		if (!mprotect(pCode, m_iSize, PROT_EXEC))
		{
			m_run = static_cast<entry_point>(pCode);

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
		munmap(m_run, m_iSize);
}

void BiaMachineCode::Execute(BiaMachineContext & p_context) const
{
	m_run(&p_context);
}

bool BiaMachineContext::IsValid() const
{
	return m_run && m_iSize;
}

}
}