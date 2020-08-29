#include "deserialize.hpp"

#include "info.hpp"

#include <bia/error/exception.hpp>
#include <bia/member/function/function.hpp>
#include <bia/member/native/regex.hpp>
#include <bia/member/native/string.hpp>
#include <bia/util/finally.hpp>
#include <bia/util/portable/stream.hpp>
#include <cstdint>

using namespace bia::resource;

std::unique_ptr<bia::gc::root> bia::resource::deserialize(std::istream& input, gc::gc& gc)
{
	const auto count = util::portable::read<serializer::size_type>(input);
	const auto lock  = gc.lock();
	gc::root::builder builder{ &gc, count };

	for (serializer::size_type i = 0; i < count; ++i) {
		const auto info    = info_from(input.get());
		std::uint32_t size = 0;

		switch (info.second) {
		case size_width::_8: size = util::portable::read<std::uint8_t>(input); break;
		case size_width::_16: size = util::portable::read<std::uint16_t>(input); break;
		case size_width::_32: size = util::portable::read<std::uint32_t>(input); break;
		default: throw;
		}

		switch (info.first) {
		case type::string: {
			auto string = gc.allocate(size);
			auto gcable = gc.construct<member::native::string>(static_cast<char*>(string.peek()));

			input.read(static_cast<char*>(string.peek()), size);
			builder.add(gcable.peek());
			string.start_monitor();
			gcable.start_monitor();

			break;
		}
		case type::regex: {
			const auto pattern = gc.allocator()->checked_allocate(size).get();
			const auto finally = util::make_finally([&gc, pattern] { gc.allocator()->deallocate(pattern); });

			input.read(static_cast<char*>(pattern), size);

			auto gcable =
			    gc.construct<member::native::regex>(std::regex{ static_cast<const char*>(pattern) });

			builder.add(gcable.peek());
			gcable.start_monitor();

			break;
		}
		case type::function: {
			// todo: this is dirty
			const auto binding_size =
			    util::portable::read<serializer::size_type>(input) * sizeof(serializer::size_type) * 2;
			auto code   = gc.allocate(size + binding_size);
			auto gcable = gc.construct<member::function::function>(
			    static_cast<const util::byte*>(code.peek()), size, binding_size);

			input.read(static_cast<char*>(code.peek()), size + binding_size);
			builder.add(gcable.peek());
			code.start_monitor();
			gcable.start_monitor();

			break;
		}
		default: BIA_THROW(error::code::bad_switch_value);
		}
	}

	return builder.finish();
}

std::pair<serializer::size_type, serializer::size_type>
    bia::resource::deserialize_binding(util::span<const util::byte*>& input)
{
	const auto tmp = util::portable::read<serializer::size_type>(input);

	return { tmp, util::portable::read<serializer::size_type>(input) };
}
