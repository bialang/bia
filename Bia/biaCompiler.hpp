#pragma once

#include <cstdint>
#include <cstring>
#include <algorithm>
#include <type_traits>

#include "biaOutputStream.hpp"
#include "biaMachineContext.hpp"
#include "biaReportBundle.hpp"
#include "biaInterpreterIdentifiers.hpp"
#include "biaLink.hpp"
#include "biaToolset.hpp"
#include "biaConstantOperation.hpp"
#include "biaException.hpp"
#include "biaTempCounter.hpp"

#define BIA_COMPILER_DEV_INVALID throw BIA_IMPLEMENTATION_EXCEPTION("Invalid case.");


namespace bia
{
namespace compiler
{

class BiaCompiler  : public grammar::BiaReportReceiver
{
public:
	/**
	 * Constructor.
	 *
	 * @param	[in]	p_output	Defines the output stream for the machine code.
	 * @param	[in]	p_context	Defines the machine context.
	 */
	inline BiaCompiler(stream::BiaOutputStream & p_output, machine::BiaMachineContext & p_context) : m_toolset(p_output), m_context(p_context)
	{
	}

	/**
	 * @see	bia::grammar::BiaReportReceiver::Report().
	 */
	inline virtual void Report(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd) override
	{
		HandleRoot(p_pBegin);
	}

private:
	enum class VALUE_TYPE
	{
		INT_32,
		INT_64,
		FLOAT,
		DOUBLE,
		STRING,
		MEMBER,
		REGISTER,
		NONE,
	};

	union Value
	{
		int32_t nInt;
		int64_t llInt;
		float rFloat;
		double rDouble;
		size_t iString;
		framework::BiaMember * pMember;
		machine::architecture::REGISTER _register;
	};

	machine::architecture::BiaToolset m_toolset;
	machine::BiaMachineContext & m_context;

	VALUE_TYPE m_valueType;
	Value m_value;

	static const void * const m_scpOperatorFunctions[][11];


