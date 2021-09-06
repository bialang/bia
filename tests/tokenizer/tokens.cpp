#include <algorithm>
#include <bia/memory/simple_allocator.hpp>
#include <bia/tokenizer/token/parse/any_of.hpp>
#include <bia/tokenizer/token/parse/tokens.hpp>
#include <bia/util/finally.hpp>
#include <catch.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>

using namespace bia::tokenizer::token;
using namespace bia::tokenizer::token::parse;
using namespace bia::error;
using namespace bia::string::encoding;

template<typename... T>
inline std::shared_ptr<Parameter> create_parameter(T&&... values)
{
	auto input   = std::make_shared<std::stringstream>();
	auto enc     = get_encoder(Standard::utf_8);
	auto reader  = std::make_shared<bia::tokenizer::Reader>(*input, *enc);
	auto bndl    = std::make_shared<std::vector<Token>>();
	auto manager = std::make_shared<bia::resource::Manager>(std::make_shared<bia::memory::Simple_allocator>());
	int dummy[sizeof...(values)] = { (*input << values, 0)... };
	return { new Parameter{ *reader, *manager, *bndl }, [input, reader, manager, enc, bndl](Parameter* ptr) {
		        delete ptr;
		        free_encoder(enc);
		      } };
	return nullptr;
}

TEST_CASE("declaration statement", "[tokenizer]")
{
	Token::Number zero{};
	zero.type    = Token::Number::Type::i;
	zero.value.i = 0;

	auto param = create_parameter("let i = 0");
	REQUIRE(!root(*param));
	REQUIRE(param->bundle.size() == 5);
	REQUIRE(param->bundle[0].value == Token::Keyword::let);
	REQUIRE(param->bundle[1].value.is_type<Token::Identifier>());
	REQUIRE(param->bundle[2].value == Operator::assign);
	REQUIRE(param->bundle[3].value == zero);
	REQUIRE(param->bundle[4].value == Token::Control::cmd_end);

	param = create_parameter("let i = ?");
	REQUIRE(static_cast<bool>(root(*param)));
	REQUIRE(param->bundle.empty());

	param = create_parameter("let i = 0 + 0");
	REQUIRE(!root(*param));
	REQUIRE(param->bundle.size() == 7);
	REQUIRE(param->bundle[0].value == Token::Keyword::let);
	REQUIRE(param->bundle[1].value.is_type<Token::Identifier>());
	REQUIRE(param->bundle[2].value == Operator::assign);
	REQUIRE(param->bundle[3].value == zero);
	REQUIRE(param->bundle[4].value == Operator::plus);
	REQUIRE(param->bundle[5].value == zero);
	REQUIRE(param->bundle[6].value == Token::Control::cmd_end);

	param = create_parameter("let i: int = 0");
	REQUIRE(!root(*param));
	REQUIRE(param->bundle.size() == 8);
	REQUIRE(param->bundle[0].value == Token::Keyword::let);
	REQUIRE(param->bundle[1].value.is_type<Token::Identifier>());
	REQUIRE(param->bundle[2].value == Token::Control::type_definition);
	REQUIRE(param->bundle[3].value == Token::Array_dimension{ 0 });
	REQUIRE(param->bundle[4].value.is_type<Token::Identifier>());
	REQUIRE(param->bundle[5].value == Operator::assign);
	REQUIRE(param->bundle[6].value == zero);
	REQUIRE(param->bundle[7].value == Token::Control::cmd_end);
}

TEST_CASE("any of", "[tokenizer]")
{
	const auto pair = any_of(*create_parameter("false"), "true", "false");
	REQUIRE(pair.second);
	REQUIRE(pair.first == 1);
}

