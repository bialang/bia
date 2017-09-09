#include "biaCompiler.h"
#include "biaGrammar.h"


namespace bia
{
namespace api
{
namespace compiler
{

using namespace machine;
using namespace grammar;


BiaCompiler::BiaCompiler(stream::BiaStream & p_output) : m_output(p_output)
{
}

void BiaCompiler::CommenceReporting()
{
}

void BiaCompiler::CompleteReport()
{
}

void BiaCompiler::Report(const std::vector<yu::interpret::SReport>& p_vReports)
{
#ifdef BIA_DEVELOPER_MODE
	//PrintReport(&p_vReports, "");
#endif

	HandleRoot(p_vReports.begin()._Ptr, p_vReports.end()._Ptr);
}

size_t BiaCompiler::CancelReport(const ycode * p_pCode)
{
	printf("Syntax error:\n");

	if (p_pCode)
	{
		putchar('\t');
		fwrite(p_pCode->GetBuffer(), p_pCode->GetSize(), 1, stdout);
		puts("\n");
	}

	return 0;
}

void BiaCompiler::PrintReport(const std::vector<yu::interpret::SReport>* p_pvReport, std::string p_stIndent)
{
	for each(auto & report in *p_pvReport)
	{
		printf("%sRule %d\tTerm %lld\tToken %lld\n%s", p_stIndent.c_str(), report.uiRule, report.llTermId, report.llTokenId, p_stIndent.c_str());
		fwrite(report.code.GetBuffer(), report.code.GetSize(), 1, stdout);
		putchar('\n');

		if (report.pvTokenUnion)
		{
			printf("%sPrinting children:\n", p_stIndent.c_str());
			PrintReport(report.pvTokenUnion, p_stIndent + "\t");
		}
	}
}

void BiaCompiler::HandleRoot(const yu::interpret::SReport * p_pBegin, const yu::interpret::SReport * p_pEnd)
{
	for (; p_pBegin < p_pEnd; ++p_pBegin)
	{
		switch (p_pBegin->llTermId)
		{
		case BGI_TERM_VARIABLE_DECLARATION:
		{
			HandleVariableDeclaration(p_pBegin);

			break;
		}
		case BGI_TERM_VARIABLE_ASSIGNEMENT:
		{
			HandleVariableAssignment(p_pBegin);

			break;
		}
		case BGI_TERM_CALL:
		{
			HandleValue(p_pBegin, false);

			break;
		}
		case BGI_TERM_WHILE:
		{
			compiler::BiaConditionMaker maker(m_output);
			auto pToken = p_pBegin->pvTokenUnion->begin()._Ptr;

			//Handle condition for first time
			HandleValue(pToken, false);
			WriteConstant(OP::JUMP_CONDITIONAL_NOT, 0LL);
			maker.MarkPlaceholder(compiler::BiaConditionMaker::L_END);
			maker.MarkLocation(compiler::BiaConditionMaker::L_BEGIN);

			//Handle statement
			if (p_pBegin->pvTokenUnion->size() > 1)
				HandleRoot(pToken[1].pvTokenUnion->begin()._Ptr, pToken[1].pvTokenUnion->end()._Ptr);

			//Write jump to end
			HandleValue(pToken, false);
			WriteConstant(OP::JUMP_CONDITIONAL, 0LL);
			maker.MarkPlaceholder(compiler::BiaConditionMaker::L_BEGIN);
			maker.MarkLocation(compiler::BiaConditionMaker::L_END);

			maker.ReplaceAll();

			break;
		}
		case BGI_TERM_IF:
		{
			compiler::BiaConditionMaker maker(m_output);

			for (auto i = p_pBegin->pvTokenUnion->begin()._Ptr, cond = p_pBegin->pvTokenUnion->end()._Ptr; i < cond; ++i)
			{
				//Handle else statement
				if (i->llTokenId == BGI_KEY_ELSE)
				{
					if (++i < cond)
						HandleRoot(i->pvTokenUnion->begin()._Ptr, i->pvTokenUnion->end()._Ptr);

					break;
				}
				//Only write if statement is not empty
				else
				{
					//Handle condition
					HandleValue(i, false, &maker);

					if (i + 1 < cond && i[1].llTokenId == BGI_R_ROOT)
					{
						//Write placeholder
						WriteConstant(OP::JUMP_CONDITIONAL_NOT, 0LL);
						maker.MarkPlaceholder(compiler::BiaConditionMaker::L_NEXT);

						//Handle statement
						HandleRoot(i[1].pvTokenUnion->begin()._Ptr, i[1].pvTokenUnion->end()._Ptr);

						//Write jump to end
						if (i + 2 < cond)
						{
							WriteConstant(OP::JUMP, 0LL);
							maker.MarkPlaceholder(compiler::BiaConditionMaker::L_END);
						}

						//Overwrite last next placeholder
						maker.MarkLocation(compiler::BiaConditionMaker::L_NEXT);

						++i;
					}
					//Empty body but other statements follow
					else if (i + 2 < cond)
					{
						//Write jump to end
						WriteConstant(OP::JUMP_CONDITIONAL, 0LL);
						maker.MarkPlaceholder(compiler::BiaConditionMaker::L_END);
					}
				}
			}

			//Replace all marks
			maker.MarkLocation(compiler::BiaConditionMaker::L_END);
			maker.ReplaceAll();

			break;
		}
		case BGI_TERM_FOR:
		{
			compiler::BiaConditionMaker maker(m_output);
			auto pToken = p_pBegin->pvTokenUnion->begin()._Ptr;
			auto pTokenEnd = p_pBegin->pvTokenUnion->end()._Ptr;

			//Handle variable declaration
			if (pToken->llTokenId == BGI_VARIABLE_DECLARATION)
				HandleVariableDeclaration(pToken++);
			//Handle variable assignment
			else if (pToken->llTokenId == BGI_VARIABLE_ASSIGNMENT)
				HandleVariableAssignment(pToken++);

			auto pCondition = pToken++;
			auto pForLoopRight = pToken < pTokenEnd && pToken->llTokenId == BGI_FOR_LOOP_RIGHT ? pToken++ : nullptr;

			//Handle condition for first time
			HandleValue(pCondition, false, &maker);
			WriteConstant(OP::JUMP_CONDITIONAL_NOT, 0LL);

			maker.MarkPlaceholder(compiler::BiaConditionMaker::L_END);
			maker.MarkLocation(compiler::BiaConditionMaker::L_BEGIN);

			//Handle registers if requested
			if (pToken < pTokenEnd && pToken->llTokenId == BGI_LOOP_REGISTERS)
			{
				//Scan only if statements are available
				if (pToken + 1 < pTokenEnd)
				{
					HandleLoopRegisters(pToken->pvTokenUnion->begin()._Ptr, pToken++->pvTokenUnion->end()._Ptr, pToken->pvTokenUnion->begin()._Ptr, pToken->pvTokenUnion->end()._Ptr);

					//Handle statement
					HandleRoot(pToken->pvTokenUnion->begin()._Ptr, pToken->pvTokenUnion->end()._Ptr);
				}
			}
			//Handle statement
			else if (pToken < pTokenEnd)
				HandleRoot(pToken->pvTokenUnion->begin()._Ptr, pToken->pvTokenUnion->end()._Ptr);

			//Handle last statement
			if (pForLoopRight)
			{
				/*if (pForLoopRight->llTokenId == BGI_VARIABLE_ASSIGNMENT)
					HandleVariableAssignment(pForLoopRight);
				else*/
					HandleValue(pForLoopRight, false);
			}

			//Write jump to end
			HandleValue(pCondition, false, &maker);
			WriteConstant(OP::JUMP_CONDITIONAL, 0LL);
			maker.MarkPlaceholder(compiler::BiaConditionMaker::L_BEGIN);
			maker.MarkLocation(compiler::BiaConditionMaker::L_END);

			maker.ReplaceAll();

			break;
		}
		case BGI_TERM_RANGE_LOOP:
		{
			auto pToken = p_pBegin->pvTokenUnion->begin()._Ptr;
			auto pTokenEnd = p_pBegin->pvTokenUnion->end()._Ptr;

			//Handle variable declaration
			if (pToken->llTokenId == BGI_VARIABLE_DECLARATION)
			{
				HandleVariableDeclaration(pToken);

				//Load created object into accumulator for range loop
				WriteOpCode(OP::LOAD, &pToken++->pvTokenUnion->at(0).code);
			}
			//Handle variable assignment
			else if (pToken->llTokenId == BGI_VARIABLE_ASSIGNMENT)
				HandleVariableAssignment(pToken++);

			//Write end and step
			WriteOpCode(OP::RANGE_LONG);
			HandleNumber(pToken++, NUMBER_TYPE::WRITE);
			HandleNumber(pToken++, NUMBER_TYPE::WRITE);
			
			//Write placeholder for loop size
			auto llPosSize = m_output.TellWrite();
			uint32_t uiTmp = 0;

			m_output.Write(&uiTmp, sizeof(uint32_t));


			//Handle statement
			if (pToken < pTokenEnd)
				HandleRoot(pToken->pvTokenUnion->begin()._Ptr, pToken->pvTokenUnion->end()._Ptr);

			//End range
			WriteOpCode(OP::RANGE_END);

			auto llPosEnd = m_output.TellWrite();
			
			m_output.SeekWrite(llPosSize);
			uiTmp = static_cast<uint32_t>(llPosEnd - llPosSize - sizeof(uint32_t));
			m_output.Write(&uiTmp, sizeof(uint32_t));
			
			m_output.SeekWrite(llPosEnd);

			break;
		}
		case BGI_TERM_PRINT:
		{
			HandleValue(p_pBegin, false);

			WriteOpCode(OP::PRINT_ACCUMULATOR);

			break;
		}
		case BGI_TERM_RETURN:
		{
			if (p_pBegin->pvTokenUnion->size() > 1)
			{
				HandleValue(p_pBegin->pvTokenUnion->begin()._Ptr + 1, false);

				WriteOpCode(OP::RETURN_ACCUMULATOR);
			}
			else
				WriteOpCode(OP::RETURN_VOID);

			break;
		}
		case BGI_TERM_IMPORT:
		{
			constexpr auto terminator = 0i8;

			WriteOpCode(OP::IMPORT);

			//From
			size_t iModule = p_pBegin->pvTokenUnion->size() > 1 && p_pBegin->pvTokenUnion->at(0).llTokenId != BGI_IMPORT_MODULE ? 1 : 0;
			
			auto usSize = static_cast<unsigned short>(p_pBegin->pvTokenUnion->at(iModule).code.GetSize()) + 4;

			m_output.Write(&usSize, sizeof(unsigned short));
			m_output.Write(p_pBegin->pvTokenUnion->at(iModule).code.GetBuffer(), usSize - 4);
			m_output.Write(".bll", 4);
			m_output.Write(&terminator, 1);

			//Alias
			if (p_pBegin->pvTokenUnion->size() > iModule + 1)
			{
				auto ucSize = static_cast<unsigned char>(p_pBegin->pvTokenUnion->at(iModule + 1).code.GetSize());

				m_output.Write(&ucSize, sizeof(unsigned char));
				m_output.Write(p_pBegin->pvTokenUnion->at(iModule + 1).code.GetBuffer(), ucSize);
			}
			else
				m_output.Write(&terminator, 1);

			//Zero-terminator
			m_output.Write(&terminator, 1);

			//Add specific name
			if (iModule)
			{
				auto ucSize = static_cast<unsigned char>(p_pBegin->pvTokenUnion->at(0).code.GetSize());

				m_output.Write(&ucSize, sizeof(unsigned char));
				m_output.Write(p_pBegin->pvTokenUnion->at(0).code.GetBuffer(), ucSize);
			}
			else
				m_output.Write(&terminator, 1);

			break;
		}
		case BGI_TERM_DELETE:
		{
			//WriteOpCode(OP::DELETE, &p_pBegin->code);

			break;
		}
		case BGI_TERM_FUNCTION_DEFINITION:
		{
			WriteOpCode(OP::DEFINE_FUNCTION, &p_pBegin++->code);
			auto pos = m_output.TellWrite();
			unsigned int unSize = 0;

			m_output.Write(&unSize, sizeof(unsigned int));

			for (auto i = p_pBegin->pvTokenUnion->begin()._Ptr + 1, cond = p_pBegin->pvTokenUnion->end()._Ptr; i < cond; ++i)
				WriteOpCode(OP::MAKE_PARAMETER, &i->code);

			if (p_pBegin + 1 < p_pEnd)
				HandleRoot((++p_pBegin)->pvTokenUnion->begin()._Ptr, p_pBegin->pvTokenUnion->end()._Ptr);

			auto pos1 = m_output.TellWrite();
			unSize = static_cast<unsigned int>(pos1 - pos - 4);

			m_output.SeekWrite(pos);
			m_output.Write(&unSize, sizeof(unsigned int));
			m_output.SeekWrite(pos1);
		}
		default:
			break;
		}
	}
}

void BiaCompiler::WriteOpCode(OP p_code, const ycode * p_pFirst, unsigned char p_ucParameterCount)
{
	m_output.Write(&p_code, sizeof(OP));

	if (p_ucParameterCount != 0xff)
		m_output.Write(&p_ucParameterCount, sizeof(unsigned char));

	//First
	if (p_pFirst)
	{
		auto iSize = p_pFirst->GetSize();

		//To large
		if (iSize > 0xff)
			throw exception::SymbolException("Symbol too long");

		auto ucSize = static_cast<unsigned char>(iSize);
		auto ullHash = utility::Hash64(p_pFirst->GetBuffer<char>(), ucSize);
		auto unHash = utility::Hash32(p_pFirst->GetBuffer<char>(), ucSize);

		m_output.Write(&ullHash, sizeof(unsigned long long));
		m_output.Write(&unHash, sizeof(unsigned int));
		m_output.Write(&ucSize, sizeof(unsigned char));
		m_output.Write(p_pFirst->GetBuffer(), p_pFirst->GetSize());
	}
}

void BiaCompiler::WriteOperator(OP p_code, const ycode & p_operator)
{
	m_output.Write(&p_code, sizeof(OP));
	
	unsigned int uiOperator = 0;
	
	memcpy(&uiOperator, p_operator.GetBuffer(), std::min(sizeof(unsigned int), p_operator.GetSize()));

	m_output.Write(&uiOperator, sizeof(unsigned int));
}

void BiaCompiler::HandleNumber(const yu::interpret::SReport * p_pReport, BiaCompiler::NUMBER_TYPE p_type)
{
	enum
	{
		LONG,
		FLOAT,
		DOUBLE
	} type;

	type = LONG;

	//Check if number is a real number
	for (auto i = p_pReport->pvTokenUnion->begin()._Ptr, cond = p_pReport->pvTokenUnion->end()._Ptr; i < cond; ++i)
	{
		if (i->llTokenId == BGI_DOT_OPERATOR)
		{
			i = cond - 1;

			if (i->llTokenId == BGI_NUMBER_LITERAL && tolower(*i->code.GetBuffer<char>()) == 'f')
				type = FLOAT;
			else
				type = DOUBLE;

			break;
		}
	}

	try
	{
		auto bPush = p_type == NUMBER_TYPE::PUSH;

		//Handle long
		if (type == LONG)
		{
			auto llTmp = std::stoll(std::string(p_pReport->code.GetBuffer<char>(), p_pReport->code.GetSize()));

			if (p_type == NUMBER_TYPE::WRITE)
				m_output.Write(&llTmp, sizeof(long long));
			else
			{
				switch (llTmp)
				{
				case -1:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_LONG_N1 : OP::LOAD_LONG_N1);

					break;
				case 0:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_LONG_0 : OP::LOAD_LONG_0);

					break;
				case 1:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_LONG_1 : OP::LOAD_LONG_1);

					break;
				case 2:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_LONG_2 : OP::LOAD_LONG_2);

					break;
				case 3:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_LONG_3 : OP::LOAD_LONG_3);

