#ifndef BIA_TOKENIZER_RESOURCE_MANAGER_HPP_
#define BIA_TOKENIZER_RESOURCE_MANAGER_HPP_

#include <cstdint>
#include <gc/memory_allocator.hpp>
#include <gc/std_memory_allocator.hpp>
#include <iterator>
#include <map>
#include <streambuf>
#include <util/gsl.hpp>
#include <vector>

namespace bia {
namespace tokenizer {

class resource_manager
{
public:
	class state
	{
	public:
		state()                  = default;
		state(const state& copy) = default;
		state(state&& move)      = default;
		std::size_t page_index() noexcept
		{
			return _page_index;
		}
		util::byte* cursor() noexcept
		{
			return _cursor;
		}

	private:
		friend class resource_manager;

		std::size_t _page_index = 0;
		util::byte* _cursor     = nullptr;
	};

	struct size
	{
		std::uint16_t more : 1;
		std::uint16_t size : 15;
	};

	class output_streambuf : public std::streambuf
	{
	public:
	protected:
		int_type sync() override
		{
			// get next page
			if (gptr() == egptr()) {
				if (_size) {
					_size->more = 1;
				}

				try {
					auto page = _resource_manager->_next_page();

					_size = new (page.first) size{};

					setp(reinterpret_cast<char*>(_size + 1), reinterpret_cast<char*>(page.second));
				} catch (const exception::bia_error&) {
					return -1;
				}
			}

			return 0;
		}
		int_type overflow(int_type c) override
		{
			if (sync() == 0) {
				if (c != traits_type::eof()) {
					sputc(traits_type::to_char_type(c));

					return c;
				}

				return c;
			}

			return traits_type::eof();
		}

	private:
		friend class resource_manager;

		resource_manager* _resource_manager;
		size* _size;

		output_streambuf(util::not_null<resource_manager*> resource_manager)
		{
			_resource_manager = resource_manager.get();
			_size             = nullptr;

			if (sync() != 0) {
				BIA_THROW(exception::memory_error, "cannot create page");
			}
		}
	};

	resource_manager(util::not_null<std::shared_ptr<gc::memory_allocator>> allocator, std::size_t page_size)
	    : _pages(gc::std_memory_allocator<util::byte*>(allocator)), _allocator(std::move(allocator.get()))
	{
		// allocate first page
		_page_size     = page_size;
		_state._cursor = static_cast<util::byte*>(_allocator->checked_allocate(_page_size).get());

		_pages.push_back(_state._cursor);
	}
	~resource_manager()
	{
		for (auto& page : _pages) {
			_allocator->deallocate(page);
		}
	}
	output_streambuf start_memory(bool avoid_duplicates)
	{
		return { this };
	}
	state save_state() const noexcept
	{
		return _state;
	}
	void restore_state(const state& old)
	{}

private:
	/** size of a single page */
	std::size_t _page_size;
	/** all currently allocated pages */
	std::vector<util::byte*, gc::std_memory_allocator<util::byte*>> _pages;
	/** the current state */
	state _state;
	/** the memory allocator */
	std::shared_ptr<gc::memory_allocator> _allocator;

	/**
	 * Allocates the next page if no more pages are available and returns its beginning and the end.
	 *
	 * @returns a pair with the beginning and the end for that page
	 * @throw see gc::memory_allocator::checked_allocate()
	 */
	std::pair<util::byte*, util::byte*> _next_page()
	{
		// no more pages available
		if (_state._page_index + 1 >= _pages.size()) {
			_pages.push_back(static_cast<util::byte*>(_allocator->checked_allocate(_page_size).get()));
		}

		_state._page_index++;

		_state._cursor = _pages[_state._page_index];

		return { _state._cursor, _state._cursor + _page_size };
	}
};

} // namespace tokenizer
} // namespace bia

#endif