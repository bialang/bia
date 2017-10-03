#pragma once

#include <stdint.h>

#include "biaGrammar.h"
#include "biaReportBundle.h"
#include "biaStream.h"
#include "biaHash.h"

#define BIA_COMPILER_DEV_TEST if(p_pBegin + 1 < p_pEnd){
#define BIA_COMPILER_DEV_TEST_END } throw exception::ImplementationException("Invalid grammar.");


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
	inline void Print(std::string p_stIndentation, const grammar::Report * p_pBegin, const grammar::Report * p_pEnd)
	{
		auto unRuleId = p_pBegin->unRuleId;

		printf("%sBEGIN %lu {%llu}\n", p_stIndentation.c_str(), unRuleId, p_pBegin->ullCustomParameter);

		for (; p_pBegin < p_pEnd; ++p_pBegin)
		{
			if (p_pBegin->type == grammar::Report::T_BEGIN)
			{
				Print(p_stIndentation + "|", p_pBegin->content.children.pBegin + 1, p_pBegin->content.children.pEnd);
				p_pBegin = p_pBegin->content.children.pEnd;
			}
			else if (p_pBegin->type == grammar::Report::T_TOKEN)
			{
				printf("%s", p_stIndentation.c_str());
				fwrite(p_pBegin->content.token.pcString, 1, p_pBegin->content.token.iSize, stdout);
				printf(" id: %lu rule: %lu {%llu}\n", p_pBegin->unTokenId, p_pBegin->unRuleId, p_pBegin->ullCustomParameter);
			}
		}

		printf("%sEND %zi\n", p_stIndentation.c_str(), unRuleId);
	}
	inline void PrintStraight(const char * p_pszIndentation, grammar::report_range p_children)
	{
		for (auto i = p_children.pBegin + 1; i <= p_children.pEnd; ++i)
		{
			switch (i->type)
			{
			case grammar::Report::T_BEGIN:
				printf("%s BEGIN [%03lu](% 2lu)\n", p_pszIndentation, i->unRuleId, i->unTokenId);

				i = i->content.children.pEnd;

				break;
			case grammar::Report::T_TOKEN:
				printf("%s TOKEN [%03lu](% 2lu) ", p_pszIndentation, i->unRuleId, i->unTokenId);
				fwrite(i->content.token.pcString, 1, i->content.token.iSize, stdout);
				puts("");

				break;
			default:
				break;
			}
		}
	}
	inline virtual void Report(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd) override
	{
		PrintStraight(">", p_pBegin->content.children);
	}

private:
	enum class NUMBER_TYPE : char
	{
		PUSH,
		LOAD,
		WRITE
	};

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
	 * @param	p_pcFirst	(Optional)	Defines the first parameter.
	 * @param	p_iSize	(Optional)	Defines the size of the first parameter.
	 * @param	p_ucParameterCount	(Optional)	Defines a parameter count.
	 *
	 * @throws	bia::exception::SymbolException	Thrown when the size of the first parameter is too long.
	*/
	inline void WriteOpCode(machine::OP p_code, const char * p_pcFirst = nullptr, size_t p_iSize = 0, uint8_t p_ucParameterCount = 0xff)
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
	inline void WriteOperator(machine::OP p_code, const grammar::Report * p_pOperator)
	{
		m_output.Write(&p_code, sizeof(machine::OP));

		unsigned int uiOperator = 0;

		memcpy(&uiOperator, p_pOperator->content.token.pcString, std::min<uint32_t>(sizeof(unsigned int), p_pOperator->content.token.iSize));

		m_output.Write(&uiOperator, sizeof(unsigned int));
	}
};

}
}
}