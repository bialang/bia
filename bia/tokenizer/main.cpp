#include <stream/buffer_input_stream.hpp>
#include <string>
#include <tokenizer/syntax.hpp>

using namespace bia;

inline stream::buffer_input_stream make_stream(const char* string)
{
	return stream::buffer_input_stream(reinterpret_cast<const std::int8_t*>(string),
	                                   reinterpret_cast<const std::int8_t*>(string) +
	                                       std::char_traits<char>::length(string));
}

class receiver : public tokenizer::token_receiver
{
	// Inherited via token_receiver
	virtual void receive(const tokenizer::token* begin, const tokenizer::token* end) override
	{
		while (begin < end) {
			puts("token");
		}
	}
};

int main()
{
	auto stream = make_stream(u8R"(

print()

)");
	receiver rec;

	tokenizer::syntax::initialize();
	puts("initialized");
	tokenizer::syntax::default_syntax().lex(stream, rec);
}