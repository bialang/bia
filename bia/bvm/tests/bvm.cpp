#include <bvm/bvm.hpp>
#include <bytecode/writer.hpp>
#include <gc/gc.hpp>
#include <gc/simple_allocator.hpp>
#include <stream/buffer_output_stream.hpp>

using namespace bia;
using namespace bia::bytecode;

inline void test_foo(long long v)
{
	printf("hello %d\n", v);
}

int main(int argc, char** argv)
{
	try {
		gc::gc gc(std::unique_ptr<gc::memory_allocator>(new gc::simple_allocator()), nullptr);
		stack::stack stack(gc.allocator(), 1024);

		bvm::context context(stack, gc);
		stream::buffer_output_stream output(*gc.allocator());
		bvm::bvm machine;
		const void* b;
		std::size_t s;

		instruction_writer wi(output);
		
		wi.write_instruction<false, OC_PUSH_IMMEDIATE, std::int64_t>(0x0807060504030201LL);
		wi.write_instruction<true, OC_CALL>(temp_member_index<std::uint32_t>{ 1 }, temp_member_index<std::uint32_t>{ 0 },
											1,
											2);
		wi.write_instruction<true, OC_JUMP>(-16);
		wi.write_end();

		printf("printing code...");

		std::tie(b, s, std::ignore) = output.take_buffer();

		for (std::size_t i = 0; i < s - max_instruction_size - 1; ++i) {
			if (!(i % 16)) {
				puts("");
			}

			printf("%02x ", static_cast<const unsigned char*>(b)[i]);
		}

		puts("\n(END)\nstarting vm");

		machine.execute(context, compiler::code(b, static_cast<const std::int8_t*>(b) + s));
	} catch (const exception::throwable& e) {
		puts(e.debug_message().c_str());
	} catch (const std::exception& e) {
		puts(e.what());
	}
}