#pragma once

#include <algorithm>

#include "utf8.h"
#include "yinterpreter.h"
#include "biaOpCodes.h"
#include "biaConditionMarker.h"
#include "biaException.h"
#include "biaStream.h"
#include "biaHash.h"


namespace bia
{
namespace api
{
namespace compiler
{

template<utf8::uint32_t _DELIMITER>
struct UTF8StringChecker : CustomChecker
{
	UTF8StringChecker(long long p_llTokenId) : CustomChecker(p_llTokenId) {}

	// Inherited via SCustomChecker
	virtual bool Check(const ycode & p_code, size_t & p_iSize, long long & p_llCustomTokenId, const unsigned int&, const unsigned int&) override
	{
		auto pStart = p_code.GetBuffer<char>();
		auto i = pStart;

		p_llCustomTokenId = cllTokenId;


		for (auto cond = pStart + p_code.GetSize(); i < cond;)
		{
			try
			{
				switch (utf8::next(i, cond))
				{
				case _DELIMITER:
					utf8::prior(i, pStart);

					p_iSize = i - pStart;

					return true;
				case '\\':
					utf8::next(i, cond);

					break;
				default:
					break;
				}
			}
			catch (...)
			{
				break;
			}
		}

		return false;
	}
};

template<char _DELIMITER>
struct ByteStringChecker : CustomChecker
{
	ByteStringChecker(long long p_llTokenId) : CustomChecker(p_llTokenId) {}

	// Inherited via SCustomChecker
	virtual bool Check(const ycode & p_code, size_t & p_iSize, long long & p_llCustomTokenId, const unsigned int&, const unsigned int&) override
	{
		p_llCustomTokenId = cllTokenId;

		for (auto pStart = reinterpret_cast<const char*>(p_code.GetBuffer()), i = pStart, cond = pStart + p_code.GetSize(); i < cond; ++i)
		{
			switch (*i)
			{
			case _DELIMITER:
				p_iSize = i - pStart;

				return true;
			case '\\':
				++i;

				break;
			default:
				break;
			}
		}

		return false;
	}
};

struct CustomOperatorChecker : CustomChecker
{
	CustomOperatorChecker(long long p_llTokenId) : CustomChecker(p_llTokenId) {}

	// Inherited via SCustomChecker
	virtual bool Check(const ycode & p_code, size_t & p_iSize, long long & p_llCustomTokenId, const unsigned int&, const unsigned int&) override
	{
		p_llCustomTokenId = cllTokenId;

		auto bInvalid = false;

		for (auto pStart = p_code.GetBuffer<char>(), i = pStart, cond = pStart + p_code.GetSize(); i < cond; ++i)
		{
			switch (*i)
			{
			case '>':
			case '<':
				bInvalid = i == pStart;

				break;
			case '&':
			case '|':
				if (i == pStart && i + 1 < cond && i[1] == *i)
				{
					bInvalid = true;

					++i;

					break;
				}
			case '+':
			case '-':
			case '^':
			case '°':
			case '~':
			case '#':
			case '!':
			case '§':
			case '$':
				bInvalid = false;

				break;
			case ' ':
			default:
				p_iSize = i - pStart;

				return p_iSize > 0 && !bInvalid;
			}
		}

		return false;
	}
};

struct AssignChecker : CustomChecker
{
	AssignChecker(long long p_llTokenId) : CustomChecker(p_llTokenId) {}

	// Inherited via SCustomChecker
	virtual bool Check(const ycode & p_code, size_t & p_iSize, long long & p_llCustomTokenId, const unsigned int&, const unsigned int&) override
	{
		p_llCustomTokenId = cllTokenId;

		auto bInvalid = true;

		for (auto pStart = p_code.GetBuffer<char>(), i = pStart, cond = pStart + p_code.GetSize(); i < cond; ++i)
		{
			switch (*i)
			{
			case '>':
			case '<':
			case '&':
			case '|':
			case '+':
			case '-':
			case '*':
			case '/':
			case '^':
			case '°':
			case '~':
			case '#':
			case '!':
			case '§':
			case '$':
			case '%':
				break;
			case '=':
				bInvalid = false;
				++i;
			case ' ':
			default:
				p_iSize = i - pStart;

				return p_iSize > 0 && !bInvalid;
			}
		}

		return false;
	}
};


class BiaCompiler : public yu::interpret::CRuleHandler
{
public:
	/**
	 * Constructor.
	 *
	 * @param	[in,out]	p_output	Defines the compiled output.
	*/
	BiaCompiler(stream::BiaStream & p_output);
	virtual void CommenceReporting() override;
	virtual void CompleteReport() override;
	virtual void Report(const std::vector<yu::interpret::SReport> & p_vReports) override;
	virtual size_t CancelReport(const ycode * p_pCode) override;

private:
	enum class PUSH_TYPE
	{
		LOAD,
		LOAD_COPY,
		PUSH,
		PUSH_COPY
	};
	enum class NUMBER_TYPE : char
	{
		PUSH,
		LOAD,
		WRITE
	};

	stream::BiaStream & m_output;

