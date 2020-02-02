#ifndef BIA_TOKENIZER_RULE_ID_HPP_
#define BIA_TOKENIZER_RULE_ID_HPP_

#include <cstddef>

namespace bia {
namespace tokenizer {

/**
 * IDs for every rule.
 */
enum class rule_id
{
	/** the root id */
	root
};

/** the amount of all rules */
constexpr auto rule_id_count = static_cast<std::size_t>(rule_id::root);

} // namespace tokenizer
} // namespace bia

#endif