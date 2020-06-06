#ifndef BIA_DETAIL_ENGINE_HPP_
#define BIA_DETAIL_ENGINE_HPP_

#include <bia/bvm/bvm.hpp>
#include <bia/bvm/context.hpp>
#include <bia/compiler/compiler.hpp>
#include <bia/connector/connector-inl.hpp>
#include <bia/gc/gc.hpp>
#include <bia/gc/memory/simple_allocator.hpp>
#include <bia/member/function/static_.hpp>
#include <bia/member/native/string.hpp>
#include <bia/resource/deserialize.hpp>
#include <bia/string/encoding/encoder.hpp>
#include <bia/tokenizer/bia_lexer.hpp>
#include <bia/util/finally.hpp>
#include <bia/util/gsl.hpp>
#include <cstring>
#include <istream>
#include <sstream>
#include <string>

namespace bia {
namespace detail {

class engine
{
public:
	engine(std::shared_ptr<gc::memory::allocator> allocator = nullptr)
	    : _gc{ allocator ? std::move(allocator) : std::make_shared<gc::memory::simple_allocator>() },
	      _context{ std::shared_ptr<gc::gc>(&_gc, [](gc::gc*) {}) }
	{}
	template<typename Return, typename... Args>
	void function(util::not_null<util::czstring> name, Return (*func)(Args...))
	{
		const auto length = std::char_traits<char>::length(name.get());
		const auto str    = static_cast<char*>(_gc.allocate(length + 1).release());
		auto name_member  = _gc.construct<member::native::string>(str);
		auto func_member  = _gc.construct<member::function::static_<Return, Args...>>(func);

		std::memcpy(str, name.get(), length);

		str[length] = 0;

		_context.symbols().put(name_member.peek(), func_member.peek());
		name_member.start_monitor();
		func_member.start_monitor();
	}
	void execute(std::istream& code)
	{
		tokenizer::bia_lexer lexer{ _gc.allocator() };
		auto encoder = bia::string::encoding::get_encoder(bia::string::encoding::standard_encoding::utf_8);
		const auto finally =
		    bia::util::make_finally([encoder] { bia::string::encoding::free_encoder(encoder); });
		std::stringstream output;
		std::stringstream resources;
		compiler::compiler compiler{ output, resources };

		lexer.lex(code, *encoder, compiler);
		compiler.finish();

		const auto bytecode = output.str();

		bia::bvm::bvm::execute(_context,
		                       { reinterpret_cast<const bia::util::byte*>(&bytecode[0]), bytecode.size() },
		                       *bia::resource::deserialize(resources, _gc));
	}

private:
	gc::gc _gc;
	bvm::context _context;
};

} // namespace detail
} // namespace bia

#endif
