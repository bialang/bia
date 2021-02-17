#include "streambuf.hpp"

#include "manager.hpp"

#include <bia/error/exception.hpp>
#include <bia/util/finally.hpp>
#include <bia/util/portable/memory.hpp>
#include <limits>
#include <utility>

using namespace bia::resource;

Streambuf::Streambuf(util::Not_null<Manager*> manager)
{
	_manager      = manager.get();
	_initial_size = _manager->_space.size();
}

Streambuf::Streambuf(Streambuf&& move) noexcept
{
	std::swap(_manager, move._manager);
	std::swap(_initial_size, move._initial_size);
}

Streambuf::~Streambuf()
{
	_discard();
}

View Streambuf::finish(type type)
{
	BIA_EXPECTS(valid());

	const auto end     = _manager->_space.size() - (epptr() - pptr());
	const auto finally = util::finallay([this] {
		_manager->_buf_active = false;
		_manager              = nullptr;
	});
	_manager->_space.truncate(end);
	return { type, _manager->_space.cursor(_initial_size), _manager->_space.cursor(end) };
}

bool Streambuf::valid() const noexcept
{
	return _manager;
}

Streambuf::int_type Streambuf::sync()
{
	BIA_EXPECTS(valid());

	// get next page if no more space is available
	if (!pptr() || pptr() == epptr()) {
		try {
			const auto buf =
			  _manager->_space.next_region(std::numeric_limits<memory::space::size_type>::max()).get();
			setp(reinterpret_cast<char*>(buf.begin()), reinterpret_cast<char*>(buf.end()));
		} catch (const error::Exception&) {
			return -1;
		}
	}
	return 0;
}

Streambuf::int_type Streambuf::overflow(int_type ch)
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

Streambuf& Streambuf::operator=(Streambuf&& move) noexcept
{
	_discard();
	std::swap(_manager, move._manager);
	std::swap(_initial_size, move._initial_size);
	return *this;
}

void Streambuf::_discard() noexcept
{
	if (valid()) {
		_manager->_buf_active = false;
		_manager              = nullptr;
		_initial_size         = 0;
	}
}
