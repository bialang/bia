#ifndef BIA_TOKENIZER_RESOURCE_MANAGER_HPP_
#define BIA_TOKENIZER_RESOURCE_MANAGER_HPP_

#include <cstdint>
#include <gc/memory_allocator.hpp>
#include <gc/std_memory_allocator.hpp>
#include <iterator>
#include <map>
#include <util/gsl.hpp>
#include <vector>

namespace bia {
namespace tokenizer {

class resource_manager
{
public:
	class output_iterator
	{
	public:
		typedef std::output_iterator_tag iterator_category;
		typedef util::byte value_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type* pointer;
		typedef value_type& reference;

		output_iterator& operator++()
		{
			BIA_EXPECTS(valid());

			_size->size++;

			// reached page end
			if (++_cursor >= _page_size) {
				_size->more = 1;

				// allocate new page
				std::tie(_cursor, _page_end) = _resource_manager->_next_page();
			}

			return *this;
		}
		output_iterator operator++(int)
		{}
		reference operator*()
		{
			BIA_EXPECTS(valid());

			return *_cursor;
		}
		void commit_close()
		{
			BIA_EXPECTS(valid());

			// align cursor to struct size
			if (reinterpret_cast<std::intptr_t>(_cursor) % alignof(size)) {
				_cursor += alignof(size) - reinterpret_cast<std::intptr_t>(_cursor) % alignof(size);
			}

			// update state and close
			_resource_manager->_state.cursor = _cursor;
			_resource_manager                = nullptr;
		}
		bool valid() const noexcept
		{
			return _resource_manager != nullptr;
		}

	private:
		friend class resource_manager;

		class resource_manager* _resource_manager;
		struct state _original_state;
		struct size* _size;
		util::byte* _cursor;
		util::byte* _page_end;

		output_iterator(resource_manager* resource_manager) noexcept
		    : _original_state(resource_manager->_state)
		{
			_resource_manager = resource_manager;
			_size = reinterpret_cast<size*>(_resource_manager);
		}
	};

	resource_manager(util::not_null<std::shared_ptr<gc::memory_allocator>> allocator, std::size_t page_size)
	    : _pages(gc::std_memory_allocator<util::byte*>(allocator)), _allocator(std::move(allocator.get()))
	{
		// allocate first page
		_pages.push_back(_state.cursor = _allocator->checked_allocate(_page_size).get());
	}
	output_iterator start_memory(bool avoid_duplicates)
	{
		return {this};
	}

private:
	struct size
	{
		std::uint16_t more : 1;
		std::uint16_t size : 15;
	};

	struct state
	{
		std::size_t page_index;
		util::byte* cursor;
	};

	struct compare
	{
		bool operator()(const std::uint8_t* left, const std::uint8_t* right) const noexcept
		{}
	};

	/** size of a single page */
	std::size_t _page_size;
	/** all currently allocated pages */
	std::vector<util::byte*, gc::std_memory_allocator<util::byte*>> _pages;
	/** the current state */
	state _state{};
	/** the memory allocator */
	std::shared_ptr<gc::memory_allocator> _allocator;

	/**
	 * Allocates the next page if no more pages are available and returns the beginning and the end.
	 *
	 * @returns a pair with the beginning and the end for that page
	 * @throw see gc::memory_allocator::checked_allocate()
	 */
	std::pair<util::byte*, util::byte*> _next_page()
	{
		// no more pages available
		if (_state.page_index + 1 >= _page.size()) {
			_pages.push_back(_allocator->checked_allocate(_page_size).get());
		}

		_state.page_index++;

		_state.cursor = _pages[_state.page_index];

		return { _state.cursor, _state.cursor + _page_size };
	}
};

} // namespace tokenizer
} // namespace bia

#endif