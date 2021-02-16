#include "deserialize.hpp"

#include <bia/error/exception.hpp>
#include <bia/util/portable/stream.hpp>
#include <cstdint>

bia::resource::Resources bia::resource::deserialize(util::Span<const util::Byte*> data)
{
	Resources resources;
	while (!data.empty()) {
		const auto length = util::portable::read<std::uint32_t>(data);
		// TODO check length
		BIA_ASSERT(length <= data.size());
		resources.push_back(util::Span<const char*>{ reinterpret_cast<const char*>(data.data()), length });
		data = data.subspan(length);
	}
	return resources;
}
