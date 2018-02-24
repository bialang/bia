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

void BiaMachineContext::Run(const void * p_pScript, size_t p_iSize)
{
	int8_t acMachineScheinSpace[sizeof(BiaMachineSchein)];

	std::unique_ptr<BiaMachineSchein, void(*)(BiaMachineSchein*)> pMachineSchein(nullptr, [](BiaMachineSchein * p_pMachineSchein) {
		p_pMachineSchein->~BiaMachineSchein();
	});
	stream::BiaOutputStreamBuffer compiled;

	//Interpret and compile
	{
		compiler::BiaCompiler compiler(compiled, *this, m_pAllocator.get());

		grammar::BiaGrammar::GetGrammar().Interpret(static_cast<const char*>(p_pScript), p_iSize, compiler);

		pMachineSchein.reset(new(acMachineScheinSpace) BiaMachineSchein(compiler.GetMachineSchein()));
	}

	//Make the compiled buffer executable
	BiaMachineCode code(compiled.GetBuffer(), std::move(*pMachineSchein));

	//Execute script
	if (code.IsValid())
		code.Execute();
}

framework::BiaMember * BiaMachineContext::GetGlobal(const std::string & p_stVariable)
{
	auto pResult = m_index.find(p_stVariable);

	//Address found
	return pResult != m_index.end() ? pResult->second : nullptr;
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

const char * BiaMachineContext::StringAddressOf(std::string p_stString)
{
	return "dummy";
}

framework::BiaMember * BiaMachineContext::AddressOf(StringKey p_name)
{
	auto pResult = m_index.find(p_name);

	//Address found
	if (pResult != m_index.end())
		return pResult->second;
	//Create address
	else
	{
		auto pAddress = static_cast<framework::BiaMember*>(m_pAllocator->ConstructBlocks<framework::BiaUndefined>(1, BiaAllocator::MEMORY_TYPE::NORMAL).pAddress);
		//auto pAddress = m_storage.CreateElement<framework::BiaUndefined>();

		m_index.insert({ p_name, pAddress });

		return pAddress;
	}
}

}
}