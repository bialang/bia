#include "resource/serializer.hpp"

#include <util/portable/memory.hpp>
#include <util/portable/stream.hpp>

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
	_output.seekp(current);
}

serializer::size_type serializer::index_of(view view)
{
	// alreay added
	const auto it = _map.find(view);

	if (it != _map.end()) {
		return it->second;
	}

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
	default: BIA_IMPLEMENTATION_ERROR("missing size_width case");
	}

	_output.write(buffer, sw.second);

	// copy data
	for (auto i = view.first; i != view.last; ++i) {
		const auto tmp = *i;

		_output.put(*reinterpret_cast<const char*>(&tmp));
	}

	_map.insert({ view, _index });

	return _index++;
}