	inline void SetValue(int32_t p_nValue)
	{
		//m_toolset.Push(p_nValue);
		m_valueType = VALUE_TYPE::INT_32;
		m_value.nInt = p_nValue;
	}
	inline void SetValue(int64_t p_llValue)
	{
		//m_toolset.Push(p_llValue);
		m_valueType = VALUE_TYPE::INT_64;
		m_value.llInt = p_llValue;
	}
	inline void SetValue(float p_rValue)
	{
		//m_toolset.Push(p_rValue);
		m_valueType = VALUE_TYPE::FLOAT;
		m_value.rFloat = p_rValue;
	}
	inline void SetValue(double p_rValue)
	{
		//m_toolset.Push(p_rValue);
		m_valueType = VALUE_TYPE::DOUBLE;
		m_value.rDouble = p_rValue;
	}
	template<typename _LEFT, typename std::enable_if<std::is_integral<_LEFT>::value, int>::type = 0>
	inline void HandleConstantOperation(_LEFT p_left, VALUE_TYPE p_rightType, Value p_rightValue, uint32_t p_unOperator)
	{
		switch (p_rightType)
		{
		case VALUE_TYPE::INT_32:
			return SetValue(ConstantOperationIntegral(p_left, p_rightValue.nInt, p_unOperator));
		case VALUE_TYPE::INT_64:
			return SetValue(ConstantOperationIntegral(p_left, p_rightValue.llInt, p_unOperator));
		case VALUE_TYPE::FLOAT:
			return SetValue(ConstantOperationBasic(p_left, p_rightValue.rFloat, p_unOperator));
		case VALUE_TYPE::DOUBLE:
			return SetValue(ConstantOperationBasic(p_left, p_rightValue.rDouble, p_unOperator));
		case VALUE_TYPE::STRING:
		default:
			break;
		}
	}
	template<typename _LEFT, typename std::enable_if<std::is_floating_point<_LEFT>::value, int>::type = 0>
	inline void HandleConstantOperation(_LEFT p_left, VALUE_TYPE p_rightType, Value p_rightValue, uint32_t p_unOperator)
	{
		switch (p_rightType)
		{
		case VALUE_TYPE::INT_32:
			return SetValue(ConstantOperationBasic(p_left, p_rightValue.nInt, p_unOperator));
		case VALUE_TYPE::INT_64:
			return SetValue(ConstantOperationBasic(p_left, p_rightValue.llInt, p_unOperator));
		case VALUE_TYPE::FLOAT:
			return SetValue(ConstantOperationBasic(p_left, p_rightValue.rFloat, p_unOperator));
		case VALUE_TYPE::DOUBLE:
			return SetValue(ConstantOperationBasic(p_left, p_rightValue.rDouble, p_unOperator));
		case VALUE_TYPE::STRING:
		default:
			break;
		}
	}
	void HandleConstantOperation(VALUE_TYPE p_leftType, Value p_leftValue, VALUE_TYPE p_rightType, Value p_rightValue, uint32_t p_unOperator);
	void HandleNumber(const grammar::Report * p_pReport);
	template<typename _LAMBDA>
	inline void HandleValue(grammar::report_range p_reports, _LAMBDA && p_function)
	{
		//Push temporary size
		auto parameter = m_toolset.ReserveTemporyMembers();
		BiaTempCounter counter;

		//Handle value and prepare the result for a function call
		HandleValue(p_reports, counter);

		p_function();

		//Clean up
		auto max = counter.Max();

		if (max == 0)
			m_toolset.DiscardTemporaryMembers(parameter);
		else
			m_toolset.CommitTemporaryMembers(m_context, parameter, max);
	}
	void HandleOperator(VALUE_TYPE p_leftType, Value p_leftValue, VALUE_TYPE p_rightType, Value p_rightValue, uint32_t p_unOperator, BiaTempCounter & p_counter);
	template<uint32_t _RULE_ID, uint32_t _DEPTH, bool _LEFT>
	inline const grammar::Report * FindNextChild(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd)
	{
		if (_LEFT)
		{
			for (uint32_t unDepth = 0; p_pBegin < p_pEnd; ++p_pBegin)
			{
				if (p_pBegin->type == grammar::Report::TYPE::BEGIN)
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
				else if (p_pBegin->type == grammar::Report::TYPE::END)
					--unDepth;
			}
		}
		else
		{
			uint32_t unDepth = 0;

			while (p_pEnd-- > p_pBegin)
			{
				if (p_pEnd->type == grammar::Report::TYPE::END)
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
				else if (p_pEnd->type == grammar::Report::TYPE::BEGIN)
					--unDepth;
			}
		}

		return nullptr;
	}
	const grammar::Report * HandleRoot(const grammar::Report * p_pReport);
	const grammar::Report * HandleVariableDeclaration(grammar::report_range p_reports);
	const grammar::Report * HandleValue(grammar::report_range p_reports, BiaTempCounter & p_counter);
	const grammar::Report * HandleValueRaw(grammar::report_range p_reports);
	template<bool _START = true>
	inline const grammar::Report * HandleMathExpressionTerm(grammar::report_range p_reports, BiaTempCounter & p_counter)
	{
		constexpr auto NEXT = _START ? &BiaCompiler::HandleMathExpressionTerm<false> : &BiaCompiler::HandleMathFactor;

		//Only one math term to handle
		if (p_reports.pBegin[1].content.children.pEnd + 1 == p_reports.pEnd)
			(this->*NEXT)(p_reports.pBegin[1].content.children, p_counter);
		else
		{
			//Handle leftmost math term
			const grammar::Report * i = (this->*NEXT)(p_reports.pBegin[1].content.children, p_counter);
			auto leftType = m_valueType;
			auto leftValue = m_value;

			do
			{
				//Move string operator to int 32 bit value
				uint32_t unOperator = 0;

				memcpy(&unOperator, i->content.token.pcString, std::min(sizeof(unOperator), i->content.token.iSize));

				//Handle first right math term
				i = (this->*NEXT)(i[1].content.children, p_counter);

				//Call operator
				if (leftType == VALUE_TYPE::MEMBER || m_valueType == VALUE_TYPE::MEMBER)
				{
					//Handle operator
					HandleOperator(leftType, leftValue, m_valueType, m_value, unOperator, p_counter);
					
					leftType = VALUE_TYPE::MEMBER;
				}
				//Both operands can be optimized
				else
				{
					HandleConstantOperation(leftType, leftValue, m_valueType, m_value, unOperator);

					leftType = m_valueType;
					leftValue = m_value;
				}
			} while (i < p_reports.pEnd);
		}

		return p_reports.pEnd + 1;
	}
	const grammar::Report * HandleMathFactor(grammar::report_range p_reports, BiaTempCounter & p_counter);
	const grammar::Report * HandlePrint(grammar::report_range p_reports);
	const grammar::Report * HandleMember(grammar::report_range p_reports);
} ;

}
}