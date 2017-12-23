#include "biaCompiler.hpp"
#include "biaException.hpp"

#define BIA_COMPILER_DEV_INVALID throw BIA_IMPLEMENTATION_EXCEPTION("Invalid case.");


namespace bia
{
namespace compiler
{

const void * const BiaCompiler::m_scpOperatorFunctions[][11] = {
	{ 
		&machine::link::Operator_iM, 
		&machine::link::Operator_IM, 
		&machine::link::Operator_fM, 
		&machine::link::Operator_dM, 
		&machine::link::Operator_sM, 
		&machine::link::Operator_MM, 
		&machine::link::Operator_Mi, 
		&machine::link::Operator_MI, 
		&machine::link::Operator_Mf, 
		&machine::link::Operator_Md, 
		&machine::link::Operator_Ms 
	}
};

void BiaCompiler::HandleConstantOperation(VALUE_TYPE p_leftType, Value p_leftValue, VALUE_TYPE p_rightType, Value p_rightValue, uint32_t p_unOperator)
{
	using namespace api::framework;

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
		break;
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

const void * BiaCompiler::HandleOperator(VALUE_TYPE p_left, VALUE_TYPE p_right, uint32_t p_unOperator)
{
	switch (p_unOperator)
	{
	default:
		m_toolset.Push(p_unOperator);

		m_valueType = VALUE_TYPE::MEMBER;

		return m_scpOperatorFunctions[0][static_cast<int>(p_left) + (static_cast<int>(p_right) + 1) % (static_cast<int>(VALUE_TYPE::MEMBER) + 1)];
	}
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

const grammar::Report * BiaCompiler::HandleValue(grammar::report_range p_reports)
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

const grammar::Report * BiaCompiler::HandleValueRaw(grammar::report_range p_reports)
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
		HandleMember(p_reports.pBegin[1].content.children);

		break;
	default:
		BIA_COMPILER_DEV_INVALID
	}

	return p_reports.pEnd + 1;
}

const grammar::Report * BiaCompiler::HandleMathFactor(grammar::report_range p_reports)
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

const grammar::Report * bia::compiler::BiaCompiler::HandlePrint(grammar::report_range p_reports)
{
	auto ucStart = m_toolset.GetPushedElements();

	//Handle value to print
	HandleValue(p_reports);

	switch (m_valueType)
	{
	case VALUE_TYPE::INT_32:
		m_toolset.Call(reinterpret_cast<const void*>(&machine::link::Print_i));

		break;
	case VALUE_TYPE::INT_64:
		m_toolset.Call(reinterpret_cast<const void*>(&machine::link::Print_I));

		break;
	case VALUE_TYPE::FLOAT:
		m_toolset.Call(reinterpret_cast<const void*>(&machine::link::Print_f));

		break;
	case VALUE_TYPE::DOUBLE:
		m_toolset.Call(reinterpret_cast<const void*>(&machine::link::Print_d));

		break;
	case VALUE_TYPE::MEMBER:
		m_toolset.Call(reinterpret_cast<const void*>(&machine::link::Print_M));

		break;
	default:
		BIA_COMPILER_DEV_INVALID
	}

	//Pop
	m_toolset.Pop(m_toolset.GetPushedElements() - ucStart);

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
		m_toolset.Push(reinterpret_cast<uintptr_t>(m_context.AddressOf(machine::BiaMachineContext::StringKey(p_reports.pBegin[1].content.token.pcString, p_reports.pBegin[1].content.token.iSize))));

		m_valueType = VALUE_TYPE::MEMBER;

		break;
	default:
		BIA_COMPILER_DEV_INVALID
	}

	return p_reports.pEnd + 1;
}

}
}