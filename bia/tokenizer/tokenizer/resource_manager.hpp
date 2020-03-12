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
		bool older(const state& other) const noexcept
		{
			return _page_index < other._page_index || (_page_index == other._page_index && _cursor < other._cursor);
		}
		state& operator=(const state& copy) = default;
		state& operator=(state&& move) = default;

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
		output_streambuf(const output_streambuf& copy) = delete;
		output_streambuf(output_streambuf&& move) noexcept
		{
			std::swap(_resource_manager, move._resource_manager);
			std::swap(_size, move._size);
		}
		~output_streambuf()
		{
			if (valid() && pptr()) {
				_resource_manager->_state._cursor = reinterpret_cast<util::byte*>(pptr()) + _size->size;
				_resource_manager->_buf_active    = false;

				_update_size(nullptr);
			}
		}
		bool valid() const noexcept
		{
			return _resource_manager;
		}
		output_streambuf& operator=(output_streambuf&& move) = default;

	protected:
		int_type sync() override
		{
			// get next page
			if (gptr() == egptr()) {
				try {
					auto page = _resource_manager->_next_page();

					_update_size(new (page.first) size{});
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

		resource_manager* _resource_manager = nullptr;
		size* _size                         = nullptr;
		size* _last_size                    = nullptr;

		output_streambuf(util::not_null<resource_manager*> resource_manager)
		{
			_resource_manager = resource_manager.get();

			if (sync() != 0) {
				BIA_THROW(exception::memory_error, "cannot create page");
			}
		}
		void _update_size(size* s) noexcept
		{
			if (_last_size) {
				_last_size->more = 1;
			}

			_last_size = _size;
			_size      = s;
		}
	};

	/**
	 * Constructor.
	 *
	 * @param allocator the memory allocator
	 * @param page_size the size of each page
	 */
	resource_manager(util::not_null<std::shared_ptr<gc::memory_allocator>> allocator,
	                 std::size_t page_size) noexcept
	    : _pages(gc::std_memory_allocator<util::byte*>(allocator)), _allocator(std::move(allocator.get()))
	{
		// allocate first page
		_page_size = page_size;
	}
	~resource_manager()
	{
		for (auto& page : _pages) {
			_allocator->deallocate(page);
		}
	}
	output_streambuf start_memory(bool avoid_duplicates)
	{
		BIA_EXPECTS(!buf_active());

		_buf_active = true;

		return { this };
	}
	state save_state() const noexcept
	{
		return _state;
	}
	void restore_state(const state& old)
	{
		BIA_EXPECTS(!_state.older(old));

		_state = old;
	}
	bool buf_active() const noexcept
	{
		return _buf_active;
	}

private:
	/** whether a streambuf is active */
	bool _buf_active = false;
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
		// current page can still store
		if (!_pages.empty() && _state._cursor + 8 <= _pages[_state._page_index - 1]) {
			return { _state._cursor, _pages[_state._page_index - 1] + _page_size };
		}

		// no more pages available: allocate new page
		if (_state._page_index + 1 >= _pages.size()) {
			_pages.push_back(static_cast<util::byte*>(_allocator->checked_allocate(_page_size).get()));
		}

		// return next page
		_state._cursor = _pages[_state._page_index++];

		return { _state._cursor, _state._cursor + _page_size };
	}
};

} // namespace tokenizer
} // namespace bia

#endif