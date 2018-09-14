#include "string_manager.hpp"
#include "string_stream.hpp"

#include <cstring>
#include <utility>


namespace bia
{
namespace machine
{

string_manager::string_manager(memory::allocator * _allocator) noexcept
{
	this->_allocator = _allocator;
}

string_manager::string_manager(string_manager && _rvalue) noexcept : _index(std::move(_rvalue._index))
{
	_allocator = _rvalue._allocator;
}

string_manager::~string_manager() noexcept
{
	// Delete all allocated strings
	for (auto & _entry : _index) {
		try {
			_allocator->deallocate(_entry.allocation());
		} catch (...) {
		}
	}

	// Delete all string resources
	for (auto & _resource : _string_resources) {
		try {
			_allocator->deallocate({ _resource, stream::string_stream::size(_resource) });
		} catch (...) {
		}
	}
}

void string_manager::register_string(int8_t * _resource)
{
	_string_resources.push_back(_resource);
}

string_manager::name_type string_manager::name_address(const char * _name, size_t _length)
{
	auto _result = _index.find({ _name, _length });

	// Create new entry
	if (_result == _index.end()) {
		auto _allocation = _allocator->allocate(_length + 1);

		memcpy(_allocation.first, _name, _length + 1);
		static_cast<char*>(_allocation.first)[_length] = 0;

		_result = _index.emplace(string_entry(_allocation)).first;
	}

	return _result->_string;
}

const char * string_manager::format_address(const char * _format, size_t _length)
{
	auto _result = _index.find({ _format, _length });

	// Create new entry
	if (_result == _index.end()) {
		auto _allocation = _allocator->allocate(_length);
		auto _string = static_cast<char*>(_allocation.first);

		// Copy in reverse order
		for (size_t i = 0; _length--; ++i) {
			_string[i] = _format[_length];
		}

		_result = _index.insert(string_entry(_allocation)).first;
	}

	return _result->_string;
}

}
}