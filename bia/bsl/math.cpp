#include "math.hpp"

#include "helper.hpp"

#include <bia/connector/connector-inl.hpp>
#include <bia/member/native/integer.hpp>
#include <cmath>

using namespace bia::bsl;

inline typename bia::member::native::integer::int_type sum(bia::connector::parameters_type params)
{
	typedef typename bia::member::native::integer::int_type int_type;

	int_type s = 0;

	for (auto i : params.positionals()) {
		if (i) {
			s += bia::member::cast::cast<int_type>(*i);
		}
	}

	return s;
}

inline typename bia::member::native::integer::int_type max(bia::connector::parameters_type params)
{
	typedef typename bia::member::native::integer::int_type int_type;

	int_type m = 0;

	for (auto i : params.positionals()) {
		if (i) {
			const auto tmp = bia::member::cast::cast<int_type>(*i);

			if (tmp > m) {
				m = tmp;
			}
		}
	}

	return m;
}

inline typename bia::member::native::integer::int_type min(bia::connector::parameters_type params)
{
	typedef typename bia::member::native::integer::int_type int_type;

	int_type m = 0;

	for (auto i : params.positionals()) {
		if (i) {
			const auto tmp = bia::member::cast::cast<int_type>(*i);

			if (tmp < m) {
				m = tmp;
			}
		}
	}

	return m;
}

math::math(gc::gc& gc) : _symbols{ _init(gc) }
{}

math::version_type math::version() const noexcept
{
	return 0;
}

bia::util::not_null<bia::member::member*> math::create(gc::gc& gc)
{
	return _symbols.get();
}

void math::gc_mark_children(bool mark) const noexcept
{
	gc::object::gc_mark(_symbols.get(), mark);
}

void math::register_gcables(gc::gc& gc) const noexcept
{
	gc.register_gcable(_symbols.get());

	for (const auto& i : _symbols->map()) {
		gc.register_gcable(i.first.get());
		gc.register_gcable(i.second.get());
	}
}

bia::member::native::dict* math::_init(gc::gc& gc)
{
	const auto dict = gc.construct<member::native::dict>().release();

	put_function(gc, *dict, "sum", &sum);
	put_function(gc, *dict, "max", &max);
	put_function(gc, *dict, "min", &min);
	put_function(gc, *dict, "sqrt", static_cast<double (*)(double)>(&std::sqrt));

	return dict;
}
