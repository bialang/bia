#ifndef BIA_BVM_CONTEXT_HPP_
#define BIA_BVM_CONTEXT_HPP_

#include "module/loader.hpp"

#include <array>
#include <bia/bytecode/op_code.hpp>
#include <bia/connector/connector-inl.hpp>
#include <bia/gc/gc.hpp>
#include <bia/gc/object/base.hpp>
#include <bia/member/function/generator.hpp>
#include <bia/member/function/method.hpp>
#include <bia/member/function/static_.hpp>
#include <bia/member/member.hpp>
#include <bia/member/native/dict.hpp>
#include <bia/util/gsl.hpp>
#include <memory>
#include <vector>

namespace bia {
namespace bvm {

inline std::vector<member::member*> make_list(connector::parameters_type params)
{
	std::vector<member::member*> list;

	list.reserve(params.size());

	for (auto i : params) {
		list.push_back(i);
	}

	return list;
}

inline gc::gcable<member::member> range(connector::parameters_type params)
{
	auto start = 0, end = std::numeric_limits<int>::max(), step = 1;

	if (params.size() == 1) {
		end = member::cast::cast<int>(*params[0]);
	} else if (params.size() == 2) {
		start = member::cast::cast<int>(*params[0]);
		end   = member::cast::cast<int>(*params[1]);
	} else if (params.size() == 3) {
		start = member::cast::cast<int>(*params[0]);
		end   = member::cast::cast<int>(*params[1]);
		step  = member::cast::cast<int>(*params[2]);
	}

	auto generator = [start, end, step]() mutable -> bia::gc::gcable<bia::member::member> {
		const auto current = start;

		if ((start += step, current) >= end) {
			return bia::member::function::stop_iteration;
		}

		return bia::creator::create(current);
	};

	return bia::gc::gc::active_gc()
	    ->construct<bia::member::function::generator<
	        bia::member::function::method<false, decltype(&decltype(generator)::operator())>>>(
	        generator, &decltype(generator)::operator());
}

class context : private gc::object::base
{
public:
	context(util::not_null<std::shared_ptr<gc::gc>> gc) noexcept
	    : _gc(std::move(gc.get())), _loader(_gc.get()), _builtins{
		      _gc->template construct<
		             member::function::static_<std::vector<member::member*>, connector::parameters_type>>(
		             &make_list)
		          .release(),
		      _gc->template construct<
		             member::function::static_<gc::gcable<member::member>, connector::parameters_type>>(
		             &range)
		          .release()
	      }
	{
		_gc->register_root(static_cast<gc::object::base*>(this));
	}
	~context()
	{
		_gc->deregister_root(static_cast<gc::object::base*>(this));
	}
	gc::gc& gc() noexcept
	{
		return *_gc;
	}
	member::native::dict& symbols() noexcept
	{
		return _symbols;
	}
	module::loader& loader() noexcept
	{
		return _loader;
	}
	member::member* builtin(bytecode::member::builtin builtin) const noexcept
	{
		if (static_cast<std::uint8_t>(builtin) >= _builtins.size()) {
			return nullptr;
		}

		return _builtins[static_cast<std::uint8_t>(builtin)];
	}

private:
	std::shared_ptr<gc::gc> _gc;
	member::native::dict _symbols;
	module::loader _loader;
	std::array<member::member*, 2> _builtins;

	void gc_mark_children(bool mark) const noexcept override
	{
		_symbols.gc_mark_children(mark);
		_loader.gc_mark_children(mark);

		for (const auto i : _builtins) {
			if (i) {
				gc::object::gc_mark(i, mark);
			}
		}
	}
	void register_gcables(gc::gc& gc) const noexcept override
	{
		for (const auto i : _builtins) {
			gc.register_gcable(i);
		}
	}
};

} // namespace bvm
} // namespace bia

#endif