					break;
				case 5:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_LONG_5 : OP::LOAD_LONG_5);

					break;
				case 10:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_LONG_10 : OP::LOAD_LONG_10);

					break;
				case 100:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_LONG_100 : OP::LOAD_LONG_100);

					break;
				case 1000:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_LONG_1000 : OP::LOAD_LONG_1000);

					break;
				case 1000000:
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_LONG_1000000 : OP::LOAD_LONG_1000000);

					break;
				default:
					WriteConstant(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_LONG : OP::LOAD_LONG, llTmp);

					break;
				}
			}
		}
		else if (type == FLOAT)
		{
			auto rTmp = std::stof(std::string(p_pReport->code.GetBuffer<char>(), p_pReport->code.GetSize()));

			if (p_type == NUMBER_TYPE::WRITE)
				m_output.Write(&rTmp, sizeof(float));
			else
			{
				if (rTmp == 0.0f)
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_FLOAT_0 : OP::LOAD_FLOAT_0);
				else if (rTmp == 1.0f)
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_FLOAT_1 : OP::LOAD_FLOAT_1);
				else if (rTmp == -1.0f)
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_FLOAT_N1 : OP::LOAD_FLOAT_N1);
				else
					WriteConstant(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_FLOAT : OP::LOAD_FLOAT, rTmp);
			}
		}
		else
		{
			auto rTmp = std::stod(std::string(p_pReport->code.GetBuffer<char>(), p_pReport->code.GetSize()));

			if (p_type == NUMBER_TYPE::WRITE)
				m_output.Write(&rTmp, sizeof(double));
			else
			{
				if (rTmp == 0.0)
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_DOUBLE_0 : OP::LOAD_DOUBLE_0);
				else if (rTmp == 1.0)
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_DOUBLE_1 : OP::LOAD_DOUBLE_1);
				else if (rTmp == -1.0)
					WriteOpCode(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_DOUBLE_N1 : OP::LOAD_DOUBLE_N1);
				else
					WriteConstant(p_type == NUMBER_TYPE::PUSH ? OP::PUSH_DOUBLE : OP::LOAD_DOUBLE, rTmp);
			}
		}
	}
	catch (...)
	{
		throw exception::ArgumentException("Invalid number.");
	}
}

