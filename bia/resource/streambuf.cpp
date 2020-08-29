#include "streambuf.hpp"

#include "manager.hpp"

#include <bia/error/exception.hpp>
#include <bia/util/finally.hpp>
#include <bia/util/portable/memory.hpp>
#include <limits>
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

	_manager->_space.truncate(end);

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
		} catch (const error::exception&) {
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
