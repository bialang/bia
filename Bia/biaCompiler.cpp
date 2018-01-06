#include "biaCompiler.hpp"
#include "biaException.hpp"

#define BIA_COMPILER_DEV_INVALID throw BIA_IMPLEMENTATION_EXCEPTION("Invalid case.");


namespace bia
{
namespace compiler
{

void BiaCompiler::HandleConstantOperation(VALUE_TYPE p_leftType, Value p_leftValue, VALUE_TYPE p_rightType, Value p_rightValue, uint32_t p_unOperator)
{
	using namespace framework;

	switch (p_leftType)
	{
	case VALUE_TYPE::INT_32:
		return HandleConstantOperation(p_leftValue.nInt, p_rightType, p_rightValue, p_unOperator);
	case VALUE_TYPE::INT_64:
		return HandleConstantOperation(p_leftValue.llInt, p_rightType, p_rightValue, p_unOperator);
	case VALUE_TYPE::FLOAT:
		return HandleConstantOperation(p_leftValue.rFloat, p_rightType, p_rightValue, p_unOperator);
	case VALUE_TYPE::DOUBLE:
		return HandleConstantOperation(p_leftValue.rDouble, p_rightType, p_rightValue, p_unOperator);
	case VALUE_TYPE::STRING:
	default:
		BIA_COMPILER_DEV_INVALID
	}
}

void BiaCompiler::HandleNumber(const grammar::Report * p_pReport)
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
				throw exception::NumberException("Invalid number.");
		}
		else
			throw exception::NumberException("Too long number.");

		//64-Bit number
		if(m_value.llInt < 0xffffffff80000000ll || m_value.llInt > 0x7fffffffll)
			m_valueType = VALUE_TYPE::INT_64;
		//32-Bit number
		else
		{
			m_value.nInt = static_cast<int32_t>(m_value.llInt);
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
				throw exception::NumberException("Invalid number.");
		}
		else
			throw exception::NumberException("Too long number.");

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
				throw exception::NumberException("Invalid number.");
		}
		else
			throw exception::NumberException("Too long number.");

		m_valueType = VALUE_TYPE::DOUBLE;

		break;
	}
	default:
		BIA_COMPILER_DEV_INVALID
	}
}

void BiaCompiler::HandleOperator(VALUE_TYPE p_leftType, Value p_leftValue, VALUE_TYPE p_rightType, Value p_rightValue, uint32_t p_unOperator, BiaTempCounter & p_counter)
{
	using namespace machine::architecture;

	switch (p_leftType)
	{
	case VALUE_TYPE::MEMBER:
	{
		switch (p_rightType)
		{
		case VALUE_TYPE::INT_32:
			m_toolset.Call(&framework::BiaMember::OperatorCallInt_32, p_leftValue.pMember, p_unOperator, p_rightValue.nInt, BiaToolset::TemporaryMember(p_counter.Current()));

			break;
		case bia::compiler::BiaCompiler::VALUE_TYPE::INT_64:
			break;
		case bia::compiler::BiaCompiler::VALUE_TYPE::FLOAT:
			break;
		case bia::compiler::BiaCompiler::VALUE_TYPE::DOUBLE:
			break;
		case VALUE_TYPE::MEMBER:
			m_toolset.Call(&framework::BiaMember::OperatorCall, p_leftValue.pMember, p_unOperator, p_rightValue.pMember, BiaToolset::TemporaryMember(p_counter.Current()));

			break;
		default:
			BIA_COMPILER_DEV_INVALID
		}

		break;
	}
	case VALUE_TYPE::TEMPORARY_MEMBER:
	{
		switch (p_rightType)
		{
		case VALUE_TYPE::INT_32:
			m_toolset.Call(&framework::BiaMember::OperatorAssignCallInt_32, BiaToolset::TemporaryMember(p_counter.Current()), p_unOperator, p_rightValue.nInt);

			break;
		case VALUE_TYPE::MEMBER:
			m_toolset.Call(&framework::BiaMember::OperatorAssignCall, BiaToolset::TemporaryMember(p_counter.Current()), p_unOperator, p_rightValue.pMember);

			break;
		case VALUE_TYPE::TEMPORARY_MEMBER:
			m_toolset.Call(&framework::BiaMember::OperatorAssignCall, BiaToolset::TemporaryMember(p_counter.Current()), p_unOperator, BiaToolset::TemporaryMember(p_rightValue.temporaryResultIndex));

			break;
		default:
			BIA_COMPILER_DEV_INVALID
		}

		break;
	}
	default:
		BIA_COMPILER_DEV_INVALID
	}
	//switch (p_unOperator)
	//{
	//default:
	//	//m_toolset.Push(p_unOperator);

	//	m_valueType = VALUE_TYPE::MEMBER;

	//	
	//	m_toolset.Call(m_scpOperatorFunctions[0][static_cast<int>(p_left) + (static_cast<int>(p_right) + 1) % (static_cast<int>(VALUE_TYPE::MEMBER) + 1)], )
	//}
}

const grammar::Report * BiaCompiler::HandleRoot(const grammar::Report * p_pReport)
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
	//case grammar::BGR_IF:
		//return HandleIf(p_pReport->content.children);
	case grammar::BGR_PRINT:
	case grammar::BGR_VALUE:
		return HandlePrint(p_pReport->content.children);
	default:
		BIA_COMPILER_DEV_INVALID
	}
}

