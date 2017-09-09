#ifndef YTOKEN_H
#define YTOKEN_H

#include <vector>
#include <memory>
#include <type_traits>

#include "yinterpreter_code.h"


namespace yu
{
namespace interpret
{

class CYinterpreter;

/**	Specifies the base struct for a token.	*/
struct SToken
{
	/**
	 * Constructor.
	 *
	 * @param	p_llTokenId	Defines the token id.
	*/
	SToken(const long long & p_llTokenId) : cllTokenId(p_llTokenId)
	{
	}
	virtual ~SToken()
	{
	}

	const long long cllTokenId;
};

struct SCharcters : SToken
{
	SCharcters(const long long & p_llTokenId, const unsigned int & p_unMinChars, const unsigned int & p_unMaxChars) : SToken(p_llTokenId)
	{
		unMinChars = p_unMinChars;
		unMaxChars = p_unMaxChars;
	}

	unsigned int unMinChars;
	unsigned int unMaxChars;
};

/**	Defines a dynamic variable using the characters from this charset.	*/
struct SCharset : SCharcters
{
	/**
	 * Constructor.
	 *
	 * @param	p_llTokenId	Defines the id of the charset.
	 * @param	p_charset	Defines the available characters.
	 * @param	p_unMinChars	(Optional)	Defines the minimum requirement of the characters.
	 * @param	p_unMaxChar	(Optional)	Defines the maximum of characters. If this value is less than @b p_unMinChars, no upper is defined.
	 */
	SCharset(const long long & p_llTokenId, const ycode & p_charset, const unsigned int & p_unMinChars = 0, const unsigned int & p_unMaxChars = 0) : SCharcters(p_llTokenId, p_unMinChars, p_unMaxChars), charset(p_charset)
	{
	}
	virtual ~SCharset()
	{
	}

	ycode charset;
};

/**	Defines one or multiple ranges of characters.	*/
struct SCharRanges : SCharcters
{
	/**	A struct that holds one range.	*/
	struct SRange
	{
		SRange() : start((const char*)nullptr, 0), end((const char*)nullptr, 0)
		{
		}

		ycode start;
		ycode end;
	};

	/**
	 * Constructor.
	 *
	 * @param	p_llTokenId	Defines the id of the char range.
	 * @param	p_unMinChars	(Optional)	Defines the minimum requirement of the characters.
	 * @param	p_unMaxChar	(Optional)	Defines the maximum of characters. If this value is less than @b p_unMinChars, no upper is defined.
	*/
	SCharRanges(const long long & p_llTokenId, const unsigned int & p_unMinChars = 0, const unsigned int & p_unMaxChars = 0) : SCharcters(p_llTokenId, p_unMinChars, p_unMaxChars)
	{
	}
	/**
	 * Adds a range. The parameters must be one of the following: char, char16_t or char32_t.
	 *
	 * @param	p_cStart	Defines the start char (included).
	 * @param	p_cEnd	Defines the end char (included).
	 *
	 * @return	this.
	*/
	template<typename T>
	SCharRanges * AddRange(T p_cStart, T p_cEnd)
	{
		static_assert(std::is_same<T, char>::value || std::is_same<T, char16_t>::value || std::is_same<T, char32_t>::value, "The parameters must be one of the following: char, char16_t or char32_t.");

		SRange range;

		//Swap if start is higher than end
		if (p_cStart > p_cEnd)
		{
			auto cTmp = p_cStart;

			p_cStart = p_cEnd;
			p_cEnd = cTmp;
		}

		range.start = ycode(&p_cStart, 1);
		range.end = ycode(&p_cEnd, 1);

		vRanges.push_back(range);

		return this;
	}
	/**
	 * Excludes a range. The parameters must be one of the following: char, char16_t or char32_t.
	 *
	 * @param	p_cStart	Defines the start char (included).
	 * @param	p_cEnd	Defines the end char (included).
	 *
	 * @return	this.
	*/
	template<typename T>
	SCharRanges * ExcludeRange(T p_cStart, T p_cEnd)
	{
		static_assert(std::is_same(T, char)::value || std::is_same(T, char16_t)::value || std::is_same(T, char32_t)::value, "The parameters must be one of the following: char, char16_t or char32_t.");

		SRange range;

		//Swap if start is higher than end
		if (p_cStart > p_cEnd)
		{
			auto cTmp = p_cStart;

			p_cStart = p_cEnd;
			p_cEnd = cTmp;
		}

		range.start = ycode(&p_cStart, 1);
		range.end = ycode(&p_cEnd, 1);

		vExcludeRanges.push_back(range);

		return this;
	}

	std::vector<SRange> vRanges;
	std::vector<SRange> vExcludeRanges;
};

/**	Matches the code by custom criteria.	*/
struct SCustomChecker : SToken
{
	/**
	 * Constructor.
	 *
	 * @param	p_llTokenId	Defines the id of the token.
	 * @param	p_pCharacters	(Optional)	Defines of what the acceptable code should consist of.
	*/
	SCustomChecker(const long long & p_llTokenId, std::shared_ptr<SCharcters> p_pCharacters = nullptr) : SToken(p_llTokenId)
	{
		m_pCharacters = p_pCharacters;
	}

