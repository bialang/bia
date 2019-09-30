#include <tokenizer/rule.hpp>

namespace bia {
namespace tokenizer {

void rule::run(stream::input_stream& input, rule_parameter& parameter)
{

    for (auto& r : rules) {
        r(input, parameter);
    }
}

}
}