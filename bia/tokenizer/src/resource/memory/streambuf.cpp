#include "tokenizer/resource/memory/streambuf.hpp"

#include "tokenizer/resource/manager.hpp"

#include <exception/memory_error.hpp>
#include <utility>

namespace bia {
namespace tokenizer {
namespace resource {
namespace memory {

streambuf::streambuf(streambuf&& move) noexcept
{
	std::swap(_manager, move._manager);
	std::swap(_size, move._size);
}

streambuf::~streambuf()
{
	if (valid()) {
		_manager->discard_memory();
	}
}

void streambuf::finish()
{
	BIA_EXPECTS(valid());

	_manager    = nullptr;
	_size->size = epptr() - pptr();

	// remove more flag is last exists and current is empty
	if (_last_size && !_size->size) {
		_last_size->more = 0;
	}
}

bool streambuf::valid() const noexcept
{
	return _manager;
}

streambuf::int_type streambuf::sync()
{
	// get next page if no more space is available
	if (!pptr() || pptr() == epptr()) {
		try {
			auto size = _manager->_next_size();

			// set more flag
			if (_last_size) {
				_last_size->more = 1;
				_last_size->size = epptr() - pptr();
			}

			_last_size = _size;
			_size      = size.first;
			_begin     = _begin ? _begin : _size;

			setp(reinterpret_cast<char*>(size.first + 1), reinterpret_cast<char*>(size.second));
		} catch (const exception::bia_error&) {
			return -1;
		}
	}

	return 0;
}

streambuf::int_type streambuf::overflow(int_type ch)
{
	// synchronize failed
	if (sync() != 0) {
		return traits_type::eof();
	} // write character to output
	else if (ch != traits_type::eof()) {
		sputc(traits_type::to_char_type(ch));
	}

	return traits_type::eof() + 1;
}

streambuf::streambuf(util::not_null<manager*> manager)
{
	_manager = manager.get();
}

} // namespace memory
} // namespace resource
} // namespace tokenizer
} // namespace bia