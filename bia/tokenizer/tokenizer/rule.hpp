#pragma once

#include "rule_id.hpp"

#include <stream/input_stream.hpp>
#include <string/encoding/encoder.hpp>
#include <vector>

namespace bia {
namespace tokenizer {

struct rule_parameter
{
    string::encoding::encoder& encoder;

};

typedef void(*rule_function_type)(stream::input_stream&, rule_parameter&);

class rule
{
public:
    enum FLAG
    {
        F_NONE = 0,
        F_OR = 0x1,
    };

    void run(stream::input_stream& input, rule_parameter& parameter);

private:
    RULE_ID id;
    int flags;
    std::vector<rule_function_type> rules;
};

}
}