void BiaCompiler::HandleValue_(const yu::interpret::SReport * p_pReport, const bool & p_bPush)
{
	switch (p_pReport->llTokenId)
	{
	case BGI_KEY_TRUE:
	{
		WriteOpCode(p_bPush ? OP::PUSH_LONG_1 : OP::LOAD_LONG_1);

		return;
	}
	case BGI_KEY_FALSE:
	case BGI_KEY_NULL:
	{
		WriteOpCode(p_bPush ? OP::PUSH_LONG_0 : OP::LOAD_LONG_0);

		return;
	}
	case BGI_NUMBER:
	{
		HandleNumber(p_pReport, p_bPush ? NUMBER_TYPE::PUSH : NUMBER_TYPE::LOAD);

		return;
	}
	case BGI_STRING:
	{
		auto & str = p_pReport->pvTokenUnion->at(1);

		//Empty string
		if (str.llTokenId == BGI_QUOTE)
		{
			WriteOpCode(p_bPush ? OP::PUSH_STRING_EMPTY : OP::LOAD_STRING_EMPTY);

			return;
		}
		//Normal string
		else
			WriteConstant(p_bPush ? OP::PUSH_STRING : OP::LOAD_STRING, 0ui16);


		auto usSize = static_cast<unsigned short>(str.code.GetSize());
		auto llPos = m_output.TellWrite() - 2;
		auto pcDst = m_output.GetBuffer(usSize + 1);
		auto pcSrc = str.code.GetBuffer<char>();
		auto pcLast = pcSrc;
		auto pcSrcEnd = pcSrc + usSize;
		auto bEscape = false;

		//Write string
		while (pcSrc < pcSrcEnd)
		{
			auto pcTmp = pcSrc;

			if (bEscape)
			{
				switch (utf8::next(pcSrc, pcSrcEnd))
				{
				case 'n':
					*pcDst++ = '\n';
					++pcLast;

					break;
				case 't':
					*pcDst++ = '\t';
					++pcLast;

					break;
				case 'r':
					*pcDst++ = '\r';
					++pcLast;

					break;
				case 'b':
					*pcDst++ = '\b';
					++pcLast;

					break;
				default:
					break;
				}


				bEscape = false;
			}
			else
			{
				switch (utf8::next(pcSrc, pcSrcEnd))
				{
				case '\\':
					memcpy(pcDst, pcLast, pcTmp - pcLast);

					pcDst += pcTmp - pcLast;
					pcLast = pcSrc;
					bEscape = true;
					--usSize;
				default:
					break;
				}
			}
		}

		memcpy(pcDst, pcLast, pcSrc - pcLast);
		pcDst[pcSrc - pcLast] = 0;

		m_output.CommitBuffer(usSize);

		auto llTmp = m_output.TellWrite();

		//Update size
		m_output.SeekWrite(llPos);
		m_output.Write(&usSize, 2);
		m_output.SeekWrite(llTmp);

		//Push result
		if (p_bPush)
		{
			constexpr auto terminator = 0i8;

			m_output.Write(&terminator, 1);
		}

		return;
	}
	case BGI_COPYOF:
	{
		HandleMemberCall(&p_pReport->pvTokenUnion->at(0), p_bPush ? PUSH_TYPE::PUSH_COPY : PUSH_TYPE::LOAD_COPY);

		return;
	}
	case BGI_MEMBER_CALL:
	{
		HandleMemberCall(p_pReport, p_bPush ? PUSH_TYPE::PUSH : PUSH_TYPE::LOAD);

		return;
	}
	case BGI_INSTANTIATION:
	{
		HandleInstatiation(p_pReport);

		break;
	}
	default:
		break;
	}

	//Otherwise push accumulator
	if (p_bPush)
		WriteOpCode(OP::PUSH_ACCUMULATOR);
}

