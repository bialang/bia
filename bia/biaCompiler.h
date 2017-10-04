#pragma once

#include <stdint.h>

#include "biaGrammar.h"
#include "biaReportBundle.h"
#include "biaStream.h"
#include "biaHash.h"

#define BIA_COMPILER_DEV_TEST if(p_pBegin + 1 < p_pEnd){
#define BIA_COMPILER_DEV_TEST_END } throw exception::ImplementationException("Invalid grammar.");
#define BIA_COMPILER_DEV_INVALID throw exception::ImplementationException("Invalid case.");


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
		if (p_children.pBegin->content.children.pBegin == p_children.pBegin->content.children.pEnd)
			return;
		else
			printf("%s  0:BEGIN [%03lu](% 2lu)\n", p_pszIndentation, p_children.pBegin->unRuleId, p_children.pBegin->unTokenId);

		for (auto i = p_children.pBegin + 1; i < p_children.pEnd; ++i)
		{
			switch (i->type)
			{
			case grammar::Report::T_EMPTY_CHILD:
				printf("%s % 2i:EMPTY [%03lu](% 2lu)\n", p_pszIndentation, i - p_children.pBegin, i->unRuleId, i->unTokenId);

				break;
			case grammar::Report::T_BEGIN:
				printf("%s % 2i:CHILD [%03lu](% 2lu)\n", p_pszIndentation, i - p_children.pBegin, i->unRuleId, i->unTokenId);

				i = i->content.children.pEnd;

				break;
			case grammar::Report::T_TOKEN:
				printf("%s % 2i:TOKEN [%03lu](% 2lu) ", p_pszIndentation, i - p_children.pBegin, i->unRuleId, i->unTokenId);
				fwrite(i->content.token.pcString, 1, i->content.token.iSize, stdout);
				puts("");
					
				break;
			default:
				puts("eRror");
				break;
			}
		}
	}
	inline virtual void Report(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd) override
	{
		HandleVariableDeclaration(p_pBegin->content.children);
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
	inline void HandleNumber(const grammar::Report * p_pReport, NUMBER_TYPE p_type)
	{
		auto bPush = p_type == NUMBER_TYPE::PUSH;

		switch (p_pReport->ullCustomParameter)
		{
		case grammar::NI_INTEGER:
		{
			auto llTmp = 0ll;

			if (p_pReport->content.token.iSize < 128)
			{
				char acTmp[129];

				memcpy(acTmp, p_pReport->content.token.pcString, p_pReport->content.token.iSize);
				acTmp[p_pReport->content.token.iSize] = 0;

				//Interpret
				char * pcEnd = nullptr;
				llTmp = strtoll(acTmp, &pcEnd, 10);

				if (acTmp == pcEnd)
					throw exception::ArgumentException("Invalid number.");
			}
			else
				throw exception::ArgumentException("Too long number.");


			if (p_type == NUMBER_TYPE::WRITE)
				m_output.Write(&llTmp, sizeof(long long));
			else
			{
				switch (llTmp)
				{
				case -1:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_LONG_N1 : machine::OP::LOAD_LONG_N1);

					break;
				case 0:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_LONG_0 : machine::OP::LOAD_LONG_0);

					break;
				case 1:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_LONG_1 : machine::OP::LOAD_LONG_1);

					break;
				case 2:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_LONG_2 : machine::OP::LOAD_LONG_2);

					break;
				case 3:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_LONG_3 : machine::OP::LOAD_LONG_3);

					break;
				case 5:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_LONG_5 : machine::OP::LOAD_LONG_5);

					break;
				case 10:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_LONG_10 : machine::OP::LOAD_LONG_10);

					break;
				case 100:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_LONG_100 : machine::OP::LOAD_LONG_100);

					break;
				case 1000:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_LONG_1000 : machine::OP::LOAD_LONG_1000);

					break;
				case 1000000:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_LONG_1000000 : machine::OP::LOAD_LONG_1000000);

					break;
				default:
					WriteConstant(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_LONG : machine::OP::LOAD_LONG, llTmp);

					break;
				}
			}

			break;
		}
		case grammar::NI_FLOAT:
		{
			auto rTmp = 0.0f;

			if (p_pReport->content.token.iSize < 128)
			{
				char acTmp[129];

				memcpy(acTmp, p_pReport->content.token.pcString, p_pReport->content.token.iSize);
				acTmp[p_pReport->content.token.iSize] = 0;

				//Interpret
				char * pcEnd = nullptr;
				rTmp = strtof(acTmp, &pcEnd);

				if (acTmp == pcEnd)
					throw exception::ArgumentException("Invalid number.");
			}
			else
				throw exception::ArgumentException("Too long number.");

			if (p_type == NUMBER_TYPE::WRITE)
				m_output.Write(&rTmp, sizeof(float));
			else
			{
				if (rTmp == 0.0f)
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_FLOAT_0 : machine::OP::LOAD_FLOAT_0);
				else if (rTmp == 1.0f)
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_FLOAT_1 : machine::OP::LOAD_FLOAT_1);
				else if (rTmp == -1.0f)
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_FLOAT_N1 : machine::OP::LOAD_FLOAT_N1);
				else
					WriteConstant(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_FLOAT : machine::OP::LOAD_FLOAT, rTmp);
			}

			break;
		}
		case grammar::NI_DOUBLE:
		{
			auto rTmp = 0.0;

			if (p_pReport->content.token.iSize < 128)
			{
				char acTmp[129];

				memcpy(acTmp, p_pReport->content.token.pcString, p_pReport->content.token.iSize);
				acTmp[p_pReport->content.token.iSize] = 0;

				//Interpret
				char * pcEnd = nullptr;
				rTmp = strtod(acTmp, &pcEnd);

				if (acTmp == pcEnd)
					throw exception::ArgumentException("Invalid number.");
			}
			else
				throw exception::ArgumentException("Too long number.");

			if (p_type == NUMBER_TYPE::WRITE)
				m_output.Write(&rTmp, sizeof(double));
			else
			{
				if (rTmp == 0.0)
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_DOUBLE_0 : machine::OP::LOAD_DOUBLE_0);
				else if (rTmp == 1.0)
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_DOUBLE_1 : machine::OP::LOAD_DOUBLE_1);
				else if (rTmp == -1.0)
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_DOUBLE_N1 : machine::OP::LOAD_DOUBLE_N1);
				else
					WriteConstant(p_type == NUMBER_TYPE::PUSH ? machine::OP::PUSH_DOUBLE : machine::OP::LOAD_DOUBLE, rTmp);
			}

			break;
		}
		default:
			BIA_COMPILER_DEV_INVALID
		}
	}
	inline uint8_t HandleParameter(grammar::report_range p_reports)
	{
		PrintStraight("p>", p_reports);

		uint8_t ucParameterCount = 0;

		++p_reports.pBegin;

		//Push all parameter values
		while (p_reports.pBegin < p_reports.pEnd)
		{
			p_reports.pBegin = HandleValue(p_reports.pBegin->content.children, true);

			if (!++ucParameterCount)
				throw exception::ArgumentException("Too many arguments passed.");
		}

		return ucParameterCount;
	}
	template<uint32_t _RULE_ID, uint32_t _DEPTH, bool _LEFT>
	inline const grammar::Report * FindNextChild(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd)
	{
		if (_LEFT)
		{
			for (uint32_t unDepth = 0; p_pBegin < p_pEnd; ++p_pBegin)
			{
				if (p_pBegin->type == grammar::Report::T_BEGIN)
				{
					//Skip
					if (unDepth > _DEPTH)
						p_pBegin = p_pBegin->content.children.pEnd;
					//Found rule
					else if (p_pBegin->unRuleId == _RULE_ID)
						return p_pBegin;
					//Go deeper
					else
						++unDepth;
				}
				else if (p_pBegin->type == grammar::Report::T_END)
					--unDepth;
			}
		}
		else
		{
			uint32_t unDepth = 0;

			while (p_pEnd-- > p_pBegin)
			{
				if (p_pEnd->type == grammar::Report::T_END)
				{
					//Skip
					if (unDepth > _DEPTH)
						p_pEnd = p_pEnd->content.children.pBegin;
					//Found rule
					else if (p_pEnd->unRuleId == _RULE_ID)
						return p_pEnd->content.children.pBegin;
					//Go deeper
					else
						++unDepth;
				}
				else if (p_pEnd->type == grammar::Report::T_BEGIN)
					--unDepth;
			}
		}

		return nullptr;
	}
	template<uint32_t _RULE_ID, uint32_t _DEPTH, bool _LEFT>
	inline const grammar::Report * FindNextToken(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd)
	{
		if (_LEFT)
		{
			for (uint32_t unDepth = 0; p_pBegin < p_pEnd; ++p_pBegin)
			{
				if (p_pBegin->type == grammar::Report::T_BEGIN)
				{
					//Skip
					if (unDepth > _DEPTH)
						p_pBegin = p_pBegin->content.children.pEnd;
					//Go deeper
					else
						++unDepth;
				}
				else if (p_pBegin->type == grammar::Report::T_END)
					--unDepth;
				//Found token
				else if (p_pBegin->unRuleId == _RULE_ID)
					return p_pBegin;
			}
		}
		else
		{
			uint32_t unDepth = 0;

			while (p_pEnd-- > p_pBegin)
			{
				if (p_pEnd->type == grammar::Report::T_END)
				{
					//Skip
					if (unDepth > _DEPTH)
						p_pEnd = p_pEnd->content.children.pBegin;
					//Go deeper
					else
						++unDepth;
				}
				else if (p_pEnd->type == grammar::Report::T_BEGIN)
					--unDepth;
				//Found token
				else if (p_pBegin->unRuleId == _RULE_ID)
					return p_pBegin;
			}
		}

		return nullptr;
	}
	inline const grammar::Report * HandleVariableDeclaration(grammar::report_range p_reports)
	{
		//Handle value
		HandleValue(p_reports.pBegin[2].content.children, false);

		//Objectify accumulator
		WriteOpCode(machine::OP::OBJECTIFY, p_reports.pBegin[1].content.token.pcString, p_reports.pBegin[1].content.token.iSize);

		return p_reports.pEnd + 1;
	}
	inline const grammar::Report * HandleValue(grammar::report_range p_reports, bool p_bPush)
	{
		HandleMathExpression(p_reports.pBegin[1].content.children, p_bPush);

		return p_reports.pEnd + 1;
	}
	inline const grammar::Report * HandleValueRaw(grammar::report_range p_reports, bool p_bPush)
	{
		PrintStraight("v>", p_reports);

		switch (p_reports.pBegin[1].unTokenId)
		{
		case grammar::BV_NUMBER:
			HandleNumber(p_reports.pBegin + 1, p_bPush ? NUMBER_TYPE::PUSH : NUMBER_TYPE::LOAD);

			break;
		//case grammar::BV_STRING:
		case grammar::BV_TRUE:
			WriteOpCode(p_bPush ? machine::OP::PUSH_LONG_1 : machine::OP::LOAD_LONG_1);

			break;
		case grammar::BV_FALSE:
		case grammar::BV_NULL:
			WriteOpCode(p_bPush ? machine::OP::PUSH_LONG_0 : machine::OP::LOAD_LONG_0);

			break;
		case grammar::BV_INSTANTIATION:
			HandleInstantiation(p_reports.pBegin[1].content.children, p_bPush);

			break;
		case grammar::BV_MEMBER:
			HandleMember(p_reports.pBegin[1].content.children, p_bPush);

			break;
		default:
			BIA_COMPILER_DEV_INVALID
		}

		return p_reports.pEnd + 1;
	}
	inline const grammar::Report * HandleInstantiation(grammar::report_range p_reports, bool p_bPush)
	{
		PrintStraight("i>", p_reports);

		//Instantiate object
		WriteOpCode(machine::OP::INSTANTIATE, p_reports.pBegin[1].content.token.pcString, p_reports.pBegin[1].content.token.iSize, HandleParameter(p_reports.pBegin[2].content.children));

		return p_reports.pEnd + 1;
	}
	inline const grammar::Report * HandleMathExpression(grammar::report_range p_reports, bool p_bPush)
	{
		PrintStraight("e>", p_reports);

		//Handle all math terms starting from the right
		for (auto i = p_reports.pEnd, pBegin = p_reports.pBegin[1].content.children.pEnd + 1; i = FindNextChild<grammar::BGR_MATH_TERM, 0, false>(pBegin, i);)
			HandleMathTerm(i->content.children, true);

		//Only one math term to handle
		if (p_reports.pBegin[1].content.children.pEnd + 1 == p_reports.pEnd)
			HandleMathTerm(p_reports.pBegin[1].content.children, p_bPush);
		else
		{
			//Load the leftmost object
			auto i = HandleMathTerm(p_reports.pBegin[1].content.children, false);

			//Call all operators
			for (auto pEnd = p_reports.pEnd[-1].content.children.pBegin; i = FindNextToken<grammar::BGR_MATH_EXPRESSION_HELPER_0, 0, true>(i, pEnd); ++i)
				WriteOperator(machine::OP::CALL_OPERATOR, i);

			//Push accumulator
			if (p_bPush)
				WriteOpCode(machine::OP::PUSH_ACCUMULATOR);
		}

		return p_reports.pEnd + 1;
	}
	inline const grammar::Report * HandleMathTerm(grammar::report_range p_reports, bool p_bPush)
	{
		PrintStraight("t>", p_reports);

		//Handle all math factors starting from the right
		for (auto i = p_reports.pEnd, pBegin = p_reports.pBegin[1].content.children.pEnd + 1; i = FindNextChild<grammar::BGR_MATH_FACTOR, 0, false>(pBegin, i);)
			HandleMathFactor(i->content.children, true);

		//Only one math factor to handle
		if (p_reports.pBegin[1].content.children.pEnd + 1 == p_reports.pEnd)
			HandleMathFactor(p_reports.pBegin[1].content.children, p_bPush);
		//Call all operator and load the leftmost object
		else
		{
			//Load the leftmost object
			auto i = HandleMathFactor(p_reports.pBegin[1].content.children, false);

			//Call all operators
			for (auto pEnd = p_reports.pEnd[-1].content.children.pBegin; i = FindNextToken<grammar::BGR_MATH_TERM_HELPER_1, 0, true>(i, pEnd); ++i)
				WriteOperator(machine::OP::CALL_OPERATOR, i);

			//Push accumulator
			if (p_bPush)
				WriteOpCode(machine::OP::PUSH_ACCUMULATOR);
		}

		return p_reports.pEnd + 1;
	}
	inline const grammar::Report * HandleMathFactor(grammar::report_range p_reports, bool p_bPush)
	{
		PrintStraight("f>", p_reports);

		switch (p_reports.pBegin[1].unRuleId)
		{
		case grammar::BGR_VALUE_RAW:
			HandleValueRaw(p_reports.pBegin[1].content.children, p_bPush);

			break;
		case grammar::BGR_MATH_EXPRESSION:
			HandleMathExpression(p_reports.pBegin[1].content.children, p_bPush);

			break;
		default:
			BIA_COMPILER_DEV_INVALID
		}

		return p_reports.pEnd + 1;
	}
	inline const grammar::Report * HandleMember(grammar::report_range p_reports, bool p_bPush)
	{
		PrintStraight("m>", p_reports);

		//Handle first element
		do
		{
			if (++p_reports.pBegin + 1 < p_reports.pEnd)
			{
				//Check if this is a function call
				switch (p_reports.pBegin[1].unRuleId)
				{
				case grammar::BGR_PARAMETER:
					//Write global function call
					WriteOpCode(machine::OP::CALL_GLOBAL, p_reports.pBegin->content.token.pcString, p_reports.pBegin->content.token.iSize, HandleParameter(p_reports.pBegin[1].content.children));

					p_reports.pBegin = p_reports.pBegin[1].content.children.pEnd + 1;

					continue;
				case grammar::BGR_PARAMETER_ITEM_ACCESS:
				{
					//Handle parameter
					auto ucParameterCount = HandleParameter(p_reports.pBegin[1].content.children);

					//Write item access
					WriteOpCode(machine::OP::LOAD, p_reports.pBegin->content.token.pcString, p_reports.pBegin->content.token.iSize);
					WriteOpCode(machine::OP::CALL, "[]", 2, ucParameterCount);

					p_reports.pBegin = p_reports.pBegin[1].content.children.pEnd + 1;

					continue;
				}
				case grammar::BGR_MEMBER_HELPER_1:
					break;
				default:
					BIA_COMPILER_DEV_INVALID
				}
			}

			//Load object
			WriteOpCode(machine::OP::LOAD, p_reports.pBegin->content.token.pcString, p_reports.pBegin->content.token.iSize);

			++p_reports.pBegin;
		} while (false);

		//Loop through all remaining elements
		while (p_reports.pBegin < p_reports.pEnd)
		{
			if (p_reports.pBegin + 1 < p_reports.pEnd)
			{
				//Check if this is a function call
				switch (p_reports.pBegin[1].unRuleId)
				{
				case grammar::BGR_PARAMETER:
					//Write function call
					WriteOpCode(machine::OP::CALL, p_reports.pBegin->content.token.pcString, p_reports.pBegin->content.token.iSize, HandleParameter(p_reports.pBegin[1].content.children));

					p_reports.pBegin = p_reports.pBegin[1].content.children.pEnd + 1;

					continue;
				case grammar::BGR_PARAMETER_ITEM_ACCESS:
				{
					//Handle parameter
					auto ucParameterCount = HandleParameter(p_reports.pBegin[1].content.children);

					//Write item access
					WriteOpCode(machine::OP::LOAD, p_reports.pBegin->content.token.pcString, p_reports.pBegin->content.token.iSize);
					WriteOpCode(machine::OP::CALL, "[]", 2, ucParameterCount);

					p_reports.pBegin = p_reports.pBegin[1].content.children.pEnd + 1;

					continue;
				}
				case grammar::BGR_MEMBER_HELPER_1:
					break;
				default:
					BIA_COMPILER_DEV_INVALID
				}
			}
			
			//Load object from accumulator
			WriteOpCode(machine::OP::LOAD_FROM_ACCUMULATOR, p_reports.pBegin->content.token.pcString, p_reports.pBegin->content.token.iSize);

			++p_reports.pBegin;
		}

		return p_reports.pEnd + 1;
	}
};

}
}
}