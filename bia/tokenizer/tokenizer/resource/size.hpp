#ifndef BIA_TOKENIZER_RESOURCE_SIZE_HPP_
#define BIA_TOKENIZER_RESOURCE_SIZE_HPP_

#include <cstdint>

namespace bia {
namespace tokenizer {
namespace resource {

struct size
{
	/** if `true`, there is more on the next page */
	std::uint16_t more : 1;
	std::uint16_t size : 15;
};

} // namespace resource
} // namespace tokenizer
} // namespace bia

#endif