void BiaCompiler::HandleValue(const yu::interpret::SReport * p_pReport, bool p_bPush, BiaConditionMaker * p_pMaker)
{
	auto bDestruct = false;

	if (!p_pMaker)
	{
		thread_local char acBuffer[sizeof(BiaConditionMaker)];

		p_pMaker = new(acBuffer) BiaConditionMaker(m_output);
		bDestruct = true;
	}

	//BiaConditionMaker maker(m_output);

	for (auto i = p_pReport->pvTokenUnion->begin()._Ptr, cond = p_pReport->pvTokenUnion->end()._Ptr; i < cond; ++i)
	{
		if (i->llTokenId == BGI_CONDITIONAL_AND)
		{
			WriteConstant(OP::JUMP_CONDITIONAL_NOT, 0ll);
			p_pMaker->MarkPlaceholder(BiaConditionMaker::L_END);
		}
		else if (i->llTokenId == BGI_CONDITIONAL_OR)
		{
			WriteConstant(OP::JUMP_CONDITIONAL, 0ll);
			p_pMaker->MarkPlaceholder(BiaConditionMaker::L_END);
		}
		else if (i->llTokenId == BGI_VALUE)
		{
			switch (i->pvTokenUnion->size())
			{
			case 1://Handle expression
			{
				HandleMathExpression(i->pvTokenUnion->begin()._Ptr, p_bPush);

				break;
			}
			case 3://Handle condition
			{
				HandleMathExpression(i->pvTokenUnion->begin()._Ptr + 2, true);
				HandleMathExpression(i->pvTokenUnion->begin()._Ptr, false);

				//WriteOpCode(OP::CALL, &i->pvTokenUnion->begin()._Ptr[1].code, 1);
				WriteOperator(OP::CALL_OPERATOR, i->pvTokenUnion->operator[](1).code);

				//Push boolean
				if (p_bPush)
					WriteOpCode(OP::PUSH_ACCUMULATOR);

				break;
			}
			default:
				break;
			}
		}
		else
		{
			throw std::string("");
			HandleValue(i, p_bPush);
		}
	}

	if (bDestruct)
	{
		p_pMaker->MarkLocation(BiaConditionMaker::L_END);
		p_pMaker->ReplaceAll();
		p_pMaker->~BiaConditionMaker();
	}
}

