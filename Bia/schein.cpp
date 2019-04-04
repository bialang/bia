#include "schein.hpp"
#include "machine_context.hpp"
#include "share.hpp"


namespace bia
{
namespace machine
{

schein::schein(machine::machine_context & _context)
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
		_allocator->destroy_big_int(memory::cast_allocation<detail::big_int>(_allocation));
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

void schein::set_member_map(const utility::index_map & _member_map)
{
	_globals = _member_map.to_list<framework::member*>([&](auto _name) { return _context->address_of_member(_name); });
}

void schein::set_name_map(const utility::index_map & _name_map)
{
	_names = _name_map.to_list<name_manager::name_t>([](auto _name) { return _name; });
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

schein::function_index_t schein::register_function_inplace(machine::virtual_machine::virtual_machine_code && _function_code)
{
	auto _tmp = _functions.size();

	_functions.emplace_back(std::move(_function_code));

	return _tmp;
}

machine::machine_context * schein::machine_context() noexcept
{
	return _context;
}

machine::string_manager & schein::string_manager() noexcept
{
	return _string_manager;
}

std::vector<utility::share<detail::regex>>& schein::regexs() noexcept
{
	return _regexs;
}

std::vector<utility::share<detail::function_holder>>& schein::functions() noexcept
{
	return _functions;
}

const schein::member_list_t & schein::globals() const noexcept
{
	return _globals;
}

const schein::name_list_t & schein::names() const noexcept
{
	return _names;
}

}
}