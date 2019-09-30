#pragma once

#include "lexer.hpp"
#include "rule.hpp"

namespace bia {
namespace tokenizer {

class default_lexer final : public lexer
{
public:
    default_lexer();
    virtual void lex(stream::input_stream& input, token_receiver& receiver) override;

private:
    rule rules[rule_id_count];
};

}
}