void BiaCompiler::HandleLoopRegisters(const yu::interpret::SReport * p_pRegisterBegin, const yu::interpret::SReport * p_pRegisterEnd, const yu::interpret::SReport * p_pBegin, const yu::interpret::SReport * p_pEnd)
{
	++p_pRegisterBegin;

	//Check if selection is negated
	auto bNegated = false;

	if (p_pRegisterBegin < p_pRegisterEnd && p_pRegisterBegin->llTokenId == BGI_EXCLAMATION_MARK)
	{
		bNegated = true;

		++p_pRegisterBegin;
	}

	//Register selection
	for (; p_pRegisterBegin < p_pRegisterEnd; ++p_pRegisterBegin)
	{

	}

	for (; p_pBegin < p_pEnd; ++p_pBegin)
	{
		printf("Found: %lli ", p_pBegin->pvTokenUnion->begin()->llTokenId);
		fwrite(p_pBegin->code.GetBuffer(), 1, p_pBegin->code.GetSize(), stdout);
		puts("");
	}
}

void BiaCompiler::HandleMathExpression(const yu::interpret::SReport * p_pReport, const bool & p_bPush)
{
	auto i = p_pReport->pvTokenUnion->end()._Ptr;
	auto cond = p_pReport->pvTokenUnion->begin()._Ptr;
	auto bNegate = false;

	//Negate
	if (cond->llTokenId == BGI_MATH_MINUS)
	{
		bNegate = true;

		++cond;
	}

	auto pLeft = cond++;

	//Push all terms starting from the right
	while (i-- > cond)
		HandleMathTerm(i--, true);

	i = cond;
	cond = p_pReport->pvTokenUnion->end()._Ptr;
	/*
	if (bNegate)
	{
		WriteConstant(OP::LOAD_LONG, -1LL);
		WriteOpCode(OP::PUSH_ACCUMULATOR);
	}*/

	//Load left object
	HandleMathTerm(pLeft, p_pReport->pvTokenUnion->size() == 1 && p_bPush);
	/*
	if (bNegate)
	{
		static ycode func = "*";
		WriteOpCode(OP::CALL, &func, nullptr, nullptr, 1);
	}
	*/
	while(i < cond)
	{
		WriteOperator(OP::CALL_OPERATOR, i->code);

		i += 2;
	}

	if (p_pReport->pvTokenUnion->size() > 1 && p_bPush)
		WriteOpCode(OP::PUSH_ACCUMULATOR);
}

