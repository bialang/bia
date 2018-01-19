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
		//Reserve temporary members
		m_parameter = m_toolset.ReserveTemporyMembers();
	}
	inline ~BiaCompiler()
	{
		//Clean up
		auto max = m_counter.Max();

		if (max == 0)
			m_toolset.DiscardTemporaryMembers(m_parameter);
		else
			m_toolset.CommitTemporaryMembers(m_context, m_parameter, max);
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
		TEMPORARY_MEMBER,
		TEST_VALUE_REGISTER,	/**	Defines that the test value is stored in the test register.	*/
		TEST_VALUE_CONSTANT,	/**	Defines that the test value is known at compile time.	*/
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
		BiaTempCounter::counter_type temporaryResultIndex;
		bool bTestValue;	/**	Defines the constant test value.	*/
	};

	machine::architecture::BiaToolset m_toolset;
	machine::BiaMachineContext & m_context;

	machine::architecture::BiaToolset::temp_members m_parameter;
	BiaTempCounter m_counter;

	VALUE_TYPE m_valueType;
	Value m_value;


	inline void SetValue(int32_t p_nValue)
	{
		m_valueType = VALUE_TYPE::INT_32;
		m_value.nInt = p_nValue;
	}
	inline void SetValue(int64_t p_llValue)
	{
		m_valueType = VALUE_TYPE::INT_64;
		m_value.llInt = p_llValue;
	}
	inline void SetValue(float p_rValue)
	{
		m_valueType = VALUE_TYPE::FLOAT;
		m_value.rFloat = p_rValue;
	}
	inline void SetValue(double p_rValue)
	{
		m_valueType = VALUE_TYPE::DOUBLE;
		m_value.rDouble = p_rValue;
	}
	template<typename _LEFT, typename std::enable_if<std::is_integral<_LEFT>::value, int>::type = 0>
	inline void HandleConstantOperation(_LEFT p_left, uint32_t p_unOperator)
	{
		switch (m_valueType)
		{
		case VALUE_TYPE::INT_32:
			return SetValue(ConstantOperationIntegral(p_left, m_value.nInt, p_unOperator));
		case VALUE_TYPE::INT_64:
			return SetValue(ConstantOperationIntegral(p_left, m_value.llInt, p_unOperator));
		case VALUE_TYPE::FLOAT:
			return SetValue(ConstantOperationBasic(p_left, m_value.rFloat, p_unOperator));
		case VALUE_TYPE::DOUBLE:
			return SetValue(ConstantOperationBasic(p_left, m_value.rDouble, p_unOperator));
		case VALUE_TYPE::STRING:
		default:
			break;
		}
	}
	template<typename _LEFT, typename std::enable_if<std::is_floating_point<_LEFT>::value, int>::type = 0>
	inline void HandleConstantOperation(_LEFT p_left, uint32_t p_unOperator)
	{
		switch (m_valueType)
		{
		case VALUE_TYPE::INT_32:
			return SetValue(ConstantOperationBasic(p_left, m_value.nInt, p_unOperator));
		case VALUE_TYPE::INT_64:
			return SetValue(ConstantOperationBasic(p_left, m_value.llInt, p_unOperator));
		case VALUE_TYPE::FLOAT:
			return SetValue(ConstantOperationBasic(p_left, m_value.rFloat, p_unOperator));
		case VALUE_TYPE::DOUBLE:
			return SetValue(ConstantOperationBasic(p_left, m_value.rDouble, p_unOperator));
		case VALUE_TYPE::STRING:
		default:
			break;
		}
	}
	void HandleConstantOperation(VALUE_TYPE p_leftType, Value p_leftValue, uint32_t p_unOperator);
	void HandleNumber(const grammar::Report * p_pReport);
	void HandleOperator(VALUE_TYPE p_leftType, Value p_leftValue, uint32_t p_unOperator, BiaTempCounter::counter_type p_destinationIndex);
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
	template<bool _IGNORE = false>
	const grammar::Report * HandleRoot(const grammar::Report * p_pReport)
	{
		//Don't compile these tokens, only return the end
		if (_IGNORE)
		{
			switch (p_pReport->unRuleId)
			{
			case grammar::BGR_ROOT_HELPER_0:
			{
				auto report = p_pReport->content.children;

				++report.pBegin;

				while (report.pBegin < report.pEnd)
					report.pBegin = HandleRoot<true>(report.pBegin);

				return report.pEnd + 1;
			}
			case grammar::BGR_VARIABLE_DECLARATION:
			case grammar::BGR_IF:
			case grammar::BGR_PRINT:
			case grammar::BGR_VALUE:
			case grammar::BGR_WHILE:
				return p_pReport->content.children.pEnd + 1;
			default:
				BIA_COMPILER_DEV_INVALID
			}
		}
		//Compile
		else
		{
			switch (p_pReport->unRuleId)
			{
			case grammar::BGR_ROOT_HELPER_0:
			{
				auto report = p_pReport->content.children;

				++report.pBegin;

				while (report.pBegin < report.pEnd)
					report.pBegin = HandleRoot(report.pBegin);

				return report.pEnd + 1;
			}
			case grammar::BGR_VARIABLE_DECLARATION:
				return HandleVariableDeclaration(p_pReport->content.children);
			case grammar::BGR_IF:
				return HandleIf(p_pReport->content.children);
			case grammar::BGR_PRINT:
			case grammar::BGR_VALUE:
				return HandlePrint(p_pReport->content.children);
			case grammar::BGR_WHILE:
				return HandlePreTestLoop(p_pReport->content.children);
			default:
				BIA_COMPILER_DEV_INVALID
			}
		}
	}
	const grammar::Report * HandleVariableDeclaration(grammar::report_range p_reports);
	/**
	 * Handles the value and calls the given function.
	 *
	 * @remarks	If _TEST is set true the value will be tested. This guarantees a test value result.
	 *
	 * @since	3.48.104.629
	 * @date	14-Jan-18
	 *
	 * @param	p_reports	Defines the reports.
	 * @param	[in]	p_callback	Defines the to be called function.
	 *
	 * @return	The end of this token.
	*/
	template<bool _TEST, typename _LAMBDA>
	inline const grammar::Report * HandleValue(grammar::report_range p_reports, _LAMBDA && p_callback)
	{
		//Handle value
		HandleValue(p_reports);
		
		//Test
		if (_TEST)
		{
			switch (m_valueType)
			{
			case VALUE_TYPE::INT_32:
			case VALUE_TYPE::FLOAT:
				m_valueType = VALUE_TYPE::TEST_VALUE_CONSTANT;
				m_value.bTestValue = m_value.nInt ? true : false;

				break;
			case VALUE_TYPE::INT_64:
			case VALUE_TYPE::DOUBLE:
				m_valueType = VALUE_TYPE::TEST_VALUE_CONSTANT;
				m_value.bTestValue = m_value.llInt ? true : false;

				break;
			case VALUE_TYPE::MEMBER:
				m_valueType = VALUE_TYPE::TEST_VALUE_REGISTER;
				m_toolset.SafeCall(&framework::BiaMember::Test, m_value.pMember);
				m_toolset.WriteTest();

				break;
			case VALUE_TYPE::TEMPORARY_MEMBER:
				m_valueType = VALUE_TYPE::TEST_VALUE_REGISTER;
				m_toolset.Call(&framework::BiaMember::Test, machine::architecture::BiaToolset::TemporaryMember(m_value.temporaryResultIndex));
				m_toolset.WriteTest();

				break;
			case VALUE_TYPE::TEST_VALUE_REGISTER:
			case VALUE_TYPE::TEST_VALUE_CONSTANT:
				break;
			default:
				BIA_COMPILER_DEV_INVALID
			}
		}

		//Execute function
		p_callback();
		
		//Pop value
		m_counter.Pop();
		
		return p_reports.pEnd + 1;
	}
	const grammar::Report * HandleValue(grammar::report_range p_reports);
	const grammar::Report * HandleValueRaw(grammar::report_range p_reports);
	template<bool _START = true>
	inline const grammar::Report * HandleMathExpressionTerm(grammar::report_range p_reports)
	{
		constexpr auto NEXT = _START ? &BiaCompiler::HandleMathExpressionTerm<false> : &BiaCompiler::HandleMathFactor;

		//Only one math term to handle
		if (p_reports.pBegin[1].content.children.pEnd + 1 == p_reports.pEnd)
			(this->*NEXT)(p_reports.pBegin[1].content.children);
		else
		{
			//Handle leftmost math term
			auto currentCounter = m_counter.Next();
			const grammar::Report * i = (this->*NEXT)(p_reports.pBegin[1].content.children);
			auto leftType = m_valueType;
			auto leftValue = m_value;

			do
			{
				//Move string operator to int 32 bit value
				uint32_t unOperator = 0;

				memcpy(&unOperator, i->content.token.pcString, std::min(sizeof(unOperator), i->content.token.iSize));

				//Handle first right math term
				i = (this->*NEXT)(i[1].content.children);

				//Call operator
				if (leftType == VALUE_TYPE::MEMBER || leftType == VALUE_TYPE::TEMPORARY_MEMBER || 
					m_valueType == VALUE_TYPE::MEMBER || m_valueType == VALUE_TYPE::TEMPORARY_MEMBER)
					HandleOperator(leftType, leftValue, unOperator, currentCounter);
				//Both operands can be optimized
				else
					HandleConstantOperation(leftType, leftValue, unOperator);

				leftType = m_valueType;
				leftValue = m_value;
				
				//Pop back
				m_counter.Pop(currentCounter);
			} while (i < p_reports.pEnd);
		}

		return p_reports.pEnd + 1;
	}
	const grammar::Report * HandleMathFactor(grammar::report_range p_reports);
	const grammar::Report * HandleIf(grammar::report_range p_reports);
	const grammar::Report * HandlePrint(grammar::report_range p_reports);
	const grammar::Report * HandleMember(grammar::report_range p_reports);
	const grammar::Report * HandlePreTestLoop(grammar::report_range p_reports);
	const grammar::Report * HandlePostTestLoop(grammar::report_range p_reports, machine::architecture::BiaToolset::position * p_pConditionPosition);
} ;

}
}