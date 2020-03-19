#ifndef BIA_TOKENIZER_RESOURCE_MEMORY_PAGE_HPP_
#define BIA_TOKENIZER_RESOURCE_MEMORY_PAGE_HPP_

#include <gc/std_memory_allocator.hpp>
#include <util/gsl.hpp>
#include <vector>

namespace bia {
namespace tokenizer {
namespace resource {
namespace memory {
typedef std::vector<util::byte*, gc::std_memory_allocator<util::byte*>> page_container_type;

} // namespace memory
} // namespace resource
} // namespace tokenizer
} // namespace bia

#endif