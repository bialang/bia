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
		return sizeof(memory::gc::GC_able<Vector*>);
	}
	constexpr static std::size_t alignment() noexcept
	{
		return alignof(memory::gc::GC_able<Vector*>);
	}
	static void frame(memory::gc::GC& gc, util::Span<util::Byte*> buffer, std::vector<std::string> value)
	{
		*reinterpret_cast<memory::gc::GC_able<Vector*>*>(buffer.data()) = gc.create<Vector>(std::move(value));
	}
	static const std::vector<std::string>& unframe(util::Span<const util::Byte*> buffer)
	{
		return (*reinterpret_cast<const memory::gc::GC_able<Vector*>*>(buffer.data()))->value;
	}
};

} // namespace bia

int main(int argc, char** argv)
{
	bia::Engine engine;
	engine.function(
	  "hello_world", [] { std::cout << "Hello, World! - C++\n"; });
	engine.function(
	  "print", [](const std::vector<std::string>& ss) {
		  for (const auto& s : ss) {
			  std::cout << s << " ";
		  }
		  std::cout << "\n";
	  });
	engine.function(
	  "read", [] {
			std::cout << "Enter a string twice...\n";
		  std::string s;
		  std::vector<std::string> ss;
		  for (int i = 0; i < 2; ++i) {
			  std::getline(std::cin, s);
			  ss.push_back(s);
		  }
		  return ss;
	  });

	std::stringstream code;
	code << u8R"(

let x = hello_world()
print(read())

	)";
	engine.run(code);
}
