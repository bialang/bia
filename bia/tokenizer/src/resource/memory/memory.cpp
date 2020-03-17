#include "tokenizer/resource/memory/memory.hpp"

namespace bia {
namespace tokenizer {
namespace resource {
namespace memory {

iterator memory::begin() const
{
	if (_pages) {
		return {};
	}

    return {};
}

iterator memory::end() const
{
    return {};
}

memory::memory(util::not_null<std::shared_ptr<page_container_type>> pages, util::not_null<const size*> size,
               std::size_t page_index)
    : _pages(std::move(pages.get()))
{
	BIA_EXPECTS(_page_index < _pages->size());

	_size       = size.get();
	_page_index = page_index;
}

} // namespace memory
} // namespace resource
} // namespace tokenizer
} // namespace bia