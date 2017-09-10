#pragma once

#include "biaGrammar.h"
#include "biaReportBundle.h"
#include "biaStream.h"
#include "biaHash.h"


namespace bia
{
namespace api
{
namespace compiler
{

class BiaCompiler : public grammar::BiaReportReceiver
{
public:
	inline BiaCompiler(stream::BiaStream & p_output) : m_output(p_output) {}
	inline virtual void Report(const grammar::BiaReportBundle & p_bundle) override
	{
		for (auto i = p_bundle.Begin(), cond = p_bundle.End(); i < cond; ++i)
		{
			fwrite(i->pcString, 1, i->iSize, stdout);
			printf(" id: %zi rule: %zi\n", i->iTokenId, i->iRuleId);
		}

		auto pBegin = p_bundle.Begin();
		auto pEnd = p_bundle.End();

		if (pBegin < pEnd)
		{
			switch (pBegin->iRuleId)
			{
			case grammar::BGR_VARIABLE_DECLARATION:
				HandleVariableDeclaration(pBegin, pEnd);

				break;
			default:
				break;
			}
		}
	}

private:
	stream::BiaStream & m_output;


	/**
	 * Writes an operation code with a following constant.
	 *
	 * @since	2.39.81.474
	 * @date	10-Sep-17
	 *
	 * @param	p_code	Defines the operation code.
	 * @param	p_value	Defines the constant value.
	*/
	template<typename T>
	inline void WriteConstant(machine::OP p_code, T p_value)
	{
		m_output.Write(&p_code, sizeof(machine::OP));
		m_output.Write(&p_value, sizeof(T));
	}
	/**
	 * Writes an operation code with some parameters.
	 *
	 * @since	2.39.81.474
	 * @date	10-Sep-17
	 *
	 * @param	p_code	Defines the operation code.
	 * @param	p_pcFirst	Defines the first parameter.
	 * @param	p_iSize	Defines the size of the first parameter.
	 * @param	p_ucParameterCount	(Optional)	Defines a parameter count.
	 *
	 * @throws	bia::exception::SymbolException	Thrown when the size of the first parameter is too long.
	*/
	inline void WriteOpCode(machine::OP p_code, const char * p_pcFirst, size_t p_iSize, unsigned char p_ucParameterCount = 0xff)
	{
		m_output.Write(&p_code, sizeof(machine::OP));

		if (p_ucParameterCount != 0xff)
			m_output.Write(&p_ucParameterCount, sizeof(unsigned char));

		//First
		if (p_pcFirst)
		{
			//Too large
			if (p_iSize > 0xff)
				throw exception::SymbolException("Symbol too long");

			auto ucSize = static_cast<unsigned char>(p_iSize);
			auto ullHash = utility::Hash64(p_pcFirst, ucSize);
			auto uiHash = utility::Hash32(p_pcFirst, ucSize);

			m_output.Write(&ullHash, 8);
			m_output.Write(&uiHash, 4);
			m_output.Write(&ucSize, sizeof(unsigned char));
			m_output.Write(p_pcFirst, p_iSize);
		}
	}
	/*void BiaCompiler::WriteOperator(OP p_code, const ycode & p_operator)
	{
		m_output.Write(&p_code, sizeof(OP));

		unsigned int uiOperator = 0;

		memcpy(&uiOperator, p_operator.GetBuffer(), std::min(sizeof(unsigned int), p_operator.GetSize()));

		m_output.Write(&uiOperator, sizeof(unsigned int));
	}*/
	inline void HandleVariableDeclaration(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd)
	{
		HandleValue(p_pBegin + 1, p_pEnd, false);

		//Objectify
		WriteOpCode(machine::OP::OBJECTIFY, p_pBegin->pcString, p_pBegin->iSize);
	}
	inline void HandleValue(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd, bool p_bPush)
	{

	}
};

}
}
}