TEST_CASE("numbers", "[tokenizer]")
{
	using Type = Token::Number::Type;

	const auto parse = [](const char* value) {
		INFO("Expression:" << value);
		const auto param = create_parameter(value);
		REQUIRE(!number(*param));
		REQUIRE(param->bundle.size() == 1);
		REQUIRE(param->bundle.front().value.is_type<Token::Number>());
		return param->bundle.begin()->value.get<Token::Number>();
	};

	SECTION("integrals")
	{
		auto num = parse("0");
		REQUIRE(num.type == Type::i);
		REQUIRE(num.value.i == 0);

		num = parse("255");
		REQUIRE(num.type == Type::i);
		REQUIRE(num.value.i == 255);

		num = parse("22222");
		REQUIRE(num.type == Type::i);
		REQUIRE(num.value.i == 22222);

		num = parse("22222u");
		REQUIRE(num.type == Type::u);
		REQUIRE(num.value.u == 22222u);

		num = parse("13i16");
		REQUIRE(num.type == Type::i16);
		REQUIRE(num.value.i16 == 13);

		num = parse("-47163i32");
		REQUIRE(num.type == Type::i32);
		REQUIRE(num.value.i32 == -47163);

		num = parse("78647163u64");
		REQUIRE(num.type == Type::u64);
		REQUIRE(num.value.u64 == 78647163);

		// hex
		num = parse("0x16");
		REQUIRE(num.type == Type::i);
		REQUIRE(num.value.i == 0x16);

		num = parse("0Xffffu16");
		REQUIRE(num.type == Type::u16);
		REQUIRE(num.value.u16 == 0xffff);

		// octal
		num = parse("0777");
		REQUIRE(num.type == Type::i);
		REQUIRE(num.value.i == 0777);

		// binary
		num = parse("0b11111111u8");
		REQUIRE(num.type == Type::u8);
		REQUIRE(num.value.u8 == 255);

		// over- and underflow
		REQUIRE(number(*create_parameter("0u8")) == Code::success);
		REQUIRE(number(*create_parameter("255u8")) == Code::success);
		REQUIRE(number(*create_parameter("256u8")) == Code::number_overflow);

		REQUIRE(number(*create_parameter("127i8")) == Code::success);
		REQUIRE(number(*create_parameter("-128i8")) == Code::success);
		REQUIRE(number(*create_parameter("128i8")) == Code::number_overflow);
		REQUIRE(number(*create_parameter("-129i8")) == Code::number_underflow);
	}

	SECTION("floating points")
	{
		auto num = parse("0.0f");
		REQUIRE(num.type == Type::f32);
		REQUIRE(num.value.f32 == 0.0f);

		num = parse("1.0F");
		REQUIRE(num.type == Type::f32);
		REQUIRE(num.value.f32 == 1.0f);

		num = parse("0.0");
		REQUIRE(num.type == Type::f64);
		REQUIRE(num.value.f64 == 0.0);

		num = parse("1.0");
		REQUIRE(num.type == Type::f64);
		REQUIRE(num.value.f64 == 1.0);

		num = parse("-1.0");
		REQUIRE(num.type == Type::f64);
		REQUIRE(num.value.f64 == -1.0);
	}

	SECTION("bad numbers")
	{
		REQUIRE(number(*create_parameter("")) == Code::bad_number);
		REQUIRE(number(*create_parameter("?")) == Code::bad_number);
		REQUIRE(number(*create_parameter("-")) == Code::bad_number);
		REQUIRE(number(*create_parameter("+")) == Code::bad_number);
		REQUIRE(number(*create_parameter("-1u")) == Code::unsigned_cannot_be_negative);
		REQUIRE(number(*create_parameter("255u7")) == Code::bad_number);
	}
}

TEST_CASE("string", "[tokenizer]")
{
	const auto parse = [](const char* p, const char* str) {
		const auto param = create_parameter(p);
		REQUIRE(!string(*param));
		REQUIRE(param->bundle.size() == 1);
		REQUIRE(param->bundle.front().value.is_type<Token::String>());

		const auto mem = param->bundle.begin()->value.get<Token::String>().memory;
		REQUIRE(mem.size() == std::char_traits<char>::length(str) + 1);
		REQUIRE(std::equal(mem.begin(), mem.end() - 1, str,
		                   [](bia::util::Byte left, char right) { return static_cast<char>(left) == right; }));
	};

	parse(R"("hello world!")", "hello world!");
	parse(R"("hi\aasd\bqwe\vasd\tasd\fasdw\bqwe\nwqd\rdasd\\awd\"ad\"")",
	      "hi\aasd\bqwe\vasd\tasd\fasdw\bqwe\nwqd\rdasd\\awd\"ad\"");
}

