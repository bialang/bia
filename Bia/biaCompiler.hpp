#pragma once

#include <cstdint>
#include <cstring>
#include <algorithm>
#include <type_traits>

#include "biaOutputStream.hpp"
#include "biaMachineContext.hpp"
#include "biaMachineSchein.hpp"
#include "biaAllocator.hpp"
#include "biaReportBundle.hpp"
#include "biaInterpreterIdentifiers.hpp"
#include "biaLink.hpp"
#include "biaToolset.hpp"
#include "biaConstantOperation.hpp"
#include "biaException.hpp"
#include "biaTempCounter.hpp"
#include "biaLocalVariableHandler.hpp"

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
	 * @param	[in]	p_pAllocator	Defines the memory allocator.
	 */
	BiaCompiler(stream::BiaOutputStream & p_output, machine::BiaMachineContext & p_context, machine::BiaAllocator * p_pAllocator);
	BiaCompiler(BiaCompiler&&) = delete;
	BiaCompiler(const BiaCompiler&) = delete;
	~BiaCompiler();

	/**
	 * @see	bia::grammar::BiaReportReceiver::Report().
	 */
	virtual void Report(const grammar::Report * p_pBegin, const grammar::Report * p_pEnd) override;
	machine::BiaMachineSchein GetMachineSchein();

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
		PARAMETER,
		RESULT_REGISTER,	/**	Defines that the result is stored in the result register.	*/
		NONE,
	};

	union Value
	{
		int32_t nInt;
		int64_t llInt;
		float rFloat;
		double rDouble;
		struct String
		{
			const char * pcString;
			size_t iSize;
		} string;
		framework::BiaMember * pMember;
		BiaTempCounter::counter_type temporaryResultIndex;
		bool bTestValue;	/**	Defines the constant test value.	*/
		struct Parameter
		{
			const char * pcFormat;
			framework::BiaMember::parameter_count parameterCount;
			machine::architecture::BiaToolset::pass_count quartetsPassed;
		} parameter;
	};
	
	machine::architecture::BiaToolset m_toolset;	/**	Defines the compiler toolset for the specific C++ compiler and architecture.	*/
	machine::BiaMachineContext & m_context;	/**	Defines the context for which this script should be compiled.	*/
	machine::BiaMachineSchein m_machineSchein;
	
	BiaLocalVariableHandler m_localVariables;	/**	Handles the local variables.	*/

	machine::architecture::BiaToolset::temp_members m_parameter;	/**	Used for initializing and finalizing the code.	*/
	BiaTempCounter m_counter;	/**	Defines the temporary address counter for temporary storage.	*/

	VALUE_TYPE m_valueType;	/**	Defines the type of the last operation result.	*/
	Value m_value;	/**	Defines the value of the last operation result.	*/


	inline void SetValue(bool p_bValue)
	{
		m_valueType = VALUE_TYPE::TEST_VALUE_CONSTANT;
		m_value.bTestValue = p_bValue;
	}
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
	/**
	 * Handles the constant compare operation and stores the result in m_value.
	 *
	 * @since	3.57.118.681
	 * @date	1-Mar-18
	 *
	 * @param	p_left	Defines the left hand value.
	 * @param	p_right	Defines the right hand value.
	 * @param	p_unOperator	Defines the compare operator.
	*/
	template<typename _LEFT, typename _RIGHT>
	inline void HandleConstantCompareOperation(_LEFT && p_left, _RIGHT && p_right, uint32_t p_unOperator)
	{
		using namespace framework;

		switch (p_unOperator)
		{
		case BiaMember::O_EQUALS:
			return SetValue(p_left == p_right);
		case BiaMember::O_EQUALS_NOT:
			return SetValue(p_left != p_right);
		case BiaMember::O_LESS_THAN:
			return SetValue(p_left < p_right);
		case BiaMember::O_LESS_EQUALS:
			return SetValue(p_left <= p_right);
		case BiaMember::O_GREATER_THAN:
			return SetValue(p_left > p_right);
		case BiaMember::O_GREATER_EQUALS:
			return SetValue(p_left >= p_right);
		default:
			BIA_COMPILER_DEV_INVALID
		}
	}
	/**
	 * Handles the constant compare operation and stores the result in m_value.
	 *
	 * @since	3.57.118.681
	 * @date	1-Mar-18
	 *
	 * @param	p_leftType	Defines the type of the left hand value.
	 * @param	p_leftValue	Defines the left hand value.
	 * @param	p_right	Defines the right hand value.
	 * @param	p_unOperator	Defines the compare operator.
	*/
	template<typename _RIGHT>
	inline void HandleConstantCompareOperation(VALUE_TYPE p_leftType, Value p_leftValue, _RIGHT && p_right, uint32_t p_unOperator)
	{
		switch (p_leftType)
		{
		case VALUE_TYPE::INT_32:
			return HandleConstantCompareOperation(p_leftValue.nInt, p_right, p_unOperator);
		case VALUE_TYPE::INT_64:
			return HandleConstantCompareOperation(p_leftValue.llInt, p_right, p_unOperator);
		case VALUE_TYPE::FLOAT:
			return HandleConstantCompareOperation(p_leftValue.rFloat, p_right, p_unOperator);
		case VALUE_TYPE::DOUBLE:
			return HandleConstantCompareOperation(p_leftValue.rDouble, p_right, p_unOperator);
			//case VALUE_TYPE::STRING:
		default:
			BIA_COMPILER_DEV_INVALID
		}
	}
	void HandleConstantOperation(VALUE_TYPE p_leftType, Value p_leftValue, uint32_t p_unOperator);
	void HandleNumber(const grammar::Report * p_pReport);
	void HandleString(const grammar::Report * p_pReport);
	/**
	 * Handles the identifier and stores the address to m_value.
	 *
	 * @remarks	VALUE_TYPE::MEMBER is guaranteed to be returned.
	 *
	 * @since	3.57.118.681
	 * @date	2-Mar-18
	 *
	 * @param	p_pReport	Defines the identifier report.
	*/
	void HandleIdentifier(const grammar::Report * p_pReport);
	void HandleOperator(VALUE_TYPE p_leftType, Value p_leftValue, uint32_t p_unOperator, BiaTempCounter::counter_type p_destinationIndex);
	void HandleCompareOperator(VALUE_TYPE p_leftType, Value p_leftValue, uint32_t p_unOperator);
	template<typename _INSTANCE, typename _BIA_INSTANCE>
	inline void HandleFunctionCall(Value::Parameter p_paramter, _INSTANCE p_instance, _BIA_INSTANCE p_biaInstance, BiaTempCounter::counter_type p_destination)
	{
		//Parameters were passed
		if (p_paramter.parameterCount)
		{
			//Formatted parameters
			if (p_paramter.pcFormat)
				m_toolset.Call(p_paramter.quartetsPassed, &framework::BiaMember::CallFormat, p_instance, p_biaInstance, machine::architecture::BiaToolset::TemporaryMember(p_destination), p_paramter.parameterCount, p_paramter.pcFormat);
			//Pure members
			else
				m_toolset.Call(p_paramter.quartetsPassed, &framework::BiaMember::CallCount, p_instance, p_biaInstance, machine::architecture::BiaToolset::TemporaryMember(p_destination), p_paramter.parameterCount);
		}
		//Call without any parameters
		else
			m_toolset.Call(&framework::BiaMember::Call, p_instance, p_biaInstance, machine::architecture::BiaToolset::TemporaryMember(p_destination));


		m_valueType = VALUE_TYPE::TEMPORARY_MEMBER;
		m_value.temporaryResultIndex = p_destination;
	}
	template<typename _INSTANCE>
	inline void HandleInstantiationCall(Value::Parameter p_paramter, _INSTANCE p_instance, BiaTempCounter::counter_type p_destination)
	{
		//Parameters were passed
		if (p_paramter.parameterCount)
		{
			//Formatted parameters
			if (p_paramter.pcFormat)
				m_toolset.Call(p_paramter.quartetsPassed, &framework::BiaMember::InstantiateFormat, p_instance, machine::architecture::BiaToolset::TemporaryMember(p_destination), p_paramter.parameterCount, p_paramter.pcFormat);
			//Pure members
			else
				m_toolset.Call(p_paramter.quartetsPassed, &framework::BiaMember::InstantiateCount, p_instance, machine::architecture::BiaToolset::TemporaryMember(p_destination), p_paramter.parameterCount);
		}
		//Call without any parameters
		else
			m_toolset.Call(&framework::BiaMember::Instantiate, p_instance, machine::architecture::BiaToolset::TemporaryMember(p_destination));


		m_valueType = VALUE_TYPE::TEMPORARY_MEMBER;
		m_value.temporaryResultIndex = p_destination;
	}
	/**
	 * Handles the compare operator call for left hand members. The left hand value is stored in m_value.
	 *
	 * @since	3.57.118.681
	 * @date	1-Mar-18
	 *
	 * @param	p_instance	Defines the member.
	 * @param	p_unOperator	Defines the compare operator.
	*/
	template<typename _INSTANCE>
	inline void HandleCompareOperatorCall(_INSTANCE && p_instance, uint32_t p_unOperator)
	{
		//Right value
		switch (m_valueType)
		{
		case VALUE_TYPE::INT_32:
			m_toolset.Call(&framework::BiaMember::TestCallInt_32, p_instance, p_unOperator, m_value.nInt);

			break;
		case VALUE_TYPE::INT_64:
			m_toolset.Call(&framework::BiaMember::TestCallInt_64, p_instance, p_unOperator, m_value.llInt);

			break;
		case VALUE_TYPE::FLOAT:
			m_toolset.Call(&framework::BiaMember::TestCallFloat, p_instance, p_unOperator, m_value.rFloat);

			break;
		case VALUE_TYPE::DOUBLE:
			m_toolset.Call(&framework::BiaMember::TestCallDouble, p_instance, p_unOperator, m_value.rDouble);

			break;
		case VALUE_TYPE::STRING:
			m_toolset.Call(&framework::BiaMember::TestCallString, p_instance, p_unOperator, GetStringLocation(m_value.string));

			break;
		case VALUE_TYPE::MEMBER:
			m_toolset.Call(&framework::BiaMember::TestCall, p_instance, p_unOperator, m_value.pMember);

			break;
		case VALUE_TYPE::TEMPORARY_MEMBER:
			m_toolset.Call(&framework::BiaMember::TestCall, p_instance, p_unOperator, machine::architecture::BiaToolset::TemporaryMember(m_value.temporaryResultIndex));

			break;
		case VALUE_TYPE::RESULT_REGISTER:
			m_toolset.Call(&framework::BiaMember::TestCall, p_instance, p_unOperator, machine::architecture::BiaToolset::ResultValue());

			break;
		default:
			BIA_COMPILER_DEV_INVALID
		}
	}
	const char * GetNameAddress(const grammar::Report * p_pReport);
	const char * GetStringLocation(Value::String p_string);
	/**
	 * Returns the format string address bound to the context.
	 *
	 * @since	3.56.116.672
	 * @date	27-Feb-18
	 *
	 * @param	p_string	Defines the string that should be copied.
	 *
	 * @return	The format address bound to the context.
	*/
	const char * GetParameterFormat(Value::String p_string);
	//framework::BiaMember * GetAddressOfVariable();
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
			case grammar::BGR_TEST_LOOP:
			case grammar::BGR_IMPORT:
			case grammar::BGR_VALUE:
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
				return HandlePrint(p_pReport->content.children);
			case grammar::BGR_TEST_LOOP:
				return HandleTestLoop(p_pReport->content.children);
			case grammar::BGR_IMPORT:
				return HandleImport(p_pReport->content.children);
			case grammar::BGR_VALUE:
				return HandleValue<false>(p_pReport->content.children, [] {});
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
		auto lastCurrent = m_counter.PeekCurrent();

		//Handle value
		HandleValue<_TEST>(p_reports);

		//Execute function
		p_callback();
		
		//Pop value
		m_counter.Pop(lastCurrent);
		
		return p_reports.pEnd + 1;
	}
	template<bool _TEST>
	inline const grammar::Report * HandleValue(grammar::report_range p_reports)
	{
		switch (p_reports.pBegin[1].unRuleId)
		{
		case grammar::BGR_VALUE_EXPRESSION:
			HandleValueExpression<_TEST>(p_reports.pBegin[1].content.children);

			break;
		case grammar::BGR_VALUE_HELPER_0:
		{
			Value destination;
			uint32_t unOperator = 0;
			
			//Get address of destination
			destination.pMember = m_context.AddressOf(machine::StringKey(p_reports.pBegin[1].content.token.pcString, p_reports.pBegin[1].content.token.iSize));

			//Convert operator
			memcpy(&unOperator, p_reports.pBegin[2].content.token.pcString, std::min(sizeof(unOperator), p_reports.pBegin[2].content.token.iSize));

			//Handle right hand value
			HandleValueExpression<false>(p_reports.pBegin[3].content.children);

			//Call assign operator
			HandleOperator(VALUE_TYPE::MEMBER, destination, unOperator, -1);

			break;
		}
		default:
			BIA_COMPILER_DEV_INVALID
		}

		return p_reports.pEnd + 1;
	}
	template<bool _TEST>
	inline const grammar::Report * HandleValueExpression(grammar::report_range p_reports)
	{
		using JUMP = machine::architecture::BiaToolset::JUMP;

		//Handle all logical operators
		auto bTest = false;
		std::vector<std::pair<JUMP, machine::architecture::BiaToolset::position>> vEndJumps;

		goto gt_start;

		while (p_reports.pBegin < p_reports.pEnd)
		{
			//Logical operator
			switch (p_reports.pBegin->unTokenId)
			{
			case grammar::BVO_LOGICAL_AND:
			{
				//Constant test result
				if (m_valueType == VALUE_TYPE::TEST_VALUE_CONSTANT)
				{
					if (!m_value.bTestValue)
					{
						vEndJumps.push_back({ JUMP::JUMP, m_toolset.WriteJump(JUMP::JUMP) });

						goto gt_end;
					}
				}
				//Jump to next condition
				else
				vEndJumps.push_back({ JUMP::JUMP_IF_FALSE, m_toolset.WriteJump(JUMP::JUMP_IF_FALSE) });

				break;
			}
			case grammar::BVO_LOGICAL_OR:
			default:
				BIA_COMPILER_DEV_INVALID
			}

		gt_start:;
			//Handle first expression
			p_reports.pBegin = HandleConditionExpression(p_reports.pBegin[1].content.children);

			//Test
			if (_TEST || bTest || p_reports.pBegin < p_reports.pEnd)
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

			//Test next value
			bTest = true;
		}

	gt_end:;
		//Update end jump locations
		auto endPos = m_toolset.GetBuffer().GetPosition();

		for (auto & jumpPos : vEndJumps)
			m_toolset.WriteJump(jumpPos.first, endPos, jumpPos.second);

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
	const grammar::Report * HandleConditionExpression(grammar::report_range p_reports);
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
			BiaTempCounter::counter_type destination = -1;
			const grammar::Report * i = (this->*NEXT)(p_reports.pBegin[1].content.children);
			auto leftType = m_valueType;
			auto leftValue = m_value;

			//Pop if not used
			if (m_valueType != VALUE_TYPE::TEMPORARY_MEMBER)
				m_counter.Pop(currentCounter);

			do
			{
				//Move string operator to int 32 bit value
				uint32_t unOperator = 0;

				memcpy(&unOperator, i->content.token.pcString, std::min(sizeof(unOperator), i->content.token.iSize));

				//Handle first right math term
				i = (this->*NEXT)(i[1].content.children);

				//Pop if not used
				if (m_valueType != VALUE_TYPE::TEMPORARY_MEMBER)
					m_counter.Pop(currentCounter);

				//Call operator
				if (leftType == VALUE_TYPE::MEMBER || leftType == VALUE_TYPE::TEMPORARY_MEMBER ||
					m_valueType == VALUE_TYPE::MEMBER || m_valueType == VALUE_TYPE::TEMPORARY_MEMBER)
				{
					//Set destination if needed
					if (destination == -1)
					{
						m_counter.Current();

						destination = currentCounter;
					}

					HandleOperator(leftType, leftValue, unOperator, destination);
				}
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
	/**
	 * Handles all if-else branch statements.
	 *
	 * @since	3.51.112.650
	 * @date	20-Jan-18
	 *
	 * @param	p_reports	Defines the if token.
	 *
	 * @return	The begin of the next token.
	*/
	const grammar::Report * HandleIf(grammar::report_range p_reports);
	/**
	 * Handles the print value and prints it.
	 *
	 * @since	3.51.112.650
	 * @date	20-Jan-18
	 *
	 * @param	p_reports	Defines the print token.
	 *
	 * @return	The begin of the next token.
	*/
	const grammar::Report * HandlePrint(grammar::report_range p_reports);
	const grammar::Report * HandleMember(grammar::report_range p_reports);
	const grammar::Report * HandleParameters(grammar::report_range p_reports);
	const grammar::Report * HandleTestLoop(grammar::report_range p_reports);
	const grammar::Report * HandleImport(grammar::report_range p_reports);
	const grammar::Report * HandleInstantiation(grammar::report_range p_reports, BiaTempCounter::counter_type p_destination);
} ;

}
}