#pragma once

#include <unordered_set>

#include "biaAllocator.hpp"
#include "biaHash.hpp"


namespace bia
{
namespace machine
{

class BiaNameManager
{
public:
	/**
	 * Constructor.
	 *
	 * @param	[in]	p_pAllocator	Defines the memory allocator.
	*/
	BiaNameManager(BiaAllocator * p_pAllocator);
	BiaNameManager(BiaNameManager && p_move);
	BiaNameManager(const BiaNameManager&) = delete;
	~BiaNameManager();

	const char * GetNameAddress(const char * p_pcString, size_t p_iSize);
	const char * GetFormatAddress(const char * p_pcString, size_t p_iSize);

private:
	struct StringEntry
	{
		inline StringEntry(const char * p_pcString, size_t p_iSize)
		{
			pcString = p_pcString;
			iSize = p_iSize;
		}
		inline StringEntry(BiaAllocator::universal_allocation p_allocation)
		{
			pcString = static_cast<const char*>(p_allocation.pAddress);
			iSize = p_allocation.iSize;
		}

		const char * pcString;
		size_t iSize;

		inline bool operator==(const StringEntry & p_string) const
		{
			return iSize == p_string.iSize ? memcmp(pcString, p_string.pcString, iSize) == 0 : false;
		}
		inline BiaAllocator::universal_allocation GetAllocation() const
		{
			return { const_cast<char*>(pcString), iSize };
		}
	};

	struct StringHasher
	{
		inline size_t operator()(const StringEntry & p_string) const
		{
			return utility::BiaHasher<size_t>().operator()(p_string.pcString, p_string.iSize);
		}
	};

	BiaAllocator * m_pAllocator;	/**	Defines the memory allocator.	*/

	std::unordered_set<StringEntry, StringHasher> m_index;	/**	Defines the index holding all allocated names.	*/
};

}
}