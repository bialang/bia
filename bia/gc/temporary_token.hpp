#ifndef BIA_GC_TEMPORARY_TOKEN_HPP_
#define BIA_GC_TEMPORARY_TOKEN_HPP_

#include "gc.hpp"

namespace bia {
namespace gc {

class temporary_token
{
public:
	temporary_token(temporary_token&& move) noexcept
	{
		std::swap(_valid, move._valid);
	}
	~temporary_token()
	{
		if (_valid) {
			gc::_active_gc_instance = nullptr;
		}
	}
	temporary_token& operator=(temporary_token&& move) noexcept
	{
		if (_valid) {
			gc::_active_gc_instance = nullptr;
			_valid                  = false;
		} else {
			_valid = move._valid;
		}

		return *this;
	}

private:
	friend gc;

	bool _valid = false;

	temporary_token(gc* gc)
	{
		BIA_EXPECTS(!gc::_active_gc_instance);

		gc::_active_gc_instance = gc;
		_valid                  = true;
	}
};

} // namespace gc
} // namespace bia

#endif
