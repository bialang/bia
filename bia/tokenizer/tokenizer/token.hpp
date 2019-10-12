#pragma once

#include "keyword.hpp"
#include "rule_id.hpp"

#include <cstdint>

namespace bia {
namespace tokenizer {

struct token
{
	enum class TYPE
	{
		INT_VALUE,
		KEYWORD,
		OPERATOR,
		IDENTIFIER,
		WRAP_BEGIN,
		WRAP_END
	};

	RULE_ID current_rule;
	RULE_ID parent_rule;
	int token_order;
	TYPE type;
	union
	{
		std::int64_t int_value;
		KEYWORD keyword;
	} content;
};

} // namespace tokenizer
} // namespace bia