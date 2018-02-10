#pragma once

#include <unordered_set>

#include "biaAllocator.hpp"


namespace bia
{
namespace machine
{

class BiaStringManager
{
public:
	/**
	 * Constructor.
	 *
	 * @param	[in]	p_pAllocator	Defines the memory allocator.
	*/
	BiaStringManager(BiaAllocator * p_pAllocator);
	BiaStringManager(BiaStringManager && p_move);
	BiaStringManager(const BiaStringManager&) = delete;
	~BiaStringManager();
	const char * GetStringAddress(const char * p_pcString, size_t p_iSize);

private:
	struct StringEntry
	{
		inline StringEntry(const char * p_pcString, size_t p_iSize)
		{
			pcString = p_pcString;
			iSize = p_iSize;
		}

		const char * pcString;
		size_t iSize;

		inline bool operator==(const StringEntry & p_string) const
		{
			return iSize == p_string.iSize ? memcmp(pcString, p_string.pcString, iSize) == 0 : false;
		}
	};

	struct StringHasher
	{
		inline size_t operator()(StringEntry p_string) const
		{
			///import 
			return 0;
		}
	};

	BiaAllocator * m_pAllocator;	/**	Defines the memory allocator.	*/

	std::unordered_set<StringEntry, StringHasher> m_index;	/**	Defines the index holding all allocated names.	*/
};

}
}