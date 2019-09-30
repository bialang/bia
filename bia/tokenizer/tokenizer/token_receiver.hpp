#pragma once

#include "token.hpp"

namespace bia {
namespace tokenizer {

class token_receiver
{
public:
    virtual ~token_receiver() = default;
    virtual void receive(const token* begin, const token* end);
};

}
}