TEST_CASE("identifiers", "[tokenizer]")
{
	REQUIRE(!identifier(*create_parameter("some_id")));
	REQUIRE(identifier(*create_parameter("let")).code == Code::bad_identifier);
	REQUIRE(!identifier(*create_parameter("lettuce")));
	REQUIRE(identifier(*create_parameter("import ")).code == Code::bad_identifier);
}

TEST_CASE("seperators", "[tokenizer]")
{
	const auto consumed = [](const char* str) -> int {
		const auto param = create_parameter(str);
		return static_cast<bool>(spacer(*param)) ? -1
		                                         : static_cast<int>(param->reader.location().character_offset);
	};

	REQUIRE(consumed("") == 0);
	REQUIRE(consumed(" \t\f\v") == 4);
	REQUIRE(consumed("asd \r\f") == -1);
	REQUIRE(consumed("+asd \r\f") == 0);
	REQUIRE(consumed("/* kartoffel */asd") == 15);
	REQUIRE(consumed(" +") == 1);
}

TEST_CASE("single expression", "[tokenizer]")
{
	auto param = create_parameter("0");
	REQUIRE(!single_expression(*param));
	REQUIRE(param->bundle.size() == 1);
	REQUIRE(param->bundle[0].value.is_type<Token::Number>());

	param = create_parameter("false");
	REQUIRE(!single_expression(*param));
	REQUIRE(param->bundle.size() == 1);
	REQUIRE(param->bundle[0].value == Token::Keyword::false_);

	param = create_parameter("not false");
	REQUIRE(!single_expression(*param));
	REQUIRE(param->bundle.size() == 2);
	REQUIRE(param->bundle[0].value == Operator::logical_not);
	REQUIRE(param->bundle[1].value == Token::Keyword::false_);

	param = create_parameter("1+2");
	REQUIRE(!single_expression(*param));
	REQUIRE(param->bundle.size() == 3);
	REQUIRE(param->bundle[0].value.is_type<Token::Number>());
	REQUIRE(param->bundle[1].value == Operator::plus);
	REQUIRE(param->bundle[2].value.is_type<Token::Number>());

	param = create_parameter("true+15");
	REQUIRE(!single_expression(*param));
	REQUIRE(param->bundle.size() == 3);
	REQUIRE(param->bundle[0].value == Token::Keyword::true_);
	REQUIRE(param->bundle[1].value == Operator::plus);
	REQUIRE(param->bundle[2].value.is_type<Token::Number>());

	param = create_parameter("3 * (4 - 11)");
	REQUIRE(!single_expression(*param));
	REQUIRE(param->bundle.size() == 7);
	REQUIRE(param->bundle[0].value.is_type<Token::Number>());
	REQUIRE(param->bundle[1].value == Operator::multiply);
	REQUIRE(param->bundle[2].value == Token::Control::bracket_open);
	REQUIRE(param->bundle[3].value.is_type<Token::Number>());
	REQUIRE(param->bundle[4].value == Operator::minus);
	REQUIRE(param->bundle[5].value.is_type<Token::Number>());
	REQUIRE(param->bundle[6].value == Token::Control::bracket_close);

	param = create_parameter("foo.asd");
	REQUIRE(!single_expression(*param));
	REQUIRE(param->bundle.size() == 3);
	REQUIRE(param->bundle[0].value.is_type<Token::Identifier>());
	REQUIRE(param->bundle[1].value == Operator::member_access);
	REQUIRE(param->bundle[2].value.is_type<Token::Identifier>());

	param = create_parameter("\"kartoffel\".q");
	REQUIRE(!single_expression(*param));
	REQUIRE(param->bundle.size() == 3);
	REQUIRE(param->bundle[0].value.is_type<Token::String>());
	REQUIRE(param->bundle[1].value == Operator::member_access);
	REQUIRE(param->bundle[2].value.is_type<Token::Identifier>());

	param = create_parameter("foo()");
	REQUIRE(!single_expression(*param));
	REQUIRE(param->bundle.size() == 3);
	REQUIRE(param->bundle[0].value.is_type<Token::Identifier>());
	REQUIRE(param->bundle[1].value == Operator::function_call_open);
	REQUIRE(param->bundle[2].value == Operator::function_call_close);

	param = create_parameter("foo(x, 45)");
	REQUIRE(!single_expression(*param));
	REQUIRE(param->bundle.size() == 6);
	REQUIRE(param->bundle[0].value.is_type<Token::Identifier>());
	REQUIRE(param->bundle[1].value == Operator::function_call_open);
	REQUIRE(param->bundle[2].value.is_type<Token::Identifier>());
	REQUIRE(param->bundle[3].value == Token::Control::comma);
	REQUIRE(param->bundle[4].value.is_type<Token::Number>());
	REQUIRE(param->bundle[5].value == Operator::function_call_close);
}

