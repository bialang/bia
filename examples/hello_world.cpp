#include <bia/engine.hpp>
#include <iostream>
#include <sstream>
#include <vector>

typedef bia::memory::gc::Container<std::vector<std::string>> Vector;
typedef bia::memory::gc::GC_able<Vector*> Pointer;

namespace bia {

template<typename Type>
struct internal::type::Framer<
  Type, typename std::enable_if<
          std::is_same<typename std::decay<Type>::type, std::vector<std::string>>::value>::type>
{
	constexpr static std::size_t size() noexcept
	{
		return Framer<Pointer>::size();
	}
	constexpr static std::size_t alignment() noexcept
	{
		return Framer<Pointer>::alignment();
	}
	static void frame(memory::gc::GC& gc, util::Span<util::Byte*> buffer, std::vector<std::string> value)
	{
		Framer<Pointer>::frame(gc, buffer, gc.create<Vector>(std::move(value)));
	}
	static std::vector<std::string>& unframe(util::Span<const util::Byte*> buffer)
	{
		return Framer<Pointer>::unframe(buffer)->value;
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
		for (int i = 0; i < 2; ++i) {
			std::getline(std::cin, s);
			ss.push_back(s);
		}
		return ss;
	});
	engine.function("append",
	                [](std::vector<std::string>& ss, const std::string& value) { ss.push_back(value); });

	auto args = engine.object("args");
	args.variable("count", std::ptrdiff_t{ argc });
	args.variable("program", std::string{ argv[0] });
	args.finish();

	std::stringstream code;
	code << u8R"(

		let input = read()
		append(input, args.program)
		print(input, args.count)

	)";
	engine.run(code);
}
