#pragma once

#include <cstring>


namespace bia
{
namespace api
{
namespace grammar
{

enum class ACTION
{
	ACCEPT,
	IGNORE,
	REJECT
};

typedef ACTION(*bia_token_function)(const char*, size_t, size_t&);



struct Keyword_var
{
	constexpr static const char * Token()
	{
		return "var";
	}
	constexpr static size_t Size()
	{
		return 3;
	}
};

struct Keyword_new
{
	constexpr static const char * Token()
	{
		return "new";
	}
	constexpr static size_t Size()
	{
		return 3;
	}
};

struct Keyword_for
{
	constexpr static const char * Token()
	{
		return "for";
	}
	constexpr static size_t Size()
	{
		return 3;
	}
};

template<size_t _SIZE>
inline bool FastFind(char p_cWhat, const char * p_pcSortedString)
{
	return true;
}

template<typename T, ACTION _SUCCESS>
inline ACTION KeywordToken(const char * p_pcBuffer, size_t p_iSize, size_t & p_iOutMatched)
{
	if (p_iSize >= T::Size())
	{
		if (memcmp(p_pcBuffer, T::Token(), T::Size()))
			return ACTION::REJECT;
		else
		{
			p_iOutMatched = T::Size();

			return _SUCCESS;
		}
	}
	else
		return ACTION::REJECT;
}

template<typename T, ACTION _SUCCESS, size_t _MIN, size_t _MAX>
inline ACTION CharsetToken(const char * p_pcBuffer, size_t p_iSize, size_t & p_iOutMatched)
{
	p_iOutMatched = 0;

	while (p_iSize)
	{
		if (!FastFind<T::Size()>(p_pcBuffer[p_iOutMatched], T::Token()))
			break;

		++p_iOutMatched;
	}

	if (_SUCCESS == ACTION::ACCEPT && !p_iOutMatched)
		return ACTION::REJECT;
	else
		return _SUCCESS;
}

}
}
}