const grammar::Report * BiaCompiler::HandleVariableDeclaration(grammar::report_range p_reports)
{
	//Handle value and prepare the result for a function call
	HandleValue(FindNextChild<grammar::BGR_VALUE, 0, true>(p_reports.pBegin + 2, p_reports.pEnd)->content.children, [&] {
		//Get address of variable
		auto pVariable = m_context.AddressOf(machine::StringKey(p_reports.pBegin[1].content.token.pcString, p_reports.pBegin[1].content.token.iSize));

		//Make call
		switch (m_valueType)
		{
		case VALUE_TYPE::INT_32:
		{
			//Optimize common used constant values
			switch (m_value.nInt)
			{
			case 0:
				m_toolset.SafeCall(&machine::link::InstantiateInt0, pVariable);

				break;
			case 1:
				m_toolset.SafeCall(&machine::link::InstantiateIntP1, pVariable);

				break;
			case -1:
				m_toolset.SafeCall(&machine::link::InstantiateIntN1, pVariable);

				break;
			default:
				m_toolset.SafeCall(&machine::link::InstantiateInt_32, pVariable, m_value.nInt);

				break;
			}

			break;
		}
		case VALUE_TYPE::INT_64:
			m_toolset.SafeCall(&machine::link::InstantiateInt_64, pVariable, m_value.llInt);

			break;
		case VALUE_TYPE::FLOAT:
			m_toolset.SafeCall(&machine::link::InstantiateFloat, pVariable, m_value.rFloat);

			break;
		case VALUE_TYPE::DOUBLE:
			m_toolset.SafeCall(&machine::link::InstantiateDouble, pVariable, m_value.rDouble);

			break;
		case VALUE_TYPE::MEMBER:
			m_toolset.SafeCall(&machine::link::InstantiateCopy, pVariable, m_value.pMember);

			break;
		default:
			BIA_COMPILER_DEV_INVALID
		}
	});

	return p_reports.pEnd + 1;
}

const grammar::Report * BiaCompiler::HandleValue(grammar::report_range p_reports, BiaTempCounter & p_counter)
{
	puts("value call");
	

	//Handle first expression
	p_reports.pBegin = HandleMathExpressionTerm(p_reports.pBegin[1].content.children, p_counter);

	//
	

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

const grammar::Report * BiaCompiler::HandleValueRaw(grammar::report_range p_reports)
{
	switch (p_reports.pBegin[1].unTokenId)
	{
	case grammar::BV_NUMBER:
		HandleNumber(p_reports.pBegin + 1);

		break;
	case grammar::BV_TRUE:
		m_value.nInt = 1;
		m_valueType = VALUE_TYPE::INT_32;

		break;
	case grammar::BV_FALSE:
	case grammar::BV_NULL:
		m_value.nInt = 0;
		m_valueType = VALUE_TYPE::INT_32;

		break;
	case grammar::BV_MEMBER:
		HandleMember(p_reports.pBegin[1].content.children);

		break;
	default:
		BIA_COMPILER_DEV_INVALID
	}

	return p_reports.pEnd + 1;
}

const grammar::Report * BiaCompiler::HandleMathFactor(grammar::report_range p_reports, BiaTempCounter & p_counter)
{
	switch (p_reports.pBegin[1].unRuleId)
	{
	case grammar::BGR_VALUE_RAW:
		HandleValueRaw(p_reports.pBegin[1].content.children);

		break;
	case grammar::BGR_VALUE:
		HandleValue(p_reports.pBegin[1].content.children, p_counter);

		break;
	default:
		BIA_COMPILER_DEV_INVALID
	}

	return p_reports.pEnd + 1;
}

const grammar::Report * bia::compiler::BiaCompiler::HandlePrint(grammar::report_range p_reports)
{
	//Handle value to print
	HandleValue(p_reports, [this] {
		switch (m_valueType)
		{
		case VALUE_TYPE::INT_32:
			m_toolset.SafeCall(&machine::link::Print_i, m_value.nInt);

			break;
		case VALUE_TYPE::INT_64:
			m_toolset.SafeCall(&machine::link::Print_I, m_value.llInt);

			break;
		case VALUE_TYPE::FLOAT:
			m_toolset.SafeCall(&machine::link::Print_f, m_value.rFloat);

			break;
		case VALUE_TYPE::DOUBLE:
			m_toolset.SafeCall(&machine::link::Print_d, m_value.rDouble);

			break;
		case VALUE_TYPE::MEMBER:
			m_toolset.SafeCall(&machine::link::Print_M, m_value.pMember);

			break;
		case VALUE_TYPE::TEMPORARY_MEMBER:
			m_toolset.Call<true>(&machine::link::Print_M, machine::architecture::BiaToolset::TemporaryMember(m_value.temporaryResultIndex));

			break;
		default:
			BIA_COMPILER_DEV_INVALID
		}
	});

	return p_reports.pEnd + 1;
}

const grammar::Report * BiaCompiler::HandleMember(grammar::report_range p_reports)
{
	switch (p_reports.pBegin[1].unTokenId)
	{
	/*case grammar::BM_INSTANTIATION:
		HandleInstantiation(p_reports.pBegin->content.children, p_bPush);

		break;
	case grammar::BM_STRING:
		HandleString(p_reports.pBegin, p_bPush);

		break;*/
	case grammar::BM_IDENTIFIER:
		m_value.pMember = m_context.AddressOf(machine::StringKey(p_reports.pBegin[1].content.token.pcString, p_reports.pBegin[1].content.token.iSize));
		m_valueType = VALUE_TYPE::MEMBER;

		break;
	default:
		BIA_COMPILER_DEV_INVALID
	}

	return p_reports.pEnd + 1;
}

}
}