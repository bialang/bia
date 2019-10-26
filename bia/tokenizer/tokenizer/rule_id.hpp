#pragma once

#include <cstddef>

namespace bia {
namespace tokenizer {

enum class RULE_ID
{
	ROOT
};

constexpr auto rule_id_count = static_cast<std::size_t>(RULE_ID::ROOT);

} // namespace tokenizer
} // namespace bia