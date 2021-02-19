#include "serializer.hpp"

#include <algorithm>
#include <bia/error/exception.hpp>
#include <bia/log/log.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/portable/memory.hpp>
#include <bia/util/portable/stream.hpp>

using namespace bia::resource;

Serializer::Serializer(std::ostream& output) noexcept : _output{ output }
{}

Serializer::Size Serializer::index_of(View view)
{
	// alreay added
	const auto it = _map.find(view);
	if (it != _map.end()) {
		return it->second;
	}
	// copy data
	util::portable::write(_output, view.type);
	util::portable::write(_output, static_cast<std::uint32_t>(view.size()));
	for (auto i : view) {
		_output.put(*reinterpret_cast<const char*>(&i));
	}
	_map.insert({ view, _index });
	return _index++;
}
