#ifndef BIA_TOKENIZER_RESOURCE_MEMORY_MEMORY_HPP_
#define BIA_TOKENIZER_RESOURCE_MEMORY_MEMORY_HPP_

#include "../size.hpp"
#include "iterator.hpp"

#include <gc/std_memory_allocator.hpp>
#include <memory>
#include <util/gsl.hpp>
#include <vector>

namespace bia {
namespace tokenizer {
namespace resource {

class manager;

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
	friend manager;

	std::shared_ptr<page_container_type> _pages;
	const size* _size;
	std::size_t _page_index;

	memory(util::not_null<std::shared_ptr<page_container_type>> pages, util::not_null<const size*> size,
	       std::size_t page_index);
};

} // namespace memory
} // namespace resource
} // namespace tokenizer
} // namespace bia

#endif