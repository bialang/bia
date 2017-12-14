#pragma once

#include <stdint.h>

#include "biaMemberHolder.h"
#include "biaMachineContext.h"
#include "biaScopeElement.h"
#include "biaByteStream.h"
#include "biaException.h"
#include "biaOpCodes.h"
#include "biaKey.h"
#include "biaDouble.h"
#include "biaFloat.h"
#include "biaLong.h"
#include "biaString.h"
#include "biaConstChar.h"


namespace bia
{
namespace machine
{

class BiaMachineHelper
{
public:
	/**
	 * Executes a function call.
	 *
	 * @since	2.28.67.395
	 * @date	24-Jul-17
	 *
	 * @param   [in,out]	p_pContext	Defines the context.
	 * @param	p_bGlobal	Defines whether the function is defined globally or not.
	 *
	 * @throws	bia::exception::AccessViolationException	Thrown when the stack is accessed incorrectly.
	 * @throws	bia::exception::InvalidByteCodeException	Thrown when the byte code is invalid.
	*/
	inline static void ExecuteCall(BiaMachineContext * p_pContext, bool p_bGlobal)
	{
		//Get parameter list
		auto ucParamCount = p_pContext->m_pCode->Read<unsigned char>();
		auto pParameterBegin = p_pContext->m_stack.GetStackBasePointer(ucParamCount);
		auto pParameterEnd = p_pContext->m_stack.GetStackEndPointer();

		//Global
		if (p_bGlobal)
		{
			auto nResult = p_pContext->m_scope.GetVariable(LoadKeyToken(*p_pContext->m_pCode)).GetMemberHolder().GetMember()->Execute(p_pContext->m_accumulator.GetInitializationDestination(), nullptr, pParameterBegin, pParameterEnd, p_pContext);

			if (nResult >= 0)
			{
				if (nResult > 0)
				{
					p_pContext->m_accumulator.ConfirmInitialization();
					p_pContext->PromoteAccumulatorClass();
				}

				p_pContext->m_stack.PopParameters(ucParamCount);

				return;
			}
		}
		else
		{
			char acDestination[api::BiaParameter::GetArraySize()];
			auto nResult = p_pContext->m_accumulator.GetMember()->Call(LoadKeyToken(*p_pContext->m_pCode), acDestination, pParameterBegin, pParameterEnd);

			if (nResult >= 0)
			{
				if (nResult > 0)
				{
					memcpy(p_pContext->m_accumulator.GetInitializationDestination(), acDestination, sizeof(acDestination));
					p_pContext->m_accumulator.ConfirmInitialization();
					p_pContext->PromoteAccumulatorClass();
				}
				else
					p_pContext->m_accumulator.Clear();

				p_pContext->m_stack.PopParameters(ucParamCount);

				return;
			}
		}

		throw exception::SymbolException("Invalid function call.");
	}
	/**
	 * Instantiates an object.
	 *
	 * @since	2.38.81.467
	 * @date	09-Sep-17
	 *
	 * @param   [in,out]	p_pContext	Defines the context.
	 * @param	p_bGlobalTemplateTable	Defines whether the class template is global or not.
	 *
	 * @throws	bia::exception::ArgumentException	Thrown when the parameters for the instance are invalid.
	 * @throws	bia::exception::InvalidByteCode	Thrown when the byte code is invalid.
	 * @throws	bia::exception::AccessViolationException	Thrown when either the stack or the accumulator were accessed illegally.
	 * @throws	bia::exception::UnknownTemplateException	Thrown when the class template is unknown.
	*/
	inline static void ExecuteInstantiate(BiaMachineContext * p_pContext, bool p_bGlobalTemplateTable)
	{
		//Get parameter list
		auto ucParamCount = p_pContext->m_pCode->Read<unsigned char>();
		auto pParameterBegin = p_pContext->m_stack.GetStackBasePointer(ucParamCount);
		auto pParameterEnd = p_pContext->m_stack.GetStackEndPointer();

		if (p_bGlobalTemplateTable)
		{
			auto pTemplate = p_pContext->m_templates.GetTemplate(LoadKeyToken(*p_pContext->m_pCode));

			if (pTemplate)
			{
				if (!pTemplate->CreateInstance(p_pContext->m_accumulator.GetInitializationDestination(), pParameterBegin, pParameterEnd))
					throw exception::ArgumentException("Cannot instantiate. No matching constructor.");

				p_pContext->m_accumulator.ConfirmInitialization();

				//Pop parameters
				p_pContext->m_stack.PopParameters(ucParamCount);

				return;
			}
		}
		else
		{
			char acDestination[api::BiaParameter::GetArraySize()];
			auto nResult = p_pContext->m_accumulator.GetMember()->Call(LoadKeyToken(*p_pContext->m_pCode), acDestination, pParameterBegin, pParameterEnd);
			
			if (nResult > 0)
			{
				memcpy(p_pContext->m_accumulator.GetInitializationDestination(), acDestination, sizeof(acDestination));
				p_pContext->m_accumulator.ConfirmInitialization();

				//Pop parameters
				p_pContext->m_stack.PopParameters(ucParamCount);

				return;
			}
		}

		throw exception::UnknownTemplateException("Unknown template.");
	}
	/**
	 * Executes a range loop.
	 *
	 * @since	2.38.81.464
	 * @date	08-Sep-17
	 *
	 * @param   [in,out]	p_pContext	Defines the context.
	 *
	 * @throws	bia::exception::AccessViolationException	Thrown when the accumulator is empty.
	 * @throws	bia::exception::ArgumentException	Thrown when the types in the range are not the same.
	 * @throws	bia::exception::InvalidByteCodeException	Thrown when the byte code is invalid.
	*/
	template<typename T>
	inline static void ExecuteRangeLoop(BiaMachineContext * p_pContext)
	{
		if (p_pContext->m_accumulator.GetType() == api::BiaParameter::TYPE::NONE)
			throw exception::AccessViolationException("Empty accumulator for range loop is invalid.");

		api::BiaParameter variable(std::move(p_pContext->m_accumulator));
		auto end = p_pContext->m_pCode->Read<T>();
		auto step = p_pContext->m_pCode->Read<T>();
		auto uiLoopSize = p_pContext->m_pCode->Read<uint32_t>();
		auto code = *p_pContext->m_pCode;

		//Initialize iterator
		T * pIterator;

		if (!variable.GetMember()->Cast(pIterator))
			throw exception::ArgumentException("Invalid type for range.");

		//Execute
		for (; *pIterator < end; *pIterator += step)
		{
			//Reset loop
			*p_pContext->m_pCode = code;

			//Exexute loop
			ExecutionLoop(p_pContext, false);
		}

		//Skip loop
		p_pContext->m_pCode->pcCursor = code.pcCursor + uiLoopSize;
	}
	inline static void ExecutionLoop(BiaMachineContext * p_pContext, bool p_bBiaFunction)
	{
		//Main execution loop
		while (p_pContext->m_pCode->GoodToRead<21>())
		{
			//Read operation code
			switch (p_pContext->m_pCode->Read<machine::OP>())
			{
			case OP::TERMINATE:
				return;
			case OP::OBJECTIFY:
			{
				if (p_pContext->m_accumulator.GetType() == api::BiaParameter::TYPE::MEMBER)
					p_pContext->m_scope.AddVariable(LoadKeyToken(*p_pContext->m_pCode), p_pContext->m_accumulator.MoveMemberHolder(), p_bBiaFunction);
				else
					p_pContext->m_scope.AddVariable(LoadKeyToken(*p_pContext->m_pCode), p_pContext->m_accumulator.MoveScopeReference(), p_bBiaFunction);

				break;
			}
			case OP::OBJECTIFY_MULTIPLE:
			{
				auto ucAdditional = p_pContext->m_pCode->Read<uint8_t>();
				auto reference = p_pContext->m_accumulator.GetType() == api::BiaParameter::TYPE::MEMBER ? p_pContext->m_scope.AddVariable(LoadKeyToken(*p_pContext->m_pCode), p_pContext->m_accumulator.MoveMemberHolder(), p_bBiaFunction) : p_pContext->m_scope.AddVariable(LoadKeyToken(*p_pContext->m_pCode), p_pContext->m_accumulator.MoveScopeReference(), p_bBiaFunction);

				//Create additional
				while (ucAdditional--)
					p_pContext->m_scope.AddVariable(LoadKeyToken(*p_pContext->m_pCode), reference, p_bBiaFunction);

				break;
			}
			case OP::INSTANTIATE:
			{
				ExecuteInstantiate(p_pContext, true);

				break;
			}
			case OP::INSTANTIATE_ACCUMULATOR:
			{
				ExecuteInstantiate(p_pContext, false);

				break;
			}
			case OP::INCREMENT:
			{
				if (!p_pContext->m_accumulator.GetMember()->Inc())
					throw exception::SymbolException("Invalid increment operation.");

				break;
			}
			case OP::DECREMENT:
			{
				if (!p_pContext->m_accumulator.GetMember()->Dec())
					throw exception::SymbolException("Invalid decrement operation.");

				break;
			}
			case OP::STORE:
			{
				if (!p_pContext->m_accumulator.GetMember()->Store(p_pContext->m_stack.GetStackBasePointer(1)->GetMember()))
					throw exception::SymbolException("Cannot store specified value.");

				p_pContext->m_stack.PopParameters(1);

				break;
			}
			case OP::LOAD:
			{
				p_pContext->m_accumulator = LoadObject(p_pContext, true, LoadKeyToken(*p_pContext->m_pCode));

				break;
			}
			case OP::LOAD_COPY:
			{
				if (!LoadObject(p_pContext, true, LoadKeyToken(*p_pContext->m_pCode)).GetMemberHolder().GetMember()->Clone(p_pContext->m_accumulator.GetCloningDestination()))
				{
					p_pContext->m_accumulator.CancelCloning();

					throw exception::AccessViolationException("Cannot clone object.");
				}

				break;
			}
			case OP::LOAD_FROM_ACCUMULATOR:
			{
				p_pContext->m_accumulator = LoadObject(p_pContext, false, LoadKeyToken(*p_pContext->m_pCode));

				break;
			}
			case OP::LOAD_LONG:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<long long>>(p_pContext->m_pCode->Read<long long>());

				break;
			}
			case OP::LOAD_LONG_0:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<long long>>(0ll);

				break;
			}
			case OP::LOAD_LONG_N1:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<long long>>(-1ll);

				break;
			}
			case OP::LOAD_LONG_1:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<long long>>(1ll);