	/**
	* Will be called by the interpreter. Checks if the beginning of the code matches the custom criteria.
	*
	* @param	p_code	Defines the code. All the code past the token will be passed.
	* @param	[out]	p_iSize	Defines the output size of the code.
	* @param	[out]	p_llCustomTokenId	Defines the custom token id of the code segment.
	* @param	p_uiRule	Defines the rule in which the method will be called.
	* @param	p_uiTermId	Defines the term of the rule.
	*
	* @return	true if it succeeds, otherwise false.
	*/
	virtual bool Check(const ycode & p_code, size_t & p_iSize, long long & p_llCustomTokenId, const unsigned int & p_uiRule, const unsigned int & p_uiTermId) = 0;

private:
	friend CYinterpreter;

	std::shared_ptr<SCharcters> m_pCharacters;
};

/**	Defines a static keyword.	*/
struct SKeyword : SToken
{
	/**
	 * Constructor.
	 *
	 * @param	p_llTokenId	Defines the id of the keyword.
	 * @param	p_keyword	Defines the keyword.
	*/
	SKeyword(const long long & p_llTokenId, const ycode & p_keyword) : SToken(p_llTokenId), keyword(p_keyword)
	{
	}
	virtual ~SKeyword()
	{
	}

	ycode keyword;

	/**
	 * Compares the name of keyword with the buffer.
	 *
	 * @param	p_right	Defines the code.
	 *
	 * @return	true if the buffer equals the keyword, otherwise false.
	*/
	virtual bool Compare(const ycode & p_right)
	{
		return p_right.BeginsWith(0, keyword);
	}
};

/**	A pointer to a user-defined rule.	*/
struct SRulePointer : SToken
{
	/**
	 * Constructor.
	 *
	 * @param	p_uiRule	Defines the rule.
	*/
	SRulePointer(unsigned int p_uiRule) : SToken(0), uiRule(p_uiRule)
	{
	}

	const unsigned int uiRule;
};

struct SOperator : SToken
{
	SOperator(const long long & p_llTokenId = 0) : SToken(p_llTokenId)
	{
	}
};

struct SSingleOperator : SOperator
{
	SSingleOperator(std::shared_ptr<SToken> p_pToken, const long long & p_llTokenId = 0) : SOperator(p_llTokenId)
	{
		pToken = p_pToken;
	}

	std::shared_ptr<SToken> pToken;
};

struct SMultipleOperator : SOperator
{
	SMultipleOperator(const std::vector<std::shared_ptr<SToken>> & p_vpTokens, const long long & p_llTokenId = 0) : SOperator(p_llTokenId), vpTokens(p_vpTokens)
	{
	}

	std::vector<std::shared_ptr<SToken>> vpTokens;
};

/**	Defines an optional token.	*/
struct SOptional : SSingleOperator
{
	/**
	 * Constructor.
	 *
	 * @param	p_pToken	Defines the token that should be optional.
	*/
	SOptional(std::shared_ptr<SToken> p_pToken) : SSingleOperator(p_pToken)
	{
	}
};

/**	Defines a filler token that will not be reported.	*/
struct SFiller : SSingleOperator
{
	/**
	 * Constructor.
	 *
	 * @param	p_pToken	Defines the token that should not be reported.
	*/
	SFiller(std::shared_ptr<SToken> p_pToken) : SSingleOperator(p_pToken)
	{
	}
};

/**	Defines a loop where the token will be looped.	*/
struct SLoop : SSingleOperator
{
	/**
	* Constructor.
	*
	* @param	p_pToken	Defines the token that should be looped.
	* @param	p_unMin	(Optional)	Defines the minimum requirement of loops.
	* @param	p_unMax	(Optional)	Defines the maximum of loops. If this value is less than @b p_unMin, no upper is defined.
	*/
	SLoop(const std::shared_ptr<SToken> & p_pToken, const unsigned int & p_unMin = 0, const unsigned int & p_unMax = 0) : SSingleOperator(p_pToken)
	{
		unMin = p_unMin;
		unMax = p_unMax;
	}