	/**
	 * Prints the rule tree to the console.
	 *
	 * @since	1.7.24.158
	 * @date	22-Apr-17
	 *
	 * @param   p_pvReport	Defines the reports.
	 * @param	p_stIndent	Defines the indent.
	*/
	static void PrintReport(const std::vector<yu::interpret::SReport> * p_pvReport, std::string p_stIndent);
	/**
	 * Handles the root rule.
	 *
	 * @since	1.7.24.158
	 * @date	22-Apr-17
	 *
	 * @param   p_pBegin	Defines the begin of the rule.
	 * @param	p_pEnd	Defines the end of the rule.
	 *
	 * @throws	bia::exception::ArgumentException	Thrown when the number is invalid.
	*/
	void HandleRoot(const yu::interpret::SReport * p_pBegin, const yu::interpret::SReport * p_pEnd);
	/**
	 * Writes the specified operation code with its parameters to the stream.
	 *
	 * @since	1.4.10.65
	 * @date	19-Apr-17
	 *
	 * @param   p_code	p_code	Defines the operation code.
	 * @param	p_pFirst	(Optional)	Defines the first parameter.
	 * @param	p_pszCallType	(Optional)	Defines the call type of the first parameter.
	 * @param	p_pSecond	(Optional)	Defines the second parameter.
	 * @param	p_ucParameterCount	(Optional)	Defines the parameter count.
	*/
	void WriteOpCode(machine::OP p_code, const ycode * p_pFirst = nullptr, unsigned char p_ucParameterCount = 0xff);
	void WriteOperator(machine::OP p_code, const ycode & p_operator);
	/**
	 * Writes a constant value to the buffer.
	 *
	 * @since	1.7.24.158
	 * @date	22-Apr-17
	 *
	 * @param   p_code	Defines the operation code.
	 * @param	p_value	Defines the constant value.
	*/
	template<typename T>
	inline void WriteConstant(machine::OP p_code, T p_value)
	{
		m_output.Write(&p_code, sizeof(machine::OP));
		m_output.Write(&p_value, sizeof(T));
	}
	/**
	 * Handles the number rule.
	 *
	 * @since	1.7.24.158
	 * @date	22-Apr-17
	 *
	 * @param   p_pReport	Defines the report.
	 *
	 * @throws	bia::exception::ArgumentException	Thrown when the number is invalid.
	*/
	void HandleNumber(const yu::interpret::SReport * p_pReport, NUMBER_TYPE p_type);
	/**
	 * Handles the next value_.
	 *
	 * @since	1.4.8.60
	 * @date	19-Apr-17
	 *
	 * @param   p_pReport	Defines the report.
	 * @param	p_bPush	Defines whether the value should be pushed.
	 *
	 * @throws	bia::exception::ArgumentException	Thrown when the number is invalid.
	*/
	void HandleValue_(const yu::interpret::SReport * p_pReport, const bool & p_bPush);
	/**
	 * Handles the next value.
	 *
	 * @since	1.4.8.60
	 * @date	19-Apr-17
	 *
	 * @param   p_pReport	Defines the report.
	 * @param	p_bPush	Defines whether the value should be pushed.
	 *
	 * @throws	bia::exception::ArgumentException	Thrown when the number is invalid.
	*/
	void HandleValue(const yu::interpret::SReport * p_pReport, bool p_bPush, compiler::BiaConditionMaker * p_pMaker = nullptr);
	void HandleLoopRegisters(const yu::interpret::SReport * p_pRegisterBegin, const yu::interpret::SReport * p_pRegisterEnd, const yu::interpret::SReport * p_pBegin, const yu::interpret::SReport * p_pEnd);
	void HandleMathExpression(const yu::interpret::SReport * p_pReport, const bool & p_bPush);
	void HandleMathTerm(const yu::interpret::SReport * p_pReport, const bool & p_bPush);
	void HandleMathFactor(const yu::interpret::SReport * p_pReport, const bool & p_bPush);
	/**
	 * Handles the variable declaration.
	 *
	 * @since	1.4.8.60
	 * @date	19-Apr-17
	 *
	 * @param   p_pReport	Defines the report.
	 *
	 * @throws	bia::exception::ArgumentException	Thrown when a number is invalid.
	*/
	void HandleVariableDeclaration(const yu::interpret::SReport * p_pReport);
	void HandleVariableAssignment(const yu::interpret::SReport * p_pReport);
	/**
	 * Handles multiple calls.
	 *
	 * @since	1.4.8.60
	 * @date	19-Apr-17
	 *
	 * @param   p_pReport	Defines the report.
	 * @param	p_type	Defines the push type.
	 *
	 * @throws	bia::exception::ArgumentException	Thrown when a number is invalid.
	*/
	void HandleMemberCall(const yu::interpret::SReport * p_pReport, PUSH_TYPE p_type);
	/**
	 * Handles the instantiation rule.
	 *
	 * @since	1.7.24.158
	 * @date	22-Apr-17
	 *
	 * @param   p_pReport	Defines the report.
	 *
	 * @throws	bia::exception::ArgumentException	Thrown when a number is invalid.
	*/
	void HandleInstatiation(const yu::interpret::SReport * p_pReport);
	/**
	 * Checks if the next identifier is a function call.
	 *
	 * @since	1.4.8.60
	 * @date	19-Apr-17
	 *
	 * @param   p_pBegin	Defines the begin.
	 * @param	p_pEnd	Defines the end.
	 *
	 * @return  true if the identifier is a function call, otherwise false.
	*/
	bool IsFunction(const yu::interpret::SReport * p_pBegin, const yu::interpret::SReport * p_pEnd, bool p_bOrItemAccess);
	/**
	 * Handles the next parameter list.
	 *
	 * @since	1.7.24.158
	 * @date	22-Apr-17
	 *
	 * @param   p_pReport	Defines the report.
	 *
	 * @throws	bia::exception::ArgumentException	Thrown when a number is invalid.
	 *
	 * @return  The amount of pushed parameters.
	*/
	unsigned char HandleIdentifierAccess(const yu::interpret::SReport * p_pReport);
};

}
}
}