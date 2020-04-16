#include "resource/streambuf.hpp"

#include "resource/manager.hpp"

#include <exception/implementation_error.hpp>
#include <limits>
#include <util/finally.hpp>
#include <util/portable/memory.hpp>
#include <utility>

using namespace bia::resource;

streambuf::streambuf(util::not_null<manager*> manager)
{
	_manager      = manager.get();
	_initial_size = _manager->_space.size();
}

streambuf::streambuf(streambuf&& move) noexcept
{
	std::swap(_manager, move._manager);
	std::swap(_initial_size, move._initial_size);
}

streambuf::~streambuf()
{
	_discard();
}

view streambuf::finish(type type)
{
	BIA_EXPECTS(valid());

	const auto end     = _manager->_space.size() - (epptr() - pptr());
	const auto size    = end - _initial_size;
	const auto finally = util::make_finally([this] {
		_manager->_buf_active = false;
		_manager              = nullptr;
	});

	if (pptr()) {
		// write type and size
		const auto sw = size_width_of(size);
		
		// write info
		sputc(info_to(type, sw.first));
		
		// write size
		char_type buffer[4]{};

		switch (sw.first) {
		case size_width::_8: util::portable::write(buffer, static_cast<std::uint8_t>(size)); break;
		case size_width::_16: util::portable::write(buffer, static_cast<std::uint16_t>(size)); break;
		case size_width::_32: util::portable::write(buffer, static_cast<std::uint32_t>(size)); break;
		default: BIA_IMPLEMENTATION_ERROR("missing size_width case");
		}

		xsputn(buffer, sw.second);
		
		// finalize
		_manager->_space.truncate(end + 1 + sw.second);
	}

	return { type, size, _manager->_space.cursor(_initial_size), _manager->_space.cursor(end) };
}

bool streambuf::valid() const noexcept
{
	return _manager;
}

streambuf::int_type streambuf::sync()
{
	BIA_EXPECTS(valid());

	// get next page if no more space is available
	if (!pptr() || pptr() == epptr()) {
		try {
			const auto buf =
			    _manager->_space.next_region(std::numeric_limits<gc::memory::space::size_type>::max()).get();

			setp(reinterpret_cast<char*>(buf.begin()), reinterpret_cast<char*>(buf.end()));
		} catch (const exception::bia_error&) {
			return -1;
		}
	}

	return 0;
}

streambuf::int_type streambuf::overflow(int_type ch)
{
	BIA_EXPECTS(valid());

	// synchronize failed
	if (sync() != 0) {
		return traits_type::eof();
	} // write character to output
	else if (ch != traits_type::eof()) {
		sputc(traits_type::to_char_type(ch));
	}

	return traits_type::eof() + 1;
}

streambuf& streambuf::operator=(streambuf&& move) noexcept
{
	_discard();

	std::swap(_manager, move._manager);
	std::swap(_initial_size, move._initial_size);

	return *this;
}

void streambuf::_discard() noexcept
{
	if (valid()) {
		_manager->_buf_active = false;
		_manager              = nullptr;
		_initial_size         = 0;
	}
}
