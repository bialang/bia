#pragma once

#include <cstdint>

#include "biaOutputStream.hpp"
#include "biaMachineContext.hpp"
#include "biaReportBundle.hpp"
#include "biaInterpreterIdentifiers.hpp"
#include "biaLink.hpp"

#define BIA_COMPILER_DEV_INVALID throw BIA_IMPLEMENTATION_EXCEPTION("Invalid case.");


namespace bia
{
namespace compiler
{

template<typename _TOOLSET>
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
		NONE,
		MEMBER,
		INT_32,
		INT_64,
		FLOAT,
		DOUBLE,
		STRING
	};

	_TOOLSET m_toolset;

	machine::BiaMachineContext & m_context;

	VALUE_TYPE m_valueType;


	inline void HandleNumber(const grammar::Report * p_pReport)
	{
		switch (p_pReport->unCustomParameter)
		{
		case grammar::NI_INTEGER:
		{
			auto llTmp = 0ll;

			if (p_pReport->content.token.iSize <= 70)
			{
				char acTmp[70];

				memcpy(acTmp, p_pReport->content.token.pcString, p_pReport->content.token.iSize);
				acTmp[p_pReport->content.token.iSize] = 0;

				//Interpret
				char * pcEnd = nullptr;
				llTmp = std::strtoll(acTmp, &pcEnd, 10);

				if (acTmp == pcEnd)
					throw exception::ArgumentException("Invalid number.");
			}
			else
				throw exception::ArgumentException("Too long number.");

			//64-Bit number
			if (llTmp & 0xffffffff00000000ull)
			{
				m_toolset.PushParameter(static_cast<uint64_t>(llTmp));

				m_valueType = VALUE_TYPE::INT_64;
			}
			//32-Bit number
			else
			{
				m_toolset.PushParameter(static_cast<uint32_t>(llTmp));

				m_valueType = VALUE_TYPE::INT_32;
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

			m_toolset.PushParameter(*reinterpret_cast<uint32_t*>(&rTmp));

			m_valueType = VALUE_TYPE::FLOAT;

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

			m_toolset.PushParameter(*reinterpret_cast<uint64_t*>(&rTmp));

			m_valueType = VALUE_TYPE::DOUBLE;

			break;
		}
		default:
			BIA_COMPILER_DEV_INVALID
		}
	}
	/**
	 * Retruns the amount of 4 byte pairs for the specified value type.
	 *
	 * @since	3.42.93.570
	 * @date	20-Dec-17
	 *
	 * @param	p_type	Defines the value type.
	 *
	 * @return	Either 1 or 2.
	*/
	inline static uint8_t ParameterElements(VALUE_TYPE p_type)
	{
		switch (p_type)
		{
		case VALUE_TYPE::MEMBER:
		case VALUE_TYPE::STRING:
			static_assert(sizeof(void*) % 4 == 0, "Pointer size must be a multiple of 4.");

			return sizeof(void*) / 4;
		case VALUE_TYPE::INT_32:
		case VALUE_TYPE::FLOAT:
			return 1;
		case VALUE_TYPE::INT_64:
		case VALUE_TYPE::DOUBLE:
			return 2;
		default:
			BIA_COMPILER_DEV_INVALID
		}
	}
	inline const void * HandleOperator(VALUE_TYPE p_left, VALUE_TYPE p_right, const grammar::Report * p_pOperator)
	{
		printf("your operator: ");
		fwrite(p_pOperator->content.token.pcString, p_pOperator->content.token.iSize, 1, stdout);
		puts("");

		return static_cast<const void*>(&machine::link::testt);
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
		m_toolset.PushParameter(reinterpret_cast<uintptr_t>(m_context.AddressOf(machine::BiaMachineContext::StringKey(p_reports.pBegin[1].content.token.pcString, p_reports.pBegin[1].content.token.iSize))));

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
		p_reports.pBegin = HandleMathExpression(p_reports.pBegin[1].content.children);

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
			m_toolset.PushParameter(uint8_t(1));

			m_valueType = VALUE_TYPE::INT_32;

			break;
		case grammar::BV_FALSE:
		case grammar::BV_NULL:
			m_toolset.PushParameter(uint8_t(0));

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
	inline const grammar::Report * HandleMathExpression(grammar::report_range p_reports)
	{
		//Only one math term to handle
		if (p_reports.pBegin[1].content.children.pEnd + 1 == p_reports.pEnd)
			HandleMathTerm(p_reports.pBegin[1].content.children);
		else
		{
			auto left = VALUE_TYPE::NONE;

			//Handle leftmost math term
			auto i = HandleMathTerm(p_reports.pBegin[1].content.children);

			left = m_valueType;

			do
			{
				auto pOperator = i;

				//Handle first right math term
				i = HandleMathTerm(i[1].content.children);

				//Call operator
				auto ucPopElements = ParameterElements(left) + ParameterElements(m_valueType);

				m_toolset.Call<false>(HandleOperator(left, m_valueType, pOperator));
				m_toolset.PopParameters(ucPopElements);

				left = m_valueType;

				//Push result
				if (ParameterElements(m_valueType) == 1)
					m_toolset.PushResult32();
				else
					m_toolset.PushResult64();
			} while (i < p_reports.pEnd);
		}

		return p_reports.pEnd + 1;
	}
	inline const grammar::Report * HandleMathTerm(grammar::report_range p_reports)
	{
		//Only one math factor to handle
		if (p_reports.pBegin[1].content.children.pEnd + 1 == p_reports.pEnd)
			HandleMathFactor(p_reports.pBegin[1].content.children);
		//Call all operator and load the leftmost object
		else
		{
			auto left = VALUE_TYPE::NONE;

			//Handle leftmost math factor
			auto i = HandleMathFactor(p_reports.pBegin[1].content.children);

			left = m_valueType;

			do
			{
				auto pOperator = i;

				//Handle first right math factor
				i = HandleMathFactor(i[1].content.children);

				//Call operator
				auto ucPopElements = ParameterElements(left) + ParameterElements(m_valueType);
				
				m_toolset.Call<false>(HandleOperator(left, m_valueType, pOperator));
				m_toolset.PopParameters(ucPopElements);

				left = m_valueType;

				//Push result
				if (ParameterElements(m_valueType) == 1)
					m_toolset.PushResult32();
				else
					m_toolset.PushResult64();
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