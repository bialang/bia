#include <algorithm>
#include <bia/gc/memory/simple_allocator.hpp>
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
	auto input = std::make_shared<std::stringstream>();
	auto enc   = get_encoder(standard_encoding::utf_8);
	auto bndl  = std::make_shared<std::vector<Token>>();
	auto manager =
	  std::make_shared<bia::resource::Manager>(std::make_shared<bia::gc::memory::simple_allocator>());
	int dummy[sizeof...(values)] = { (*input << values, 0)... };
	return { new Parameter{ *input, *manager, *enc, *bndl }, [input, manager, enc, bndl](Parameter* ptr) {
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

TEST_CASE("number", "[tokenizer]")
{
	const auto parse = [](const char* value) {
		const auto param = create_parameter(value);
		REQUIRE(!number(*param));
		REQUIRE(param->bundle.size() == 1);
		REQUIRE(param->bundle.front().value.is_type<Token::Number>());
		return param->bundle.begin()->value.get<Token::Number>();
	};

	auto num = parse("0");
	REQUIRE(num.type == Token::Number::Type::i);
	REQUIRE(num.value.i == 0);

	num = parse("255");
	REQUIRE(num.type == Token::Number::Type::i);
	REQUIRE(num.value.i == 255);

	num = parse("22222");
	REQUIRE(num.type == Token::Number::Type::i);
	REQUIRE(num.value.i == 22222);

	REQUIRE(number(*create_parameter("?")).code == bia::error::Code::bad_number);
	REQUIRE(number(*create_parameter("-")).code == bia::error::Code::bad_number);
	REQUIRE(number(*create_parameter("+")).code == bia::error::Code::bad_number);
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
	const auto consumed = [](const char* str) -> std::streamoff {
		const auto param = create_parameter(str);
		return static_cast<bool>(spacer(*param)) ? -1 : static_cast<std::streamoff>(param->input.tellg());
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
	REQUIRE(param->bundle.size() == 13);
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
