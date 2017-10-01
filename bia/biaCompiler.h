#pragma once

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
		printf("%s BEGIN %zi\n", p_stIndentation.c_str(), p_pBegin->iRuleId);

		for (; p_pBegin < p_pEnd; ++p_pBegin)
		{
			if (p_pBegin->children.first)
			{
				Print(p_stIndentation + "#", p_pBegin->children.first, p_pBegin->children.second);
				p_pBegin = p_pBegin->children.second - 1;
			}
			else
			{
				printf("%s", p_stIndentation.c_str());
				fwrite(p_pBegin->pcString, 1, p_pBegin->iSize, stdout);
				printf(" id: %zi rule: %zi\n", p_pBegin->iTokenId, p_pBegin->iRuleId);
			}
		}

		printf("%s END %zi\n", p_stIndentation.c_str(), p_pBegin->iRuleId);
	}
	inline virtual void Report(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd) override
	{
		Print("", p_pBegin, p_pEnd);

		if (p_pBegin < p_pEnd)
		{
			switch (p_pBegin->iRuleId)
			{
			case grammar::BGR_VARIABLE_DECLARATION:
				HandleVariableDeclaration(p_pBegin->children);

				break;
			default:
				break;
			}
		}
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
	inline void WriteOpCode(machine::OP p_code, const char * p_pcFirst = nullptr, size_t p_iSize = 0, unsigned char p_ucParameterCount = 0xff)
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

		memcpy(&uiOperator, p_pOperator->pcString, std::min(sizeof(unsigned int), p_pOperator->iSize));

		m_output.Write(&uiOperator, sizeof(unsigned int));
	}
	inline void HandleVariableDeclaration(grammar::report_range p_reports)
	{
		HandleValue(p_reports.first[1].children, false);

		//Objectify
		WriteOpCode(machine::OP::OBJECTIFY, p_reports.first->pcString, p_reports.first->iSize);
	}
	template<size_t _RULE_ID, bool _LEFT = true>
	inline const grammar::Report * FindWrapHeader(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd)
	{
		if (_LEFT)
		{
			return nullptr;
		}
		else
		{
			while (p_pEnd-- > p_pBegin)
			{
				if (p_pEnd->iRuleId == _RULE_ID && !p_pEnd->iTokenId)
					return p_pEnd;
			}

			return nullptr;
		}
	}
	inline const grammar::Report * HandleValue(grammar::report_range p_reports, bool p_bPush)
	{
		HandleMathExpression(p_reports.first->children, p_bPush);

		return p_reports.second;
	}
	inline const grammar::Report * HandleMathExpression(grammar::report_range p_reports, bool p_bPush)
	{
		//Push all terms starting from the right
		auto i = p_reports.second;

		while (i = FindWrapHeader<grammar::BGR_MATH_TERM, false>(p_reports.first + 1, i))
		{
			if (i->iRuleId != grammar::BGR_MATH_TERM)
				puts("error");
			else
				puts("sucecs");
			HandleMathTerm(i->children, true);
		}

		//Load the leftmost object
		HandleMathTerm(p_reports.first->children, p_bPush);

		//Call all operators

		return p_reports.second;
	}
	inline const grammar::Report * HandleMathTerm(grammar::report_range p_reports, bool p_bPush)
	{
		//Push all factors starting from the right
		for (auto i = p_reports.second; i = FindWrapHeader<grammar::BGR_MATH_FACTOR, false>(p_reports.first + 1, i);)
			HandleMathFactor(i->children, true);

		Print("@@", p_reports.first, p_reports.second);

		auto bPushed = false;
		auto bLoaded = false;
		auto i = p_reports.first + 3;

		/*do
		{
			const grammar::Report * pOperator = nullptr;

			//Get operator
			if (i + 1 < p_reports.second)
			{
				pOperator = i->children.first;

				i += 2;
			}

			//Load object
			if (!bLoaded)
			{
				if (pOperator)
					HandleMathFactor(p_reports.first->children, false);
				else
				{
					HandleMathFactor(p_reports.first->children, p_bPush);

					bPushed = true;
				}

				bLoaded = true;
			}

			//Call operator
			if (pOperator)
				WriteOperator(machine::OP::CALL_OPERATOR, pOperator);
		} while (i < p_reports.second);*/

		//Push accumulator
		if (p_bPush && !bPushed)
			WriteOpCode(machine::OP::PUSH_ACCUMULATOR);

		return p_reports.second;
	}
	inline const grammar::Report * HandleMathFactor(grammar::report_range p_reports, bool p_bPush)
	{
		switch (p_reports.first->iRuleId)
		{
		case grammar::BGR_MATH_EXPRESSION:
			HandleMathExpression(p_reports.first->children, p_bPush);

			break;
		case grammar::BGR_VALUE_RAW:
			HandleValueRaw(p_reports.first->children, p_bPush);

			break;
		default:
			throw exception::ImplementationException("Invalid switch case.");
		}

		return p_reports.second;
	}
	inline void HandleValueRaw(grammar::report_range p_reports, bool p_bPush)
	{
		switch (p_reports.first->iTokenId)
		{
		case grammar::BV_NUMBER:
			HandleNumber(p_reports.first, p_bPush ? NUMBER_TYPE::PUSH : NUMBER_TYPE::LOAD);

			return;
		case grammar::BV_TRUE:
			WriteOpCode(p_bPush ? machine::OP::PUSH_LONG_1 : machine::OP::LOAD_LONG_1);

			return;
		case grammar::BV_FALSE:
			WriteOpCode(p_bPush ? machine::OP::PUSH_LONG_0 : machine::OP::LOAD_LONG_0);

			return;
		}

		//Push accumulator
		if (p_bPush)
			WriteOpCode(machine::OP::PUSH_ACCUMULATOR);
	}
	inline void HandleNumber(const grammar::Report * p_pReport, NUMBER_TYPE p_type)
	{
		auto bPush = p_type == NUMBER_TYPE::PUSH;

		switch (p_pReport->ullCustomParameter)
		{
		case grammar::NI_INTEGER:
		{
			auto llTmp = 0ll;

			if (p_pReport->iSize < 128)
			{
				char acTmp[129];

				memcpy(acTmp, p_pReport->pcString, p_pReport->iSize);
				acTmp[p_pReport->iSize] = 0;

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

			if (p_pReport->iSize < 128)
			{
				char acTmp[129];

				memcpy(acTmp, p_pReport->pcString, p_pReport->iSize);
				acTmp[p_pReport->iSize] = 0;

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

			if (p_pReport->iSize < 128)
			{
				char acTmp[129];

				memcpy(acTmp, p_pReport->pcString, p_pReport->iSize);
				acTmp[p_pReport->iSize] = 0;

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
			throw exception::ImplementationException("Invalid custom parameter.");
		}
	}
};

}
}
}