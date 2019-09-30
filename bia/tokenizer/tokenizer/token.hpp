#pragma once

#include "rule_id.hpp"
#include "keyword.hpp"

#include <cstdint>

namespace bia {
namespace tokenizer {

struct token
{
    enum class TYPE
    {
        INT_VALUE,
        KEYWORD,
        WRAP_BEGIN,
        WRAP_END
    };

    RULE_ID current_rule;
    RULE_ID parent_rule;
    int token_order;
    TYPE type;
    union {
        std::int64_t int_value;
        KEYWORD keyword;
    } content;
};

}
}