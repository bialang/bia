#include "biaDisassembler.h"
#include "biaOpCodes.h"

#include <string>


namespace bia
{
namespace machine
{
namespace debug
{

template<typename T>
inline std::string & ReadBuffer(stream::BiaByteStream & p_byteCode, std::string & p_stBuffer)
{
	if (std::is_same<T, unsigned char>::value)
		p_byteCode.pcCursor += 12;

	T size = p_byteCode.Read<T>();

	p_stBuffer.resize(size);

	if (!p_byteCode.Read(&p_stBuffer[0], size))
		throw 0;

	return p_stBuffer;
}

void BiaDisassembler::DisassembleByteCode(stream::BiaByteStream p_byteCode)
{
	puts("\n\n===================DISASSEMBLY===================");

	const auto pszIndent = "\t";
	std::string stBuffer;

	try
	{
		while (p_byteCode.GoodToRead<21>())
		{
			//Read operation code
			auto opCode = p_byteCode.Read<OP>();

			printf("0x%08x\t", static_cast<unsigned int>(p_byteCode.TellRead() - 1));

			switch (opCode)
			{
			case OP::TERMINATE:
			{
				puts("end");

				break;
			}
			case OP::OBJECTIFY:
			{
				printf("objtfy%s%s\n", pszIndent, ReadBuffer<unsigned char>(p_byteCode, stBuffer).c_str());

				break;
			}
			case OP::INSTANTIATE:
			{
				printf("inst%s%hu\t", pszIndent, p_byteCode.Read<unsigned char>());
				printf("%s\n", ReadBuffer<unsigned char>(p_byteCode, stBuffer).c_str());

				break;
			}
			case OP::INSTANTIATE_ACCUMULATOR:
			{
				printf("insta%s%hu\t", pszIndent, p_byteCode.Read<unsigned char>());
				printf("%s\n", ReadBuffer<unsigned char>(p_byteCode, stBuffer).c_str());

				break;
			}
			case OP::INCREMENT:
			{
				puts("inc");

				break;
			}
			case OP::DECREMENT:
			{
				puts("dec");

				break;
			}
			case OP::STORE:
			{
				puts("store");

				break;
			}
			case OP::LOAD:
			{
				printf("load%s%s\n", pszIndent, ReadBuffer<unsigned char>(p_byteCode, stBuffer).c_str());

				break;
			}
			case OP::LOAD_COPY:
			{
				printf("loadc%s%s\n", pszIndent, ReadBuffer<unsigned char>(p_byteCode, stBuffer).c_str());

				break;
			}
			case OP::LOAD_FROM_ACCUMULATOR:
			{
				printf("loada%s%s\n", pszIndent, ReadBuffer<unsigned char>(p_byteCode, stBuffer).c_str());

				break;
			}
			case OP::LOAD_LONG:
			{
				printf("loadl%s%lli\n", pszIndent, p_byteCode.Read<long long>());

				break;
			}
			case OP::LOAD_LONG_0:
			{
				puts("loadl_0");

				break;
			}
			case OP::LOAD_LONG_N1:
			{
				puts("loadl_-1");

				break;
			}
			case OP::LOAD_LONG_1:
			{
				puts("loadl_1");

				break;
			}
			case OP::LOAD_LONG_2:
			{
				puts("loadl_2");

				break;
			}
			case OP::LOAD_LONG_3:
			{
				puts("loadl_3");

				break;
			}
			case OP::LOAD_LONG_5:
			{
				puts("loadl_5");

				break;
			}
			case OP::LOAD_LONG_10:
			{
				puts("loadl_10");

				break;
			}
			case OP::LOAD_LONG_100:
			{
				puts("loadl_100");

				break;
			}
			case OP::LOAD_LONG_1000:
			{
				puts("loadl_1000");

				break;
			}
			case OP::LOAD_LONG_1000000:
			{
				puts("loadl_1000000");

				break;
			}
			case OP::LOAD_FLOAT:
			{
				printf("loadf%s%f\n", pszIndent, p_byteCode.Read<float>());

				break;
			}
			case OP::LOAD_FLOAT_0:
			{
				puts("loadf_0");

				break;
			}
			case OP::LOAD_FLOAT_N1:
			{
				puts("loadf_-1");

				break;
			}
			case OP::LOAD_FLOAT_1:
			{
				puts("loadf_1");

				break;
			}
			case OP::LOAD_DOUBLE:
			{
				printf("loadd%s%f\n", pszIndent, p_byteCode.Read<double>());

				break;
			}
			case OP::LOAD_DOUBLE_0:
			{
				puts("loadd_0");

				break;
			}
			case OP::LOAD_DOUBLE_N1:
			{
				puts("loadd_-1");

				break;
			}
			case OP::LOAD_DOUBLE_1:
			{
				puts("loadd_1");

				break;
			}
			case OP::LOAD_STRING:
			{
				printf("loads%s%s\n", pszIndent, ReadBuffer<uint32_t>(p_byteCode, stBuffer).c_str());

				break;
			}
			case OP::LOAD_STRING_EMPTY:
			{
				puts("loads_empty");

				break;
			}
			case OP::PUSH_ACCUMULATOR:
			{
				puts("pusha");

				break;
			}
			case OP::PUSH:
			{
				printf("push%s%s\n", pszIndent, ReadBuffer<unsigned char>(p_byteCode, stBuffer).c_str());

				break;
			}
			case OP::PUSH_COPY:
			{
				printf("pushc%s%s\n", pszIndent, ReadBuffer<unsigned char>(p_byteCode, stBuffer).c_str());

				break;
			}
			case OP::PUSH_LONG:
			{
				printf("pushl%s%lli\n", pszIndent, p_byteCode.Read<long long>());

				break;
			}
			case OP::PUSH_LONG_0:
			{
				puts("pushl_0");

				break;
			}
			case OP::PUSH_LONG_N1:
			{
				puts("pushl_-1");

				break;
			}
			case OP::PUSH_LONG_1:
			{
				puts("pushl_1");

				break;
			}
			case OP::PUSH_LONG_2:
			{
				puts("pushl_2");

				break;
			}
			case OP::PUSH_LONG_3:
			{
				puts("pushl_3");

				break;
			}
			case OP::PUSH_LONG_5:
			{
				puts("pushl_5");

				break;
			}
			case OP::PUSH_LONG_10:
			{
				puts("pushl_10");

				break;
			}
			case OP::PUSH_LONG_100:
			{
				puts("pushl_100");

				break;
			}
			case OP::PUSH_LONG_1000:
			{
				puts("pushl_1000");

				break;
			}
			case OP::PUSH_LONG_1000000:
			{
				puts("pushl_1000000");

				break;
			}
			case OP::PUSH_FLOAT:
			{
				printf("pushf%s%f\n", pszIndent, p_byteCode.Read<float>());

				break;
			}
			case OP::PUSH_FLOAT_0:
			{
				puts("pushf_0");

				break;
			}
			case OP::PUSH_FLOAT_N1:
			{
				puts("pushf_-1");

				break;
			}
			case OP::PUSH_FLOAT_1:
			{
				puts("pushf_1");

				break;
			}
			case OP::PUSH_DOUBLE:
			{
				printf("pushd%s%lf\n", pszIndent, p_byteCode.Read<double>());

				break;
			}
			case OP::PUSH_DOUBLE_0:
			{
				puts("pushd_0");

				break;
			}
			case OP::PUSH_DOUBLE_N1:
			{
				puts("pushd_-1");

				break;
			}
			case OP::PUSH_DOUBLE_1:
			{
				puts("pushd_1");

				break;
			}
			case OP::PUSH_STRING:
			{
				printf("pushs%s%s\n", pszIndent, ReadBuffer<uint32_t>(p_byteCode, stBuffer).c_str());
				++p_byteCode.pcCursor;

				break;
			}
			case OP::PUSH_STRING_EMPTY:
			{
				puts("pushs_empty");

				break;
			}
			case OP::CALL:
			{
				printf("call%s%hu\t", pszIndent, p_byteCode.Read<unsigned char>());
				printf("%s\n", ReadBuffer<unsigned char>(p_byteCode, stBuffer).c_str());

				break;
			}
			case OP::CALL_GLOBAL:
			{
				printf("callg%s%hu\t", pszIndent, p_byteCode.Read<unsigned char>());
				printf("%s\n", ReadBuffer<unsigned char>(p_byteCode, stBuffer).c_str());

				break;
			}
			case OP::CALL_OPERATOR:
			{
				char acBuf[5]{};

				p_byteCode.Read(acBuf, 4);

				printf("callo%s%s\n", pszIndent, acBuf);

				break;
			}
			case OP::JUMP_CONDITIONAL:
			{
				fputs("jmpc", stdout);

				goto gt_write_location;
			}
			case OP::JUMP_CONDITIONAL_NOT:
			{
				fputs("jmpn", stdout);

				goto gt_write_location;
			}
			case OP::JUMP:
			{
				fputs("jmp", stdout);

			gt_write_location:;
				auto llOffset = p_byteCode.Read<long long>();

				printf("%s0x%08x\n", pszIndent, static_cast<unsigned int>(llOffset + p_byteCode.TellRead()));

				break;
			}
			case OP::PRINT_OBJECT:
			{
				printf("printo%s%s\n", pszIndent, ReadBuffer<unsigned char>(p_byteCode, stBuffer).c_str());

				break;
			}
			case OP::PRINT_ACCUMULATOR:
			{
				printf("printa\n");

				break;
			}
			case OP::DEFINE_FUNCTION:
			{
				auto pszName = ReadBuffer<unsigned char>(p_byteCode, stBuffer).c_str();
				auto unSize = p_byteCode.Read<unsigned int>();

				printf("def%s%s\t%u\n", pszIndent, pszName, unSize);

				break;
			}
			case OP::MAKE_PARAMETER:
			{
				printf("make%s%s\n", pszIndent, ReadBuffer<unsigned char>(p_byteCode, stBuffer).c_str());

				break;
			}
			case OP::RETURN:
			{
				printf("return%s%s\n", pszIndent, ReadBuffer<unsigned char>(p_byteCode, stBuffer).c_str());

				break;
			}
			case OP::RETURN_ACCUMULATOR:
			{
				puts("returna");

				break;
			}
			case OP::RETURN_VOID:
			{
				puts("returnv");

				break;
			}
			//case OP::DELETE:
			{
				printf("del%s%s\n", pszIndent, ReadBuffer<unsigned char>(p_byteCode, stBuffer).c_str());

				break;
			}
			case OP::IMPORT:
			{
				printf("imprt%s%s\t", pszIndent, ReadBuffer<unsigned short>(p_byteCode, stBuffer).c_str());

				p_byteCode.pcCursor++;

				//Alias
				auto ucTmp = p_byteCode.Read<unsigned char>();

				if (ucTmp)
				{
					if (p_byteCode.pcCursor + ucTmp + 1 > p_byteCode.pcByteCodeEnd)
						throw 0;

					fwrite(p_byteCode.pcCursor, 1, ucTmp, stdout);
					p_byteCode.pcCursor += ucTmp;
				}
				else
					fputs("-\t", stdout);

				++p_byteCode.pcCursor;

				//Specific
				ucTmp = p_byteCode.Read<unsigned char>();

				if (ucTmp)
				{
					if (p_byteCode.pcCursor + ucTmp > p_byteCode.pcByteCodeEnd)
						throw 0;

					fwrite(p_byteCode.pcCursor, 1, ucTmp, stdout);
					p_byteCode.pcCursor += ucTmp;
				}
				else
					fputs("-", stdout);

				
				putchar('\n');

				break;
			}
			case OP::RANGE_END:
			{
				puts("range_end");

				break;
			}
			case OP::RANGE_LONG:
			{
				auto llEnd = p_byteCode.Read<long long>();
				auto llStep = p_byteCode.Read<long long>();
				auto uiSize = p_byteCode.Read<uint32_t>();

				printf("rngl%s%lli\t%lli\t0x%08x\n", pszIndent, llEnd, llStep, static_cast<unsigned int>(uiSize + p_byteCode.TellRead()));

				break;
			}
			case OP::RANGE_DOUBLE:
			{
				auto rEnd = p_byteCode.Read<double>();
				auto rStep = p_byteCode.Read<double>();
				auto uiSize = p_byteCode.Read<uint32_t>();

				printf("rngl%s%f\t%f\t0x%08x\n", pszIndent, rEnd, rStep, static_cast<unsigned int>(uiSize + p_byteCode.TellRead()));

				break;
			}
			case OP::RANGE_FLOAT:
			{
				auto rEnd = p_byteCode.Read<float>();
				auto rStep = p_byteCode.Read<float>();
				auto uiSize = p_byteCode.Read<uint32_t>();

				printf("rngl%s%f\t%f\t0x%08x\n", pszIndent, rEnd, rStep, static_cast<unsigned int>(uiSize + p_byteCode.TellRead()));

				break;
			}
			default:
				puts("Unknown operation code.");

				goto gt_end;
			}
		}
	}
	catch (...)
	{
		puts("\nInvalid byte code.");
	}

gt_end:;	
	puts("===================DISASSEMBLY===================\n\n");
}

}
}
}