TEST_CASE("if statement", "[tokenizer]")
{
	auto param = create_parameter("if true { }");
	REQUIRE(!if_stmt(*param));
	REQUIRE(param->bundle.size() == 3);
	REQUIRE(param->bundle[0].value == Token::Keyword::if_);
	REQUIRE(param->bundle[1].value == Token::Keyword::true_);
	REQUIRE(param->bundle[2].value.is_type<Token::Batch>());

	param = create_parameter("if true { } else if 0 {}");
	REQUIRE(!if_stmt(*param));
	REQUIRE(param->bundle.size() == 6);
	REQUIRE(param->bundle[0].value == Token::Keyword::if_);
	REQUIRE(param->bundle[1].value == Token::Keyword::true_);
	REQUIRE(param->bundle[2].value.is_type<Token::Batch>());
	REQUIRE(param->bundle[3].value == Token::Keyword::else_if);
	REQUIRE(param->bundle[4].value.is_type<Token::Number>());
	REQUIRE(param->bundle[5].value.is_type<Token::Batch>());

	param = create_parameter("if 1 { } else if false {} else { let x = 0 }");
	REQUIRE(!if_stmt(*param));
	REQUIRE(param->bundle.size() > 9);
	REQUIRE(param->bundle[0].value == Token::Keyword::if_);
	REQUIRE(param->bundle[1].value.is_type<Token::Number>());
	REQUIRE(param->bundle[2].value.is_type<Token::Batch>());
	REQUIRE(param->bundle[3].value == Token::Keyword::else_if);
	REQUIRE(param->bundle[4].value == Token::Keyword::false_);
	REQUIRE(param->bundle[5].value.is_type<Token::Batch>());
	REQUIRE(param->bundle[6].value == Token::Keyword::else_);
	REQUIRE(param->bundle[7].value.is_type<Token::Batch>());
	REQUIRE(param->bundle[8].value == Token::Keyword::let);
	// other tokens
}

TEST_CASE("while statement", "[tokenizer]")
{
	auto param = create_parameter("while true { }");
	REQUIRE(!root(*param));
	REQUIRE(param->bundle.size() == 4);
	REQUIRE(param->bundle[0].value == Token::Keyword::while_);
	REQUIRE(param->bundle[1].value == Token::Keyword::true_);
	REQUIRE(param->bundle[2].value.is_type<Token::Batch>());
	REQUIRE(param->bundle[3].value == Token::Control::cmd_end);

	param = create_parameter("while 1 {\nlet x = 0\n}");
	REQUIRE(!root(*param));
	REQUIRE(param->bundle.size() > 4);
	REQUIRE(param->bundle[0].value == Token::Keyword::while_);
	REQUIRE(param->bundle[1].value.is_type<Token::Number>());
	REQUIRE(param->bundle[2].value.is_type<Token::Batch>());
	REQUIRE(param->bundle[3].value == Token::Keyword::let);
	// other tokens
	REQUIRE(param->bundle.back().value == Token::Control::cmd_end);
}

TEST_CASE("import statement", "[tokenizer]")
{
	auto param = create_parameter("import hello_world");
	REQUIRE(!import_stmt(*param));
	REQUIRE(param->bundle.size() == 2);
	REQUIRE(param->bundle[0].value == Token::Keyword::import);
	REQUIRE(param->bundle[1].value.is_type<Token::Identifier>());
}
