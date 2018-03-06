#pragma once

#include <cstdint>
#include <vector>

#include "biaException.hpp"
#include "biaReportBundle.hpp"


namespace bia
{
namespace grammar
{

typedef uint64_t flag_type;

constexpr flag_type NONE = 0;
constexpr flag_type FILLER_TOKEN = 0x1;
constexpr flag_type OPTIONAL_TOKEN = 0x2;
constexpr flag_type LOOPING_TOKEN = 0x4;
constexpr flag_type STARTING_WHITESPACE_TOKEN = 0x8;
constexpr flag_type STARTING_WHITESPACE_OPTIONAL_TOKEN = 0x10;
constexpr flag_type ENDING_WHITESPACE_TOKEN = 0x20;

enum class ACTION
{
	REPORT,
	DONT_REPORT,
	REPORT_AND_LOOP,
	DONT_REPORT_AND_LOOP,
	ERROR
};

class BiaInterpreterRule;

struct TokenParams
{
	BiaReportBundle * pBundle;
	BiaInterpreterRule * pRules;
	Report::token_id iTokenId;
};

struct TokenOutput
{
	size_t iTokenSize;
	size_t iBufferOffset;
	size_t iBufferPadding;
	Report::custom_parameter iCustom;
};

typedef ACTION(*bia_token_function)(const char*, size_t, TokenParams, TokenOutput&);

class BiaInterpreterRule
{
public:
	enum FLAGS : uint32_t
	{
		F_NONE = 0,
		F_OR = 0x1,
		F_WRAP_UP = 0x2,
		F_DONT_REPORT_EMPTY = 0x4
	};


	BiaInterpreterRule();
	/**
	 * Constructor.
	 *
	 * @param	p_fFlags	Defines the flags.
	 * @param	p_vTokens	Defines the tokens for this rule.
	*/
	BiaInterpreterRule(uint32_t p_fFlags, std::vector<bia_token_function> p_vTokens);
	/**
	 * Runs this rule.
	 *
	 * @since	2.39.82.486
	 * @date	16-Sep-17
	 *
	 * @param	p_pcBuffer	Defines a buffer which this rule should be run on.
	 * @param	p_iSize	Defines the size of the buffer.
	 * @param	p_params	Defines parameters for the token functions.
	 *
	 * @return	The amount of bytes processed of the buffer.
	*/
	size_t RunRule(const char * p_pcBuffer, size_t p_iSize, TokenParams p_params);

private:
	uint32_t m_fFlags;

	std::vector<bia_token_function> m_vTokens;
};

}
}