				break;
			}
			case OP::LOAD_LONG_2:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<long long>>(2ll);

				break;
			}
			case OP::LOAD_LONG_3:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<long long>>(3ll);

				break;
			}
			case OP::LOAD_LONG_5:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<long long>>(5ll);

				break;
			}
			case OP::LOAD_LONG_10:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<long long>>(10ll);

				break;
			}
			case OP::LOAD_LONG_100:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<long long>>(100ll);

				break;
			}
			case OP::LOAD_LONG_1000:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<long long>>(1000ll);

				break;
			}
			case OP::LOAD_LONG_1000000:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<long long>>(1000000ll);

				break;
			}
			case OP::LOAD_FLOAT:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<float>>(p_pContext->m_pCode->Read<float>());

				break;
			}
			case OP::LOAD_FLOAT_0:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<float>>(0.0f);

				break;
			}
			case OP::LOAD_FLOAT_N1:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<float>>(-1.0f);

				break;
			}
			case OP::LOAD_FLOAT_1:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<float>>(1.0f);

				break;
			}
			case OP::LOAD_DOUBLE:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<double>>(p_pContext->m_pCode->Read<double>());

				break;
			}
			case OP::LOAD_DOUBLE_0:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<double>>(0.0);

				break;
			}
			case OP::LOAD_DOUBLE_N1:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<double>>(-1.0);

				break;
			}
			case OP::LOAD_DOUBLE_1:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<double>>(1.0);
				
				break;
			}
			case OP::LOAD_STRING:
			{
				auto iLength = static_cast<size_t>(p_pContext->m_pCode->Read<uint32_t>());
				
				if (p_pContext->m_pCode->pcCursor + iLength > p_pContext->m_pCode->pcByteCodeEnd)
					throw exception::InvalidByteCodeException("Invalid string length.");

				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<std::string>>(reinterpret_cast<const char*>(p_pContext->m_pCode->pcCursor), iLength);
				p_pContext->m_pCode->pcCursor += iLength;

				break;
			}
			case OP::LOAD_STRING_EMPTY:
			{
				p_pContext->m_accumulator.Initialize<api::framework::native::BiaNativeVariable<std::string>>(static_cast<const char*>(""), 0);

				break;
			}
			case OP::PUSH_ACCUMULATOR:
			{
				//Push accumulator
				p_pContext->m_stack += std::move(p_pContext->m_accumulator);

				break;
			}
			case OP::PUSH:
			{
				//Push object
				p_pContext->m_stack += LoadObject(p_pContext, true, LoadKeyToken(*p_pContext->m_pCode));

				break;
			}
			case OP::PUSH_COPY:
			{
				if (!LoadObject(p_pContext, true, LoadKeyToken(*p_pContext->m_pCode)).GetMemberHolder().GetMember()->Clone(p_pContext->m_stack.GetAndPush()->GetCloningDestination()))
				{
					p_pContext->m_accumulator.CancelCloning();

					throw exception::AccessViolationException("Cannot clone object.");
				}

				break;
			}
			case OP::PUSH_LONG:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<long long>>(p_pContext->m_pCode->Read<long long>());

				break;
			}
			case OP::PUSH_LONG_0:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<long long>>(0ll);

				break;
			}
			case OP::PUSH_LONG_N1:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<long long>>(-1ll);

				break;
			}
			case OP::PUSH_LONG_1:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<long long>>(1ll);

				break;
			}
			case OP::PUSH_LONG_2:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<long long>>(2ll);

				break;
			}
			case OP::PUSH_LONG_3:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<long long>>(3ll);

				break;
			}
			case OP::PUSH_LONG_5:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<long long>>(5ll);

				break;
			}
			case OP::PUSH_LONG_10:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<long long>>(10ll);

				break;
			}
			case OP::PUSH_LONG_100:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<long long>>(100ll);

				break;
			}
			case OP::PUSH_LONG_1000:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<long long>>(1000ll);

				break;
			}
			case OP::PUSH_LONG_1000000:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<long long>>(1000000ll);

				break;
			}
			case OP::PUSH_FLOAT:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<float>>(p_pContext->m_pCode->Read<float>());

				break;
			}
			case OP::PUSH_FLOAT_0:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<float>>(0.0f);

				break;
			}
			case OP::PUSH_FLOAT_N1:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<float>>(-1.0f);

				break;
			}
			case OP::PUSH_FLOAT_1:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<float>>(1.0f);

				break;
			}
			case OP::PUSH_DOUBLE:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<double>>(p_pContext->m_pCode->Read<double>());

				break;
			}
			case OP::PUSH_DOUBLE_0:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<double>>(0.0);

				break;
			}
			case OP::PUSH_DOUBLE_N1:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<double>>(-1.0);

				break;
			}
			case OP::PUSH_DOUBLE_1:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<double>>(1.0);

				break;
			}
			case OP::PUSH_STRING:
			{
				auto unSize = p_pContext->m_pCode->Read<uint32_t>();

				//Read buffer
				if (p_pContext->m_pCode->pcCursor + unSize + 1 > p_pContext->m_pCode->pcByteCodeEnd)
					throw exception::InvalidByteCodeException("Invalid string parameter.");

				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<const char*>>(reinterpret_cast<const char*>(p_pContext->m_pCode->pcCursor));
				p_pContext->m_pCode->pcCursor += unSize + 1;

				break;
			}
			case OP::PUSH_STRING_EMPTY:
			{
				p_pContext->m_stack.GetAndPush()->Initialize<api::framework::native::BiaNativeVariable<const char*>>(EMPTY_STRING);

				break;
			}
			case OP::CALL:
			{
				ExecuteCall(p_pContext, false);

				break;
			}
			case OP::CALL_GLOBAL:
			{
				ExecuteCall(p_pContext, true);

				break;
			}
			case OP::CALL_OPERATOR:
			{
				char acDestination[sizeof(api::framework::BiaMemberHolder)];
				auto nResult = p_pContext->m_accumulator.GetMember()->Operator(p_pContext->m_pCode->Read<unsigned int>(), acDestination, p_pContext->m_stack.GetStackBasePointer(1)->GetMember());

				if (nResult >= 0)
				{
					if (nResult > 0)
					{
						memcpy(p_pContext->m_accumulator.GetInitializationDestination(), acDestination, sizeof(acDestination));
						p_pContext->m_accumulator.ConfirmInitialization();
					}

					p_pContext->m_stack.PopParameters(1);
				}
				else
					throw exception::SymbolException("Invalid operator operation.");

				break;
			}
			case OP::JUMP_CONDITIONAL:
			{
				if (!p_pContext->m_accumulator.GetMember()->Conditional())
				{
					if (!p_pContext->m_pCode->SeekRead(p_pContext->m_pCode->TellRead() + 8))
						throw exception::BadByteCodeException("Bad op code parameter.");

					break;
				}

				goto gt_jump;
			}
			case OP::JUMP_CONDITIONAL_NOT:
			{
				if (p_pContext->m_accumulator.GetMember()->Conditional())
				{
					if (!p_pContext->m_pCode->SeekRead(p_pContext->m_pCode->TellRead() + 8))
						throw exception::BadByteCodeException("Bad op code parameter.");

					break;
				}
			}
			case OP::JUMP:
			{
			gt_jump:;
				auto llOffset = p_pContext->m_pCode->Read<long long>();

				if (!p_pContext->m_pCode->SeekRead(llOffset + p_pContext->m_pCode->TellRead()))
					throw exception::BadByteCodeException("Invalid jump offset.");

				break;
			}
			case OP::PRINT_OBJECT:
			{
				//Print object
				LoadObject(p_pContext, true, LoadKeyToken(*p_pContext->m_pCode)).GetMemberHolder().GetMember()->Print();
				putchar('\n');

				break;
			}
			case OP::PRINT_ACCUMULATOR:
			{
				//Print accumulator
				p_pContext->m_accumulator.GetMember()->Print();
				putchar('\n');

				break;
			}
			/*case OP::DEFINE_FUNCTION:
			{
				DefineFunction(p_pContext, p_bBiaFunction);

				break;
			}*/
			case OP::RETURN:
				p_pContext->m_accumulator = LoadObject(p_pContext, true, LoadKeyToken(*p_pContext->m_pCode));
			case OP::RETURN_ACCUMULATOR:
				return;
			case OP::RETURN_VOID:
			{
				p_pContext->m_accumulator.Clear();

				return;
			}
			//case OP::DELETE:
			//{
			//	//Read variable name
			//	LoadNameFromBuffer(*p_pContext->m_pCode, p_pContext->m_stNameBuffer);

			//	auto pResult = p_pContext->m_scopeIndex.find(p_pContext->m_stNameBuffer);
			//	
			//	if (pResult != p_pContext->m_scopeIndex.end())
			//	{
			//		pResult->second.back()->GetLink()->pElement
			//		if (pResult->second.size() > 1)
			//			pResult->second.pop_back();
			//		else
			//			p_pContext->m_scopeIndex.erase(pResult);
			//	}

			//	break;
			//}
			case OP::IMPORT:
			{
				//Read import module
				if (!ImportModule(p_pContext))
					throw exception::ArgumentException("Specified module not found.");

				break;
			}
			case OP::RANGE_END:
				return;
			case OP::RANGE_LONG:
			{
				ExecuteRangeLoop<long long>(p_pContext);

				break;
			}
			case OP::RANGE_DOUBLE:
			{
				ExecuteRangeLoop<double>(p_pContext);

				break;
			}
			case OP::RANGE_FLOAT:
			{
				ExecuteRangeLoop<float>(p_pContext);

				break;
			}
			default:
				throw exception::InvalidByteCodeException("Unknown operation code.");
			}
		}
	}
	/**
	 * Imports a module specified in the byte code.
	 *
	 * @since	2.38.81.467
	 * @date	09-Sep-17
	 *
	 * @param   [in,out]	p_pContext	Defines the context.
	 *
	 * @throws	bia::exception::InvalidByteCodeException	Thrown when the byte code is invalid.
	 *
	 * @return  true if it succeeds, otherwise false.
	*/
	BIA_API static bool ImportModule(BiaMachineContext * p_pContext);
	/**
	 * Loads a key token from the byte stream.
	 *
	 * @since	2.21.57.341
	 * @date	18-Jul-17
	 *
	 * @param   [in,out]	p_byteCode	Defines the stream.
	 *
	 * @throws	bia::exception::InvalidByteCode	Thrown when the byte code is invalid.
	*/
	inline static BiaKeyToken LoadKeyToken(stream::BiaByteStream & p_byteCode)
	{
		BiaKeyToken keyToken;

		keyToken.unHash64 = p_byteCode.Read<uint64_t>();
		keyToken.unHash32 = p_byteCode.Read<uint32_t>();
		keyToken.ucLength = p_byteCode.Read<uint8_t>();

		if (p_byteCode.pcCursor + keyToken.ucLength > p_byteCode.pcByteCodeEnd)
			throw exception::InvalidByteCodeException("Invalid name parameter.");

		keyToken.pcString = reinterpret_cast<const char*>(p_byteCode.pcCursor);
		p_byteCode.pcCursor += keyToken.ucLength;

		return keyToken;
	}
	/**
	 * Loads an object.
	 *
	 * @since	2.38.81.467
	 * @date	09-Sep-17
	 *
	 * @param   [in,out]	p_pContext	Defines the context.
	 * @param	p_bGlobalObject	Defines whether the object is a global or a member object.
	 * @param	p_name	Defines the name of the object.
	 *
	 * @throws	bia::exception::SymbolException	Thrown when the object is unknown.
	 * @throws	bia::exception::AccessViolationException	Thrown when the a member object was requested but the accumulator was empty.
	 *
	 * @return  A reference to the object.
	*/
	inline static scope::BiaScopeReference LoadObject(BiaMachineContext * p_pContext, bool p_bGlobalObject, const BiaKey & p_name)
	{
		//Load from global object
		if (p_bGlobalObject)
			return p_pContext->m_scope.GetVariable(p_name);
		//Load from accumulator
		else
		{
			char acReference[sizeof(scope::BiaScopeReference)];

			if (p_pContext->m_accumulator.GetMember()->LoadObject(p_name, acReference))
				return std::move(*reinterpret_cast<scope::BiaScopeReference*>(acReference));
		}

		throw exception::SymbolException("Unknown variable.");
	}

private:
	constexpr static const char * EMPTY_STRING = "";
};

}
}