void BiaCompiler::HandleMathTerm(const yu::interpret::SReport * p_pReport, const bool & p_bPush)
{
	auto i = p_pReport->pvTokenUnion->end()._Ptr;
	auto cond = p_pReport->pvTokenUnion->begin()._Ptr + 1;

	//Push all values starting from the right
	while (i-- > cond)
		HandleMathFactor(i--, true);

	cond = p_pReport->pvTokenUnion->end()._Ptr;

	auto pLeft = i++;
	auto bPushed = false;

	do
	{
		yu::interpret::SReport * pOperator = nullptr;

		//Get operator
		if (i + 1 < cond)
		{
			pOperator = i;

			i += 2;
		}

		//Load object
		if (pLeft)
		{
			if (pOperator)
				HandleMathFactor(pLeft, false);
			else
			{
				HandleMathFactor(pLeft, p_bPush);

				bPushed = true;
			}

			pLeft = nullptr;
		}

		//Call operator
		if (pOperator)
			WriteOperator(OP::CALL_OPERATOR, pOperator->code);
	} while (i < cond);

	if (p_bPush && !bPushed)
		WriteOpCode(OP::PUSH_ACCUMULATOR);
}

void BiaCompiler::HandleMathFactor(const yu::interpret::SReport * p_pReport, const bool & p_bPush)
{
	if (p_pReport->llTokenId == BGI_MATH_EXPRESSION)
		HandleMathExpression(p_pReport, p_bPush);
	else
		HandleValue_(p_pReport, p_bPush);
}

