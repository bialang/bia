#include "biaMachineContext.hpp"
#include "biaOutputStreamBuffer.hpp"
#include "biaUndefined.hpp"

#include <memory>
#include <cstdint>


namespace bia
{
namespace machine
{

void BiaMachineContext::Run(stream::BiaInputStream & p_input)
{
	uint8_t aucSpace[sizeof(BiaMachineCode)];
	std::unique_ptr<BiaMachineCode, void(*)(BiaMachineCode*)> pMachineCode(nullptr, [](BiaMachineCode * p_pCode) {
		p_pCode->~BiaMachineCode();
	});

	{
		//Compile
		stream::BiaOutputStreamBuffer compiled;

		//Make the compiled buffer executable
		pMachineCode.reset(new(aucSpace) BiaMachineCode(compiled.GetBuffer()));
	}

	//Execute script
	if (pMachineCode->IsValid())
		pMachineCode->Execute();
}

void BiaMachineContext::ConstructTemporaryAddresses(int8_t p_cCount, framework::BiaMember ** p_ppDestination)
{
	printf("construct %p\n", p_ppDestination);

	for (int8_t i = 0; i < p_cCount; ++i)
	{
		p_ppDestination[i] = new(malloc(50)) framework::BiaUndefined();

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

		free(p_ppAddresses[i]);
	}
}

const char * BiaMachineContext::StringAddressOf(std::string p_stString)
{
	auto pResult = m_stringAddresses.find(p_stString);

	//Not found
	if (pResult == m_stringAddresses.end())
		pResult = m_stringAddresses.insert(std::move(p_stString)).first;

	return pResult->data();
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
		auto pAddress = m_storage.CreateElement<framework::BiaUndefined>();

		m_index.insert({ p_name, pAddress });

		return pAddress;
	}
}

}
}