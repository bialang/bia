#include "biaMachineContext.h"
#include "biaMachineHelper.h"


namespace bia
{
namespace machine
{

void BiaMachineContext::Execute(stream::BiaByteStream p_byteCode)
{
	//Initialize context and machine
	InitiaiteContext(&p_byteCode);

	//Main execution loop
	try
	{
		BiaMachineHelper::ExecutionLoop(this, false);
	}
	catch (...)
	{
		m_accumulator.Clear();
		m_stack.Clear();

		throw;
	}

	m_accumulator.Clear();
	m_stack.Clear();
}

/*
bool BiaMachineContext::Execute(api::BiaParameter & p_return, api::BiaParameter * p_pBegin, const api::BiaParameter * p_pEnd, stream::BiaByteStream & p_byteCode)
{
	auto pCode = m_pCode;

	m_pCode = &p_byteCode;

	m_scope.OpenScope();

	//Make parameter
	while (m_pCode->GoodToRead())
	{
		if (m_pCode->Read<OP>() == OP::MAKE_PARAMETER)
		{
			//Too few parameters
			if (p_pBegin >= p_pEnd)
				return false;

			switch (p_pBegin->GetType())
			{
			case api::BiaParameter::TYPE::MEMBER:
				m_scope.AddVariable(BiaMachineHelper::LoadKeyToken(*m_pCode), p_pBegin++->MoveMemberHolder(), true);

				break;
			case api::BiaParameter::TYPE::REFERENCE:
				m_scope.AddVariable(BiaMachineHelper::LoadKeyToken(*m_pCode), p_pBegin++->MoveScopeReference(), true);

				break;
			default:
				throw exception::AccessViolationException("Invalid parameter");
			}
		}
		else
		{
			//Undo cursor move of read
			m_pCode->pcCursor -= sizeof(OP);

			break;
		}
	}

	//Too many arguments
	if (m_pCode->pcCursor < m_pCode->pcByteCodeEnd && p_pBegin < p_pEnd)
		return false;

	try
	{
		BiaMachineHelper::ExecutionLoop(this, true);
	}
	catch (...)
	{
		//Clean up
		m_pCode = pCode;

		m_scope.CloseScope();

		throw;
	}

	//Clean up
	m_pCode = pCode;

	m_scope.CloseScope();

	if (&p_return != &m_accumulator)
		p_return = std::move(m_accumulator);

	return true;
}
*/
}
}