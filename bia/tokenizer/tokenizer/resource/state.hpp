#ifndef BIA_TOKENIZER_RESOURCE_STATE_HPP_
#define BIA_TOKENIZER_RESOURCE_STATE_HPP_

#include <cstddef>
#include <util/gsl.hpp>

namespace bia {
namespace tokenizer {
namespace resource {

struct state
{
	util::byte* cursor;
	std::size_t page_index;

	bool older(const state& other) const noexcept
	{
		return page_index < other.page_index ||
		       (page_index == other.page_index && cursor < other.cursor);
	}
};

} // namespace resource
} // namespace tokenizer
} // namespace bia

#endif