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
	inline virtual void Report(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd) override
	{
		Print("", p_pBegin, p_pEnd);

		if (p_pBegin < p_pEnd)
		{
			switch (p_pBegin->unRuleId)
			{
			case grammar::BGR_VARIABLE_DECLARATION:
				HandleVariableDeclaration(p_pBegin->content.children);

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
	inline void HandleVariableDeclaration(grammar::report_range p_reports)
	{
		//Handle value
		HandleValue(p_reports.pBegin[2].content.children, false);

		//Objectify
		WriteOpCode(machine::OP::OBJECTIFY, p_reports.pBegin[1].content.token.pcString, p_reports.pBegin[1].content.token.iSize);
	}
	inline void HandleValueRaw(grammar::report_range p_reports, bool p_bPush)
	{
		switch (p_reports.pBegin->unRuleId)
		{
		case grammar::BGR_VALUE_RAW:
		{
			switch (p_reports.pBegin->unTokenId)
			{
			case grammar::BV_NUMBER:
				HandleNumber(p_reports.pBegin, p_bPush ? NUMBER_TYPE::PUSH : NUMBER_TYPE::LOAD);

				return;
			case grammar::BV_TRUE:
				WriteOpCode(p_bPush ? machine::OP::PUSH_LONG_1 : machine::OP::LOAD_LONG_1);

				return;
			case grammar::BV_FALSE:
				WriteOpCode(p_bPush ? machine::OP::PUSH_LONG_0 : machine::OP::LOAD_LONG_0);

				return;
			}
		}
		case grammar::BGR_INSTANTIATION:
			HandleInstantiation(p_reports, p_bPush);

			return;
		}
	}
	inline void HandleNumber(const grammar::Report * p_pReport, NUMBER_TYPE p_type)
	{
		auto bPush = p_type == NUMBER_TYPE::PUSH;

		switch (p_pReport->ullCustomParameter)
		{
		case grammar::NI_INTEGER:
		{
			auto llTmp = 0ll;

			if (p_pReport[1].content.token.iSize < 128)
			{
				char acTmp[129];

				memcpy(acTmp, p_pReport[1].content.token.pcString, p_pReport[1].content.token.iSize);
				acTmp[p_pReport[1].content.token.iSize] = 0;

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

			if (p_pReport[1].content.token.iSize < 128)
			{
				char acTmp[129];

				memcpy(acTmp, p_pReport[1].content.token.pcString, p_pReport[1].content.token.iSize);
				acTmp[p_pReport[1].content.token.iSize] = 0;

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

			if (p_pReport[1].content.token.iSize < 128)
			{
				char acTmp[129];

				memcpy(acTmp, p_pReport[1].content.token.pcString, p_pReport[1].content.token.iSize);
				acTmp[p_pReport[1].content.token.iSize] = 0;

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
	inline uint8_t HandleParameter(grammar::report_range p_reports)
	{
		uint8_t ucParameterCount = 0;

		for (; p_reports.pBegin < p_reports.pEnd; ++p_reports.pBegin, ++ucParameterCount)
		{
			if (p_reports.pBegin->content.children.pEnd)
				p_reports.pBegin = p_reports.pBegin->content.children.pEnd;
		}

		return ucParameterCount;
	}
	template<uint32_t _RULE_ID, uint32_t _DEPTH, bool _LEFT = true>
	inline const grammar::Report * FindWrapHeader(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd)
	{
		if (_LEFT)
		{
			return nullptr;
		}
		else
		{
			printf("%lu\n", _RULE_ID);
			Print("==", p_pBegin, p_pEnd);

			uint32_t unDepth = 0;

			while (p_pEnd-- > p_pBegin)
			{
				//Token end found
				if (p_pEnd->type == grammar::Report::T_END)
				{
					//Searched token
					if (unDepth <= _DEPTH && p_pEnd->unRuleId == _RULE_ID)
						return p_pEnd->content.children.pBegin;
					//Skip
					else if (unDepth >= _DEPTH)
						p_pEnd = p_pEnd->content.children.pBegin;
					else
						++unDepth;
				}
				else if (p_pEnd->type == grammar::Report::T_BEGIN)
					--unDepth;
			}
			/*
			for (; p_pEnd > p_pBegin; --p_pEnd)
			{
				if(p_pEnd->children)
			}

			while (p_pEnd-- > p_pBegin)
			{
				if (p_pEnd->iRuleId == _RULE_ID && !p_pEnd->iTokenId)
					return p_pEnd;
			}*/

			return nullptr;
		}
	}
	inline const grammar::Report * HandleValue(grammar::report_range p_reports, bool p_bPush)
	{
		HandleMathExpression(p_reports.pBegin[1].content.children, p_bPush);

		return p_reports.pEnd + 1;
	}
	inline const grammar::Report * HandleMathExpression(grammar::report_range p_reports, bool p_bPush)
	{
		//Push all terms starting from the right
		for (auto i = p_reports.pEnd; i = FindWrapHeader<grammar::BGR_MATH_TERM, 10, false>(p_reports.pBegin + 1, i);)
			HandleMathTerm(i[1].content.children, true);

		//With operator
		if (p_reports.pBegin->content.children.pEnd + 1 < p_reports.pEnd && p_reports.pBegin->content.children.pEnd->unRuleId == grammar::BGR_MATH_EXPRESSION_HELPER_0)
		{
			//First write first object and then write all operators
			for (auto i = HandleMathTerm(p_reports.pBegin[1].content.children, false); i < p_reports.pEnd; i = (++i)->content.children.pEnd)
				WriteOperator(machine::OP::CALL_OPERATOR, i);

			//Push result if needed
			if (p_bPush)
				WriteOpCode(machine::OP::PUSH_ACCUMULATOR);
		}
		else
			HandleMathTerm(p_reports.pBegin[1].content.children.pBegin[1].content.children, p_bPush);
		
		return p_reports.pEnd + 1;
	}
	inline const grammar::Report * HandleMathTerm(grammar::report_range p_reports, bool p_bPush)
	{
		//Push all factors starting from the right
		for (auto i = p_reports.pEnd; i = FindWrapHeader<grammar::BGR_MATH_FACTOR, 10, false>(p_reports.pBegin + 1, i);)
			HandleMathFactor(i[1].content.children, true);

		//With operator
		if (p_reports.pBegin->content.children.pEnd + 1 < p_reports.pEnd && p_reports.pBegin->content.children.pEnd->unRuleId == grammar::BGR_MATH_TERM_HELPER_1)
		{
			//First write first object and then write all operators
			for (auto i = HandleMathFactor(p_reports.pBegin[1].content.children, false); i < p_reports.pEnd; i = (++i)->content.children.pEnd)
				WriteOperator(machine::OP::CALL_OPERATOR, i);

			//Push result if needed
			if (p_bPush)
				WriteOpCode(machine::OP::PUSH_ACCUMULATOR);
		}
		else
			HandleMathFactor(p_reports.pBegin[1].content.children, p_bPush);

		return p_reports.pEnd + 1;
	}
	inline const grammar::Report * HandleMathFactor(grammar::report_range p_reports, bool p_bPush)
	{
		switch (p_reports.pBegin->unRuleId)
		{
		case grammar::BGR_MATH_EXPRESSION:
			HandleMathExpression(p_reports.pBegin[1].content.children, p_bPush);
			
			break;
		case grammar::BGR_VALUE_RAW:
			HandleValueRaw(p_reports.pBegin->content.children, p_bPush);

			break;
		default:
			throw exception::ImplementationException("Invalid switch case.");
		}

		return p_reports.pEnd + 1;
	}
	inline const grammar::Report * HandleInstantiation(grammar::report_range p_reports, bool p_bPush)
	{
		/*
		if (p_pReport->pvTokenUnion->size() == 2)
		{
		p_pReport = p_pReport->pvTokenUnion->begin()._Ptr;

		WriteOpCode(OP::INSTANTIATE, &p_pReport[0].code, HandleIdentifierAccess(p_pReport + 1));
		}
		else
		{
		p_pReport = p_pReport->pvTokenUnion->begin()._Ptr;

		auto ucParameterCount = HandleIdentifierAccess(p_pReport + 2);

		WriteOpCode(OP::LOAD, &p_pReport->code);
		WriteOpCode(OP::INSTANTIATE_ACCUMULATOR, &p_pReport[1].code, ucParameterCount);
		}
		*/

		WriteOpCode(machine::OP::INSTANTIATE, p_reports.pBegin[1].content.token.pcString, p_reports.pBegin[1].content.token.iSize, HandleParameter(p_reports.pBegin[2].content.children));

		//Push if wanted
		if (p_bPush)
			WriteOpCode(machine::OP::PUSH_ACCUMULATOR);

		return p_reports.pEnd + 1;
	}
};

}
}
}