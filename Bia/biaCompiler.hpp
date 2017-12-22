#pragma once

#include <cstdint>
#include <cstring>
#include <algorithm>

#include "biaOutputStream.hpp"
#include "biaMachineContext.hpp"
#include "biaReportBundle.hpp"
#include "biaInterpreterIdentifiers.hpp"
#include "biaLink.hpp"
#include "biaToolset.hpp"

#define BIA_COMPILER_DEV_INVALID throw BIA_IMPLEMENTATION_EXCEPTION("Invalid case.");


namespace bia
{
namespace compiler
{

class BiaCompiler final : public grammar::BiaReportReceiver
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
		NONE,
	};

	union Value
	{
		int32_t nInt;
		int64_t llInt;
		float rFloat;
		double rDouble;
		size_t iString;
	};

	machine::architecture::BiaToolset m_toolset;

	machine::BiaMachineContext & m_context;

	VALUE_TYPE m_valueType;
	Value m_value;


	inline void HandleNumber(const grammar::Report * p_pReport)
	{
		switch (p_pReport->unCustomParameter)
		{
		case grammar::NI_INTEGER:
		{
			if (p_pReport->content.token.iSize <= 70)
			{
				char acTmp[70];

				memcpy(acTmp, p_pReport->content.token.pcString, p_pReport->content.token.iSize);
				acTmp[p_pReport->content.token.iSize] = 0;

				//Interpret
				char * pcEnd = nullptr;
				m_value.llInt = std::strtoll(acTmp, &pcEnd, 10);

				if (acTmp == pcEnd)
					throw exception::ArgumentException("Invalid number.");
			}
			else
				throw exception::ArgumentException("Too long number.");

			//64-Bit number
			if (m_value.llInt & 0xffffffff00000000ull)
			{
				m_toolset.Push(m_value.llInt);

				m_valueType = VALUE_TYPE::INT_64;
			}
			//32-Bit number
			else
			{
				m_toolset.Push(m_value.nInt);

				m_valueType = VALUE_TYPE::INT_32;
			}

			break;
		}
		case grammar::NI_FLOAT:
		{
			if (p_pReport->content.token.iSize < 128)
			{
				char acTmp[129];

				memcpy(acTmp, p_pReport->content.token.pcString, p_pReport->content.token.iSize);
				acTmp[p_pReport->content.token.iSize] = 0;

				//Interpret
				char * pcEnd = nullptr;
				m_value.rFloat = strtof(acTmp, &pcEnd);

				if (acTmp == pcEnd)
					throw exception::ArgumentException("Invalid number.");
			}
			else
				throw exception::ArgumentException("Too long number.");

			m_toolset.Push(m_value.rFloat);

			m_valueType = VALUE_TYPE::FLOAT;

			break;
		}
		case grammar::NI_DOUBLE:
		{
			if (p_pReport->content.token.iSize < 128)
			{
				char acTmp[129];

				memcpy(acTmp, p_pReport->content.token.pcString, p_pReport->content.token.iSize);
				acTmp[p_pReport->content.token.iSize] = 0;

				//Interpret
				char * pcEnd = nullptr;
				m_value.rDouble = strtod(acTmp, &pcEnd);

				if (acTmp == pcEnd)
					throw exception::ArgumentException("Invalid number.");
			}
			else
				throw exception::ArgumentException("Too long number.");

			m_toolset.Push(m_value.rDouble);

			m_valueType = VALUE_TYPE::DOUBLE;

			break;
		}
		default:
			BIA_COMPILER_DEV_INVALID
		}
	}
	inline void HandleConstantOperation(VALUE_TYPE p_leftType, Value p_leftValue, VALUE_TYPE p_rightType, Value p_rightValue, uint32_t p_unOperator)
	{
		m_toolset.Push(p_leftValue.nInt);
	}
	inline static const void * GetOperatorFunction_xM(VALUE_TYPE p_right)
	{

	}
	inline const void * HandleOperator(VALUE_TYPE p_left, VALUE_TYPE p_right, uint32_t p_unOperator)
	{
		switch (p_unOperator)
		{
		default:
			m_toolset.Push(p_unOperator);

			return static_cast<const void*>(&machine::link::Operator_MM);
		}
	}
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
	inline const grammar::Report * HandleRoot(const grammar::Report * p_pReport)
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
			//return HandleIf(p_pReport->content.children);
		default:
			BIA_COMPILER_DEV_INVALID
		}
	}
	inline const grammar::Report * HandleVariableDeclaration(grammar::report_range p_reports)
	{
		//PrintStraight("vd>", p_reports);

		//Handle value
		auto pRight = FindNextChild<grammar::BGR_VALUE, 0, true>(p_reports.pBegin + 2, p_reports.pEnd);

		m_valueType = VALUE_TYPE::NONE;

		//Push address of variable
		m_toolset.Push(reinterpret_cast<uintptr_t>(m_context.AddressOf(machine::BiaMachineContext::StringKey(p_reports.pBegin[1].content.token.pcString, p_reports.pBegin[1].content.token.iSize))));

		//Handle value and prepare the result for a function call
		HandleValue(pRight->content.children);

		//Make call
		switch (m_valueType)
		{
		case VALUE_TYPE::INT_32:
			m_toolset.Call(reinterpret_cast<const void*>(&machine::link::InstantiateInt_32));

			break;
		case VALUE_TYPE::INT_64:
			m_toolset.Call(reinterpret_cast<const void*>(&machine::link::InstantiateInt_64));

			break;
		case VALUE_TYPE::FLOAT:
			m_toolset.Call(reinterpret_cast<const void*>(&machine::link::InstantiateFloat));

			break;
		case VALUE_TYPE::DOUBLE:
			m_toolset.Call(reinterpret_cast<const void*>(&machine::link::InstantiateDouble));

			break;
		default:
			BIA_COMPILER_DEV_INVALID
		}

		return p_reports.pEnd + 1;
	}
	inline const grammar::Report * HandleValue(grammar::report_range p_reports)
	{
		//PrintStraight("vv>", p_reports);
		
		//Handle first expression
		p_reports.pBegin = HandleMathExpressionTerm(p_reports.pBegin[1].content.children);

		//Logical operators were used
		/*if (p_reports.pBegin < p_reports.pEnd)
		{
			BiaConditionMakerDouble maker(m_output);
			STATE state = S_NONE;

			do
			{
				//Logical operator
				switch (p_reports.pBegin->unTokenId)
				{
				case grammar::BVO_LOGICAL_AND:
				{
					constexpr uint64_t cullNull = 0;

					WriteConstant(machine::OP::JUMP_CONDITIONAL_NOT, cullNull);

					maker.MarkPlaceholder(BiaConditionMakerDouble::L_NEXT_1);

					//Mark last next
					if (state == S_NEXT_0)
						maker.MarkLocation(BiaConditionMakerDouble::L_NEXT_0);

					state = S_NEXT_1;

					break;
				}
				case grammar::BVO_LOGICAL_OR:
				{
					constexpr uint64_t cullNull = 0;

					WriteConstant(machine::OP::JUMP_CONDITIONAL, cullNull);

					maker.MarkPlaceholder(BiaConditionMakerDouble::L_NEXT_0);

					//Mark last next
					if (state == S_NEXT_1)
						maker.MarkLocation(BiaConditionMakerDouble::L_NEXT_1);

					state = S_NEXT_0;

					break;
				}
				default:
					BIA_COMPILER_DEV_INVALID
				}

				//Handle right value
				p_reports.pBegin = HandleMathExpression(p_reports.pBegin[1].content.children, false);
			} while (p_reports.pBegin < p_reports.pEnd);

			//Mark last next
			switch (state)
			{
			case S_NEXT_0:
				maker.MarkLocation(BiaConditionMakerDouble::L_NEXT_0);

				break;
			case S_NEXT_1:
				maker.MarkLocation(BiaConditionMakerDouble::L_NEXT_1);

				break;
			default:
				break;
			}
		}*/

		return p_reports.pEnd + 1;
	}
	inline const grammar::Report * HandleValueRaw(grammar::report_range p_reports)
	{
		switch (p_reports.pBegin[1].unTokenId)
		{
		case grammar::BV_NUMBER:
			HandleNumber(p_reports.pBegin + 1);

			break;
		case grammar::BV_TRUE:
			m_toolset.Push<uint8_t>(1);

			m_valueType = VALUE_TYPE::INT_32;

			break;
		case grammar::BV_FALSE:
		case grammar::BV_NULL:
			m_toolset.Push<uint8_t>(0);

			m_valueType = VALUE_TYPE::INT_32;

			break;
		case grammar::BV_MEMBER:
			//HandleMember(p_reports.pBegin[1].content.children, p_bPush);

			//break;
		default:
			BIA_COMPILER_DEV_INVALID
		}

		return p_reports.pEnd + 1;
	}
	template<bool _START = true>
	inline const grammar::Report * HandleMathExpressionTerm(grammar::report_range p_reports)
	{
		constexpr auto NEXT = _START ? HandleMathExpressionTerm<false> : HandleMathFactor;

		//Only one math term to handle
		if (p_reports.pBegin[1].content.children.pEnd + 1 == p_reports.pEnd)
			NEXT(p_reports.pBegin[1].content.children);
		else
		{
			m_toolset.MarkLocation();

			//Handle leftmost math term
			const grammar::Report * i = NEXT(p_reports.pBegin[1].content.children);
			auto leftType = m_valueType;
			auto leftValue = m_value;

			do
			{
				//Move string operator to int 32 bit value
				uint32_t unOperator = 0;

				memcpy(&unOperator, i->content.token.pcString, std::min(sizeof(unOperator), i->content.token.iSize));

				//Handle first right math term
				i = NEXT(i[1].content.children);

				//Call operator
				if (leftType == VALUE_TYPE::MEMBER || m_valueType == VALUE_TYPE::MEMBER)
				{
					m_toolset.Call<false>(HandleOperator(leftType, m_valueType, unOperator));
					m_toolset.PushResult();
					m_toolset.PopPoint();

					leftType = VALUE_TYPE::MEMBER;
				}
				//Both operands can be optimized
				else
				{
					m_toolset.RestoreLocation();

					HandleConstantOperation(leftType, leftValue, m_valueType, m_value, unOperator);

					leftType = m_valueType;
					leftValue = m_value;
				}
			} while (i < p_reports.pEnd);
		}

		return p_reports.pEnd + 1;
	}
	inline const grammar::Report * HandleMathFactor(grammar::report_range p_reports)
	{
		switch (p_reports.pBegin[1].unRuleId)
		{
		case grammar::BGR_VALUE_RAW:
			HandleValueRaw(p_reports.pBegin[1].content.children);

			break;
		case grammar::BGR_VALUE:
			HandleValue(p_reports.pBegin[1].content.children);

			break;
		default:
			BIA_COMPILER_DEV_INVALID
		}

		return p_reports.pEnd + 1;
	}
} ;

}
}