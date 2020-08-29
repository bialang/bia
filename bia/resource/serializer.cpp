#include "serializer.hpp"

#include <algorithm>
#include <bia/error/exception.hpp>
#include <bia/log/log.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/portable/memory.hpp>
#include <bia/util/portable/stream.hpp>

using namespace bia::resource;

serializer::serializer(std::ostream& output) noexcept : _output{ output }, _start{ output.tellp() }
{
	util::portable::write(output, size_type{ 0 });
}

void serializer::finish()
{
	const auto current = _output.tellp();

	_output.seekp(_start);
	util::portable::write(_output, _index);

	// finalize last bindings
	if (_last_binding != std::ostream::off_type{ -1 } && _binding_count) {
		_output.seekp(_last_binding);
		util::portable::write(_output, _binding_count);
	}

	_output.seekp(current);
}

serializer::size_type serializer::index_of(view view)
{
	// alreay added
	const auto it = _map.find(view);

	if (it != _map.end()) {
		return it->second;
	}

	// finalize bindings of last write
	if (_last_binding != std::ostream::off_type{ -1 }) {
		if (_binding_count) {
			const auto current = _output.tellp();

			_output.seekp(_last_binding);
			util::portable::write(_output, _binding_count);
			_output.seekp(current);

			_binding_count = 0;
		}

		_last_binding = std::ostream::off_type{ -1 };
	}

	BIA_LOG(TRACE, "serializing new entry with {} bytes", view.size);

	// write info
	const auto sw = size_width_of(view.size);

	// write info
	_output.put(info_to(view.type, sw.first));

	// write size
	char buffer[4]{};

	switch (sw.first) {
	case size_width::_8: util::portable::write(buffer, static_cast<std::uint8_t>(view.size)); break;
	case size_width::_16: util::portable::write(buffer, static_cast<std::uint16_t>(view.size)); break;
	case size_width::_32: util::portable::write(buffer, static_cast<std::uint32_t>(view.size)); break;
	default: BIA_THROW(error::code::bad_switch_value);
	}

	_output.write(buffer, sw.second);

	// bindable
	if (view.type == type::function) {
		_binding_count = 0;
		_last_binding  = _output.tellp();

		util::portable::write(_output, size_type{ 0 });
	}

	// copy data
	for (auto i : view) {
		_output.put(*reinterpret_cast<const char*>(&i));
	}

	_map.insert({ view, _index });

	return _index++;
}

void serializer::add_binding(size_type from, size_type to)
{
	BIA_EXPECTS(_last_binding != std::ostream::off_type{ -1 });

	util::portable::write(_output, from, to);

	++_binding_count;
}
