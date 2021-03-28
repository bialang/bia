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
	// already added
	const auto it = _map.find(view);
	if (it != _map.end()) {
		return it->second;
	}

	// copy data
	util::portable::write(_output, view.type);
	// remove zero terminating character from string
	int pad = view.type == Type::string ? 1 : 0;
	util::portable::write(_output, static_cast<std::uint32_t>(view.size() - pad));
	for (auto it = view.begin(), c = view.end() - pad; it != c; ++it) {
		_output.put(static_cast<char>(*it));
	}
	_map.insert({ view, _index });
	return _index++;
}
