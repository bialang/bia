#include "name_manager.hpp"
#include "varg_member_passer.hpp"

#include <cstring>
#include <utility>


namespace bia
{
namespace machine
{

name_manager::name_manager(memory::allocator * _allocator) noexcept
{
	this->_allocator = _allocator;
}

name_manager::name_manager(name_manager && _move) noexcept : _index(std::move(_move._index))
{
	_allocator = _move._allocator;
}

name_manager::~name_manager() noexcept
{
	// Delete all allocated strings
	for (auto & _entry : _index) {
		try {
			_allocator->deallocate(_entry.allocation());
		} catch (...) {
		}
	}
}

name_manager::name_t name_manager::name_address(const char * _name, size_t _length)
{
	auto _result = _index.find({ _name, _length + 1 });

	// Create new entry
	if (_result == _index.end()) {
		auto _allocation = _allocator->allocate(_length + 1);

		memcpy(_allocation.first, _name, _length + 1);
		static_cast<char*>(_allocation.first)[_length] = 0;

		_result = _index.emplace(string_entry(_allocation)).first;
	}

	return _result->string;
}

name_manager::name_t name_manager::name_address_or_null(const char * _name, size_t _length) const noexcept
{
	auto _result = _index.find({ _name, _length + 1 });

	return _result == _index.end() ? nullptr : _result->string;
}

const char * name_manager::format_address(const char * _format, size_t _length)
{
	BIA_NOT_IMPLEMENTED;
	auto _result = _index.find({ _format, _length });

	// Create new entry
	if (_result == _index.end()) {
		auto _allocation = _allocator->allocate(_length);
		auto _string = static_cast<char*>(_allocation.first);
		size_t i = 0;

		for (; i < machine::platform::varg_member_passer::varg_register_passes(); ++i) {
			_string[i] = _format[i];
		}

		// Copy rest in reverse order
		for (; i < _length; ++i) {
			_string[i] = _format[_length - 1 - (i - machine::platform::varg_member_passer::varg_register_passes())];
		}

		_result = _index.insert(string_entry(_allocation)).first;
	}

	return _result->string;
}

}
}