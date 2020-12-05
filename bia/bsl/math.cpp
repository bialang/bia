#include "math.hpp"

#include "helper.hpp"

#include <bia/connector/connector-inl.hpp>
#include <bia/error/exception.hpp>
#include <bia/gc/temporary_token.hpp>
#include <bia/member/native/integer.hpp>
#include <bia/util/gsl.hpp>
#include <cmath>

using namespace bia::bsl;

inline bia::gc::gcable<bia::member::member> sum(bia::connector::parameters_type params)
{
	bia::gc::gcable<bia::member::member> s;
	for (auto i : params.positionals()) {
		if (!s.peek()) {
			s = i;
		} else if (i) {
			s = s.peek()->operation(*i, bia::member::infix_operator::addition);
		}
	}
	return s;
}

inline bia::gc::gcable<bia::member::member> max(bia::connector::parameters_type params)
{
	bia::gc::gcable<bia::member::member> m;
	for (auto i : params.positionals()) {
		if (!m.peek() || (i && m.peek()->test(bia::member::test_operator::less, *i))) {
			m = i;
		}
	}
	return m;
}

inline bia::gc::gcable<bia::member::member> min(bia::connector::parameters_type params)
{
	bia::gc::gcable<bia::member::member> m;
	for (auto i : params.positionals()) {
		if (!m.peek() || (i && m.peek()->test(bia::member::test_operator::greater, *i))) {
			m = i;
		}
	}
	return m;
}

inline bia::gc::gcable<bia::member::member> average(bia::connector::parameters_type params)
{
	bia::gc::gcable<bia::member::member> s;
	for (auto i : params.positionals()) {
		if (!s.peek()) {
			s = i;
		} else if (i) {
			s = s.peek()->operation(*i, bia::member::infix_operator::addition);
		}
	}

	if (const auto ptr = s.peek()) {
		const bia::member::native::integer<int> count{ bia::util::narrow<int>(params.size()) };
		return ptr->operation(count, bia::member::infix_operator::division);
	}

	return s;
}

inline bia::gc::gcable<bia::member::member> absolute(bia::connector::parameters_type params)
{
	if (params.size() != 1 || !params[0]) {
		BIA_THROW(bia::error::code::null_argument);
	}

	const bia::member::native::integer<int> zero{ 0 };
	return params[0]->test(bia::member::test_operator::less, zero)
	         ? params[0]->self_operation(bia::member::self_operator::unary_minus)
	         : params[0];
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
	put_function(gc, *dict, "avg", &average);
	put_function(gc, *dict, "abs", &absolute);
	put_function(gc, *dict, "sqrt", static_cast<double (*)(double)>(&std::sqrt));
	put_function(gc, *dict, "cbrt", static_cast<double (*)(double)>(&std::cbrt));
	put_function(gc, *dict, "pow", static_cast<double (*)(double, double)>(&std::pow));
	put_function(gc, *dict, "log", static_cast<double (*)(double)>(&std::log));
	put_function(gc, *dict, "exp", static_cast<double (*)(double)>(&std::exp));
	put_function(gc, *dict, "sin", static_cast<double (*)(double)>(&std::sin));
	put_function(gc, *dict, "cos", static_cast<double (*)(double)>(&std::cos));
	put_function(gc, *dict, "tan", static_cast<double (*)(double)>(&std::tan));
	put_function(gc, *dict, "sinh", static_cast<double (*)(double)>(&std::sinh));
	put_function(gc, *dict, "cosh", static_cast<double (*)(double)>(&std::cosh));
	put_function(gc, *dict, "tanh", static_cast<double (*)(double)>(&std::tanh));
	put_function(gc, *dict, "asin", static_cast<double (*)(double)>(&std::asin));
	put_function(gc, *dict, "acos", static_cast<double (*)(double)>(&std::acos));
	put_function(gc, *dict, "atan", static_cast<double (*)(double)>(&std::atan));
	put_function(gc, *dict, "asinh", static_cast<double (*)(double)>(&std::asinh));
	put_function(gc, *dict, "acosh", static_cast<double (*)(double)>(&std::acosh));
	put_function(gc, *dict, "atanh", static_cast<double (*)(double)>(&std::atanh));
	put_function(gc, *dict, "ceil", static_cast<double (*)(double)>(&std::ceil));
	put_function(gc, *dict, "floor", static_cast<double (*)(double)>(&std::floor));
	put_function(gc, *dict, "round", static_cast<double (*)(double)>(&std::round));
	put_function(gc, *dict, "hypot", static_cast<double (*)(double, double)>(&std::hypot));
	put_gcable(gc, *dict, "pi",
	           creator::create(gc, 3.141592653589793238462643383279502884197169399375105820974));
	put_gcable(gc, *dict, "tau",
	           creator::create(gc, 2 * 3.141592653589793238462643383279502884197169399375105820974));
	put_gcable(gc, *dict, "e",
	           creator::create(gc, 2.718281828459045235360287471352662497757247093699959574966));

	return dict;
}
