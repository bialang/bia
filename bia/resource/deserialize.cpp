#include "deserialize.hpp"

#include "info.hpp"
#include "serializer.hpp"

#include <cstdint>
#include <bia/member/native/string.hpp>
#include <bia/util/portable/stream.hpp>

std::unique_ptr<bia::gc::root> bia::resource::deserialize(std::istream& input, gc::gc& gc)
{
	const auto count = util::portable::read<serializer::size_type>(input);
	const auto lock  = gc.lock();
	gc::root::builder builder{ &gc, count };

	for (serializer::size_type i = 0; i < count; ++i) {
		const auto info    = info_from(input.get());
		std::uint32_t size = 0;

		BIA_EXPECTS(info.first == type::string);

		switch (info.second) {
		case size_width::_8: size = util::portable::read<std::uint8_t>(input); break;
		case size_width::_16: size = util::portable::read<std::uint16_t>(input); break;
		case size_width::_32: size = util::portable::read<std::uint32_t>(input); break;
		default: throw;
		}

		auto string = gc.allocate(size);
		auto gcable = gc.construct<member::native::string>(static_cast<char*>(string.peek()));

		input.read(static_cast<char*>(string.peek()), size);
		builder.add(gcable.peek());
		string.start_monitor();
		gcable.start_monitor();
	}

	return builder.finish();
}
