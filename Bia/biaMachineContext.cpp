#include "biaMachineContext.hpp"
#include "biaOutputStreamBuffer.hpp"
#include "biaCompiler.hpp"
#include "biaGrammar.hpp"
#include "biaUndefined.hpp"

#include <memory>
#include <cstdint>


namespace bia
{
namespace machine
{

BiaMachineContext::BiaMachineContext(std::shared_ptr<BiaAllocator> p_pAllocator) : m_pAllocator(std::move(p_pAllocator)), m_nameManager(m_pAllocator.get())
{
}

BiaMachineContext::~BiaMachineContext()
{
	for (auto & member : m_index)
		m_pAllocator->DestroyBlocks(member.second, BiaAllocator::MEMORY_TYPE::NORMAL);
}

bool BiaMachineContext::SetScript(std::string p_stScriptName, const char * p_pcScript, size_t p_iSize)
{
	auto machineCode = CompileScript(p_pcScript, p_iSize);

	if (!machineCode.IsValid())
		return false;

	//Set script
#if defined(BIA_CPP_17)
	m_scripts.insert_or_assign(std::move(p_stScriptName), std::move(machineCode));
#else
	m_scripts[std::move(p_stScriptName)] = std::move(machineCode);
#endif

	return true;
}

bool BiaMachineContext::Execute(const char * p_pcScript, size_t p_iSize)
{
	auto machineCode = CompileScript(p_pcScript, p_iSize);

	if (!machineCode.IsValid())
		return false;

	//Execute
	machineCode.Execute();

	return true;
}

bool BiaMachineContext::ExecuteScript(const std::string & p_stScriptName)
{
	auto pResult = m_scripts.find(p_stScriptName);

	if (pResult == m_scripts.end())
		return false;

	//Execute
	pResult->second.Execute();

	return true;
}

BiaMachineCode * BiaMachineContext::GetScript(const std::string & p_stScriptName)
{
	auto pResult = m_scripts.find(p_stScriptName);

	return pResult == m_scripts.end() ? nullptr : &pResult->second;
}

framework::BiaMember * BiaMachineContext::GetGlobal(const std::string & p_stVariable)
{
	auto pResult = m_index.find(p_stVariable);

	//Address found
	return pResult != m_index.end() ? pResult->second.pAddress : nullptr;
}

void BiaMachineContext::ConstructTemporaryAddresses(int8_t p_cCount, framework::BiaMember ** p_ppDestination)
{
	auto blocks = m_pAllocator->AllocateBlocks(p_cCount, BiaAllocator::MEMORY_TYPE::NORMAL);
	auto pBlocks = static_cast<int8_t*>(blocks.pAddress);
	printf("construct %p\n", p_ppDestination);

	for (int8_t i = 0; i < p_cCount; ++i)
	{
		p_ppDestination[i] = new(pBlocks + i * BiaAllocator::BLOCK_SIZE) framework::BiaUndefined();

		printf("Allocated: %p\n", p_ppDestination[i]);
	}
}

void BiaMachineContext::DestructTemporaryAddresses(int8_t p_cCount, framework::BiaMember ** p_ppAddresses)
{
	printf("destroy %p\n", p_ppAddresses);

	for (int8_t i = 0; i < p_cCount; ++i)
	{
		printf("Deallocated: %p\n", p_ppAddresses[i]);

		p_ppAddresses[i]->~BiaMember();

	}

	m_pAllocator->DeallocateBlocks({ *p_ppAddresses, static_cast<size_t>(p_cCount) }, BiaAllocator::MEMORY_TYPE::NORMAL);
}

const char * BiaMachineContext::NameAddressOf(const char * p_pcName, size_t p_iSize)
{
	return m_nameManager.GetNameAddress(p_pcName, p_iSize);
}

const char * BiaMachineContext::FormatAddressOf(const char * p_pcName, size_t p_iSize)
{
	return m_nameManager.GetFormatAddress(p_pcName, p_iSize);
}

const char * BiaMachineContext::StringAddressOf(std::string p_stString)
{
	return "hi";
}

framework::BiaMember * BiaMachineContext::AddressOf(StringKey p_name)
{
	auto pResult = m_index.find(p_name);

	//Address found
	if (pResult != m_index.end())
		return pResult->second.pAddress;
	//Create address
	else
	{
		auto allocation = m_pAllocator->ConstructBlocks<framework::BiaMember, framework::BiaUndefined>(1, BiaAllocator::MEMORY_TYPE::NORMAL);
		//auto pAddress = m_storage.CreateElement<framework::BiaUndefined>();

		m_index.insert({ p_name, allocation });

		return allocation.pAddress;
	}
}

BiaMachineCode BiaMachineContext::CompileScript(const void * p_pScript, size_t p_iSize)
{
	BiaMachineSchein machineSchein(m_pAllocator.get());
	stream::BiaOutputStreamBuffer compiled;

	//Interpret and compile
	{
		compiler::BiaCompiler compiler(compiled, *this, m_pAllocator.get());

		grammar::BiaGrammar::GetGrammar().Interpret(static_cast<const char*>(p_pScript), p_iSize, compiler);

		machineSchein = compiler.GetMachineSchein();
	}

	//Make the compiled buffer executable
	return BiaMachineCode(compiled.GetBuffer(), std::move(machineSchein));
}

}
}