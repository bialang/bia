#include "schein.hpp"
#include "machine_context.hpp"
#include "share.hpp"


namespace bia
{
namespace machine
{

schein::schein(machine::machine_context & _context) : _stack(_context.allocator(), 64/*TODO*/)
{
	this->_context = &_context;
}

schein::~schein()
{
	clear();
}

void schein::register_allocation(memory::universal_allocation _allocation, deleter_function_t && _deleter)
{
	_allocations.emplace_back(std::make_pair(_allocation, std::move(_deleter)));
}

void schein::register_allocation(memory::universal_allocation _allocation, const deleter_function_t & _deleter)
{
	_allocations.emplace_back(std::make_pair(_allocation, _deleter));
}

void schein::register_big_int(memory::big_int_allocation _allocation)
{
	register_allocation(memory::cast_allocation<void>(_allocation), [_allocator = _context->big_int_allocator()](memory::universal_allocation _allocation) {
		_allocator->destroy_big_int(memory::cast_allocation<dependency::big_int>(_allocation));
	});
}

void schein::clear()
{
	auto _allocator = _context->allocator();

	for (auto & _allocation : _allocations) {
		if (_allocation.second) {
			_allocation.second(_allocation.first);
		} else {
			_allocator->deallocate(_allocation.first);
		}
	}

	_allocations.clear();
}

schein::regex_index_t schein::register_regex_inplace(const uint8_t * _bytes, size_t _size)
{
	BIA_NOT_IMPLEMENTED;
	/*auto _tmp = _regexs.size();

	_regexs.emplace_back(_bytes, _size);

	return _tmp;*/
}

schein::regex_index_t schein::register_regex_inplace(const char * _string, string_length_t _length)
{
	auto _tmp = _regexs.size();

	_regexs.emplace_back(_string, _length);

	return _tmp;
}

schein::regex_index_t schein::register_regex_inplace(const char16_t * _string, string_length_t _length)
{
	auto _tmp = _regexs.size();

	_regexs.emplace_back(_string, _length);

	return _tmp;
}

schein::regex_index_t schein::register_regex_inplace(const char32_t * _string, string_length_t _length)
{
	auto _tmp = _regexs.size();

	_regexs.emplace_back(_string, _length);

	return _tmp;
}

machine::machine_context * schein::machine_context() noexcept
{
	return _context;
}

machine::stack & schein::stack() noexcept
{
	return _stack;
}

machine::string_manager & schein::string_manager() noexcept
{
	return _string_manager;
}

std::vector<utility::share<dependency::regex>>& schein::regexs() noexcept
{
	return _regexs;
}

}
}