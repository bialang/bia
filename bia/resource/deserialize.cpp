#include "deserialize.hpp"

#include <bia/error/exception.hpp>
#include <bia/util/portable/stream.hpp>
#include <cstdint>
#include <cstring>

bia::resource::Resources bia::resource::deserialize(util::Span<const util::Byte*> data, memory::gc::GC& gc)
{
	Resources resources;
	while (!data.empty()) {
		const auto length = util::portable::read<std::uint32_t>(data);
		// TODO check length
		BIA_ASSERT(length <= data.size());
		auto ptr = gc.allocate(length);
		std::memcpy(ptr, data.data(), length);
		resources.push_back(util::Span<const char*>{ static_cast<char*>(ptr), length });
		data = data.subspan(length);
	}
	return resources;
}
