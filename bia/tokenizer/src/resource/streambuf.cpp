#include "tokenizer/resource/streambuf.hpp"

#include "tokenizer/resource/manager.hpp"

#include <utility>

namespace bia {
namespace tokenizer {
namespace resource {

streambuf::streambuf(streambuf&& move) noexcept
{
	std::swap(_manager, move._manager);
	std::swap(_begin, move._begin);
}

streambuf::~streambuf()
{
	if (valid()) {
		_manager->discard_memory(*this);
	}
}

void streambuf::close() noexcept
{
	_manager = nullptr;
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
			auto buf = _manager->_space.next_region(0);

			setp(reinterpret_cast<char*>(buf.begin()), reinterpret_cast<char*>(buf.end()));
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
	_begin   = manager->_space.size();
}

} // namespace resource
} // namespace tokenizer
} // namespace bia