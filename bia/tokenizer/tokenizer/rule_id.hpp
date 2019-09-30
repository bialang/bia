#pragma once

namespace bia {
namespace tokenizer {

enum class RULE_ID
{
    ROOT
};

constexpr auto rule_id_count = static_cast<int>(RULE_ID::ROOT);

}
}