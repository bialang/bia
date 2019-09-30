#pragma once

#include "../rule.hpp"

namespace bia {
namespace tokenizer {

template<typename Keyword>
inline void keyword_token(stream::input_stream& input, rule_parameter& parameter)
{
    constexpr auto size = 32;

    if (input.supports_bufferless()) {
        auto buffer = input.bufferless_read(size);

        parameter.encoder.convert
    }
}

}
}