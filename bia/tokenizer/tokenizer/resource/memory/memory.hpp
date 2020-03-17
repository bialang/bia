#ifndef BIA_TOKENIZER_RESOURCE_MEMORY_MEMORY_HPP_
#define BIA_TOKENIZER_RESOURCE_MEMORY_MEMORY_HPP_

#include "../size.hpp"
#include "iterator.hpp"

namespace bia {
namespace tokenizer {
namespace resource {
namespace memory {

class memory
{
public:
	memory()                   = default;
	memory(const memory& copy) = default;
	memory(memory&& move)      = default;

	iterator begin() const;
	iterator end() const;

private:
	const size* _size;
};

} // namespace memory
} // namespace resource
} // namespace tokenizer
} // namespace bia

#endif