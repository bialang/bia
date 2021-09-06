#include <bia/engine.hpp>
#include <iostream>
#include <sstream>
#include <vector>

struct Vector : bia::memory::gc::Base
{
	std::vector<std::string> value;

	Vector(std::vector<std::string>&& value) noexcept : value{ std::move(value) }
	{}
};

namespace bia {

template<typename Type>
struct internal::type::Framer<
  Type, typename std::enable_if<
          std::is_same<typename std::decay<Type>::type, std::vector<std::string>>::value>::type>
{
	constexpr static std::size_t size() noexcept
	{
		return sizeof(std::vector<std::string>);
	}
	constexpr static std::size_t alignment() noexcept
	{
		return alignof(std::vector<std::string>);
	}
	static void frame(memory::gc::GC& gc, util::Span<util::Byte*> buffer, std::vector<std::string> value)
	{
		new (buffer.data()) std::vector<std::string>{ std::move(value) };
	}
	static const std::vector<std::string>& unframe(util::Span<const util::Byte*> buffer)
	{
		return *reinterpret_cast<const std::vector<std::string>*>(buffer.data());
	}
};

} // namespace bia

int main(int argc, char** argv)
{
	bia::Engine engine;
	engine.function("hello_world", [] { std::cout << "Hello, World! - C++\n"; });
	engine.function("print", [](const std::vector<std::string>& ss, std::ptrdiff_t i) {
		for (const auto& s : ss) {
			std::cout << s << " ";
		}
		std::cout << i << "\n";
	});
	engine.function("read", [] {
		std::cout << "Enter a string twice...\n";
		std::string s;
		std::vector<std::string> ss;
		for (int i = 0; i < 1; ++i) {
			std::getline(std::cin, s);
			ss.push_back(s);
		}
		return ss;
	});

	std::stringstream code;
	code << u8R"(

let args = read()
print(read(), 9)
print(args, 45)

	)";
	engine.run(code);
}
