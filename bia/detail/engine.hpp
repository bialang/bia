#ifndef BIA_DETAIL_ENGINE_HPP_
#define BIA_DETAIL_ENGINE_HPP_

#include <bia/assembler/disassembler.hpp>
#include <bia/bvm/bvm.hpp>
#include <bia/bvm/context.hpp>
#include <bia/bvm/module/module.hpp>
#include <bia/compiler/compiler.hpp>
#include <bia/connector/connector-inl.hpp>
#include <bia/gc/gc.hpp>
#include <bia/gc/memory/simple_allocator.hpp>
#include <bia/member/function/method.hpp>
#include <bia/member/function/static_.hpp>
#include <bia/member/native/string.hpp>
#include <bia/resource/deserialize.hpp>
#include <bia/string/encoding/encoder.hpp>
#include <bia/tokenizer/bia_lexer.hpp>
#include <bia/util/finally.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/type_traits/method_info.hpp>
#include <cstring>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

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
	template<typename Functor>
	void function(util::not_null<util::czstring> name, Functor&& functor)
	{
		typedef typename std::remove_const<typename std::decay<Functor>::type>::type functor_type;

		static_assert(util::type_traits::functor_info<functor_type>::is_functor, "must be a functor");

		const auto length = std::char_traits<char>::length(name.get());
		const auto str    = static_cast<char*>(_gc.allocate(length + 1).release());
		auto name_member  = _gc.construct<member::native::string>(str);
		auto func_member =
		    _gc.construct<member::function::method<false, decltype(&functor_type::operator())>>(
		        std::forward<Functor>(functor), &functor_type::operator());

		std::memcpy(str, name.get(), length);

		str[length] = 0;

		_context.symbols().put(name_member.peek(), func_member.peek());
		name_member.start_monitor();
		func_member.start_monitor();
	}
	template<typename Module, typename... Args>
	void module(util::not_null<util::czstring> name, Args&&... args)
	{
		static_assert(std::is_base_of<bvm::module::module, Module>::value,
		              "module type must inherit bia::module::module");

		const auto length  = std::char_traits<char>::length(name.get());
		const auto str     = static_cast<char*>(_gc.allocate(length + 1).release());
		auto name_member   = _gc.construct<member::native::string>(str);
		auto module_member = _gc.construct<Module>(std::forward<Args>(args)...);

		std::memcpy(str, name.get(), length);

		str[length] = 0;

		_context.loader().add_module(name_member.peek(), module_member.peek());
		name_member.start_monitor();
		module_member.start_monitor();
	}
	void execute(std::istream& code)
	{
		tokenizer::bia_lexer lexer{ _gc.allocator() };
		auto encoder       = string::encoding::get_encoder(string::encoding::standard_encoding::utf_8);
		const auto finally = util::make_finally([encoder] { string::encoding::free_encoder(encoder); });
		std::stringstream output;
		std::stringstream resources;
		compiler::compiler compiler{ output, resources };

		lexer.lex(code, *encoder, compiler);
		compiler.finish();

		const auto bytecode          = output.str();
		const auto decoded_resources = resource::deserialize(resources, _gc);

		assembler::disassemble({ reinterpret_cast<const util::byte*>(&bytecode[0]), bytecode.size() },
		                       *decoded_resources, std::cout);
		bvm::bvm::execute(_context, { reinterpret_cast<const util::byte*>(&bytecode[0]), bytecode.size() },
		                  *decoded_resources);
	}
	gc::gc& gc() noexcept
	{
		return _gc;
	}
	bvm::context& context() noexcept
	{
		return _context;
	}

private:
	gc::gc _gc;
	bvm::context _context;
};

} // namespace detail
} // namespace bia

#endif
