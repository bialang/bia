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
	inline virtual void Report(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd) override
	{
		for (auto i = p_pBegin, cond = p_pEnd; i < cond; ++i)
		{
			fwrite(i->pcString, 1, i->iSize, stdout);
			printf(" id: %zi rule: %zi depth: %i\n", i->iTokenId, i->iRuleId, i->children.second - i->children.first);
		}

		/*if (p_pBegin < p_pEnd)
		{
			switch (p_pBegin->iRuleId)
			{
			case grammar::BGR_VARIABLE_DECLARATION:
				HandleVariableDeclaration(p_pBegin, p_pEnd);

				break;
			default:
				break;
			}
		}*/
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
	/*void BiaCompiler::WriteOperator(OP p_code, const ycode & p_operator)
	{
		m_output.Write(&p_code, sizeof(OP));

		unsigned int uiOperator = 0;

		memcpy(&uiOperator, p_operator.GetBuffer(), std::min(sizeof(unsigned int), p_operator.GetSize()));

		m_output.Write(&uiOperator, sizeof(unsigned int));
	}*/
	inline const grammar::Report * FindCorrespondingEnd(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd, size_t p_iDepth)
	{
		//while (p_pBegin < p_pEnd && p_pBegin->iDepth >= p_iDepth)
			++p_pBegin;

		return p_pBegin;
	}
	inline void HandleVariableDeclaration(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd)
	{
		HandleValue(p_pBegin + 1, false);

		//Objectify
		WriteOpCode(machine::OP::OBJECTIFY, p_pBegin->pcString, p_pBegin->iSize);
	}
	inline const grammar::Report * HandleValue(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd)
	{
		p_pBegin = HandleMathExpression(p_pBegin, p_pEnd);


		return p_pBegin;
	}
	inline const grammar::Report * HandleMathExpression(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd)
	{
		BIA_COMPILER_DEV_TEST
		auto pInfo = p_pBegin++;

		//p_pEnd = FindCorrespondingEnd(p_pBegin, p_pEnd, pInfo->iDepth);

		do
		{
			//Handle first term
			p_pBegin = HandleMathTerm(p_pBegin, p_pEnd);
		} while (p_pBegin < p_pEnd);

		return p_pBegin;
		BIA_COMPILER_DEV_TEST_END
	}
	inline const grammar::Report * HandleMathTerm(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd)
	{

	}
	inline void HandleValueRaw(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd, bool p_bPush)
	{
		switch (p_pBegin->iTokenId)
		{
		case grammar::BV_NUMBER:
			HandleNumber(p_pBegin, p_bPush ? NUMBER_TYPE::PUSH : NUMBER_TYPE::LOAD);

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