void BiaCompiler::HandleVariableDeclaration(const yu::interpret::SReport * p_pReport)
{
	HandleValue(p_pReport->pvTokenUnion->begin()._Ptr + 1, false);

	WriteOpCode(OP::OBJECTIFY, &p_pReport->pvTokenUnion->at(0).code);
}

void BiaCompiler::HandleVariableAssignment(const yu::interpret::SReport * p_pReport)
{
	HandleValue(p_pReport->pvTokenUnion->begin()._Ptr + 2, true);

	HandleMemberCall(&p_pReport->pvTokenUnion->at(0), PUSH_TYPE::LOAD);

	auto & assignOperator = p_pReport->pvTokenUnion->at(1).code;

	if (assignOperator == "=")
		WriteOpCode(OP::STORE);
	else
		WriteOperator(OP::CALL_OPERATOR, assignOperator);
}

void BiaCompiler::HandleMemberCall(const yu::interpret::SReport * p_pReport, PUSH_TYPE p_type)
{
	const ycode * pPrefix = nullptr;
	auto i = p_pReport->pvTokenUnion->begin()._Ptr;
	auto cond = p_pReport->pvTokenUnion->end()._Ptr;

	if (i->llTokenId == BGI_OPERATOR)
		pPrefix = &i++->code;

	auto * pCallerName = IsFunction(i, cond, false) ? nullptr : &i++->code;
	auto bFirstCall = true;

	//Only one object
	if (i == cond && pCallerName)
	{
		if (pPrefix)
		{
			WriteOpCode(OP::LOAD, pCallerName);

			if (!pPrefix->Compare("++"))
				WriteOpCode(OP::INCREMENT);
			else if (!pPrefix->Compare("--"))
				WriteOpCode(OP::DECREMENT);
			else
				WriteOperator(OP::CALL_SELF_OPERATOR, *pPrefix);

			if (p_type == PUSH_TYPE::PUSH || p_type == PUSH_TYPE::PUSH_COPY)
				WriteOpCode(OP::PUSH_ACCUMULATOR);
		}
		else
		{
			switch (p_type)
			{
			case PUSH_TYPE::LOAD:
				WriteOpCode(OP::LOAD, pCallerName);

				break;
			case PUSH_TYPE::LOAD_COPY:
				WriteOpCode(OP::LOAD_COPY, pCallerName);

				break;
			case PUSH_TYPE::PUSH:
				WriteOpCode(OP::PUSH, pCallerName);

				break;
			case PUSH_TYPE::PUSH_COPY:
				WriteOpCode(OP::PUSH_COPY, pCallerName);

				break;
			default:
				break;
			}
		}

		return;
	}

	for (; i < cond; ++i)
	{
		//Handle function
		if (IsFunction(i, cond, true))
		{
			static ycode itemAccessName = "[]";
			auto bFunctionCall = IsFunction(i, cond, false);
			auto * pName = bFunctionCall ? &i[0].code : &itemAccessName;
			auto ucParameterCount = bFunctionCall ? HandleIdentifierAccess(++i) : HandleIdentifierAccess(i);

			//Write caller on first function call
			if (bFirstCall)
			{
				//Caller is a global function
				if (!pCallerName && bFunctionCall)
				{
					WriteOpCode(OP::CALL_GLOBAL, pName, ucParameterCount);

					bFirstCall = false;

					continue;
				}

				WriteOpCode(OP::LOAD, pCallerName);

				bFirstCall = false;
			}

			//Call the function
			WriteOpCode(OP::CALL, pName, ucParameterCount);
		}
		//Variable load
		else
		{
			auto * pName = &i[0].code;

			//Write caller on first function call
			if (bFirstCall)
			{
				//Caller is a global function
				if (!pCallerName)
				{
					//WriteOpCode(OP::CALL_GLOBAL, pName, "vg:");

					bFirstCall = false;

					continue;
				}

				WriteOpCode(OP::LOAD, pCallerName);

				bFirstCall = false;
			}

			//Call the function
			WriteOpCode(OP::LOAD_FROM_ACCUMULATOR, pName);
		}
	}

	//Push return value if needed
	if (p_type == PUSH_TYPE::PUSH || p_type == PUSH_TYPE::PUSH_COPY)
		WriteOpCode(OP::PUSH_ACCUMULATOR);
}

void BiaCompiler::HandleInstatiation(const yu::interpret::SReport * p_pReport)
{
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
}

bool BiaCompiler::IsFunction(const yu::interpret::SReport * p_pReport, const yu::interpret::SReport * p_pEnd, bool p_bOrItemAccess)
{
	return (p_pReport + 1 < p_pEnd && p_pReport->llTokenId == BGI_IDENTIFIER && p_pReport[1].llTokenId == BGI_PARAMETER_LIST) || (p_bOrItemAccess && p_pReport[0].llTokenId == BGI_ITEM_ACCESS);
}

unsigned char BiaCompiler::HandleIdentifierAccess(const yu::interpret::SReport * p_pReport)
{
	unsigned char ucParameterCount = 0;

	//Loop through all parameter. Start at +1 because first element is "("
	for (auto i = p_pReport->pvTokenUnion->begin()._Ptr + 1, cond = p_pReport->pvTokenUnion->end()._Ptr; i < cond; ++i)
	{
		HandleValue(i, true);

		++ucParameterCount;
	}

	return ucParameterCount;
}

}
}
}