	unsigned int unMin;
	unsigned int unMax;
};

/**	Overwrites the token id of the specified token.	*/
struct SIdOverwrite : SSingleOperator
{
	/**
	 * Constructor.
	 *
	 * @param	p_llTokenId	Defines the new token id.
	 * @param	p_pToken	Defines the token that should be looped.
	*/
	SIdOverwrite(const long long & p_llTokenId, const std::shared_ptr<SToken> & p_pToken) : SSingleOperator(p_pToken, p_llTokenId) {}
};

/**	Defines an or clause out of tokens.	*/
struct SOr : SMultipleOperator
{
	/**
	 * Constructor.
	 *
	 * @param	p_vpTokens	Defines the available tokens.
	*/
	SOr(const std::vector<std::shared_ptr<SToken>> & p_vpTokens) : SMultipleOperator(p_vpTokens)
	{
	}
};

/**	Defines an and clause out of tokens.	*/
struct SAnd : SMultipleOperator
{
	/**
	 * Constructor.
	 *
	 * @param	p_vpTokens	Defines the available tokens.
	*/
	SAnd(const std::vector<std::shared_ptr<SToken>> & p_vpTokens) : SMultipleOperator(p_vpTokens)
	{
	}
};

/**	Defines a cluster where all tokens are optional and the order is unimportant.	*/
struct SOptionalCluster : SMultipleOperator
{
	/**
	 * Constructor.
	 *
	 * @param	p_vpTokens	Defines the tokens.
	 * @param	p_bRepeatToken	Defines wheter a token can be repeatedly used or not.
	 * @param	p_unMin	(Optional)	Defines the minimum requirement of the tokens.
	 * @param	p_unMax	(Optional)	Defines the maximum of tokens. If this value is less than @b p_unMin, no upper is defined.
	*/
	SOptionalCluster(const std::vector<std::shared_ptr<SToken>> & p_vpTokens, const bool & p_bRepeatToken, const unsigned int & p_unMin = 0, const unsigned int & p_unMax = 0) : SMultipleOperator(p_vpTokens)
	{
		bRepeatToken = p_bRepeatToken;

		unMin = p_unMin;
		unMax = p_unMax;
	}

	bool bRepeatToken;
	unsigned int unMin;
	unsigned int unMax;
};

/**	Packs all the token into one report (SReport::pvTokenUnion).	*/
struct STokenUnion : SMultipleOperator
{
	/**
	 * Constructor.
	 *
	 * @param	p_llTokenId	Defines the id of the union.
	 * @param	p_vpTokens	Defines the tokens.
	 * @param	p_bOutlineChildren	(Optional)	Defines whether the united tokens should be outlined or not.
	*/
	STokenUnion(const long long & p_llTokenId, const std::vector<std::shared_ptr<SToken>> & p_vpTokens, const bool & p_bOutlineChildren = false) : SMultipleOperator(p_vpTokens, p_llTokenId)
	{
		bOutlineChildren = p_bOutlineChildren;
	}

	bool bOutlineChildren;
};

/**	Allows prioritazied tokens in this region.	*/
struct SPriorityRegion : SMultipleOperator
{
	/**
	 * Constructor.
	 *
	 * @param	p_vpTokens	Defines the available tokens.
	*/
	SPriorityRegion(const std::vector<std::shared_ptr<SToken>> & p_vpTokens) : SMultipleOperator(p_vpTokens)
	{
	}
};

struct SPriorityToken : SToken
{

};

/**	Defines a term of a rule consiting of multiple tokens which will be reported.	*/
struct STerm
{
	/**
	 * Constructor.
	 *
	 * @param	p_uiTermId	Defines the id of the term.
	 * @param	p_vpTokens	Defines the tokens which define the term.
	*/
	STerm(const unsigned int & p_uiTermId, const std::vector<std::shared_ptr<SToken>> & p_vpTokens) : cuiTermId(p_uiTermId)
	{
		vpTokens = p_vpTokens;
	}

	std::vector<std::shared_ptr<SToken>> vpTokens;

	const unsigned int cuiTermId;
};

/**
 * Creates a shared token.
 *
 * @param	p_pNewToken	Defines the new allocated token.
 *
 * @return	The new allocated token as a shared pointer.
*/
inline std::shared_ptr<SToken> nt(SToken * p_pNewToken)
{
	return std::shared_ptr<SToken>(p_pNewToken);
}

/**
 * Creates a new shared term.
 *
 * @param	p_llTermId	Defines the id of the term.
 * @param	p_vpTokens	Defines the tokens of the term.
 *
 * @return	The new shared term.
*/
inline std::shared_ptr<STerm> NewTerm(const unsigned int & p_uiTermId, const std::vector<std::shared_ptr<SToken>> & p_vpTokens)
{
	return std::shared_ptr<STerm>(new STerm(p_uiTermId, p_vpTokens));
}

}
}

using yu::interpret::nt;
using yu::interpret::NewTerm;

typedef yu::interpret::SKeyword Keyword;
typedef yu::interpret::SFiller Filler;
typedef yu::interpret::SCharset Charset;
typedef yu::interpret::SCharRanges CharRanges;
typedef yu::interpret::SLoop Loop;
typedef yu::interpret::SIdOverwrite IdOverwrite;
typedef yu::interpret::SAnd And;
typedef yu::interpret::SOr Or;
typedef yu::interpret::SOptional Optional;
typedef yu::interpret::SOptionalCluster OptionalCluster;
typedef yu::interpret::STokenUnion TokenUnion;
typedef yu::interpret::SRulePointer RulePointer;
typedef yu::interpret::SCustomChecker CustomChecker;

#endif // !YTOKEN_H