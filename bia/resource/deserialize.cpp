#include "deserialize.hpp"

#include <bia/error/exception.hpp>
#include <bia/util/portable/stream.hpp>
#include <cstdint>
#include <cstring>

bia::resource::Resources bia::resource::deserialize(util::Span<const util::Byte*> data, memory::gc::GC& gc)
{
	Resources resources;
	while (!data.empty()) {
		const auto type   = util::portable::read<Type>(data);
		const auto length = util::portable::read<std::uint32_t>(data);
		// TODO check length
		BIA_ASSERT(length <= data.size());
		if (type == Type::string) {
			resources.push_back(
			  gc.create<member::object::String>(std::string{ reinterpret_cast<const char*>(data.data()), length }));
		} else if (type == Type::regex) {
			// TODO check size
			resources.push_back(
			  gc.create<memory::gc::Regex>(std::regex{ reinterpret_cast<const char*>(data.begin()) }));
		} else {
			// TODO
			BIA_ASSERT(false);
		}
		data = data.subspan(length);
	}
	return resources;
}
