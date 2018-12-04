#pragma once

#include <map>
#include <cstring>
#include <exception>
#include <typeinfo>
#include <cstdarg>
#include <utility>
#include <functional>


class test
{
public:
	static void add_test(const char * _name, std::function<void()> && _test)
	{
		_tests[_name] = std::move(_test);
	}
	template<typename Type>
	static void assert_equals(Type _actual, Type _expected, const char * _message...)
	{
		va_list _args;
		va_start(_args, _message);

		assert(_actual == _expected, _message, _args);

		va_end(_args);
	}
	static void assert_true(bool _condition, const char * _message...)
	{
		va_list _args;
		va_start(_args, _message);

		assert(_condition, _message, _args);

		va_end(_args);
	}
	static void assert_false(bool _condition, const char * _message...)
	{
		va_list _args;
		va_start(_args, _message);

		assert(!_condition, _message, _args);

		va_end(_args);
	}
	static void fail(const char * _message...)
	{

	}
	static bool test_main(const char * _mode)
	{
		try {
			// Test all
			if (!_mode) {
				for (auto & _test : _tests) {
					try {
						_test.second();
					} catch (...) {
						_mode = _test.first;
					}
				}
			} else {
				auto _test = _tests.find(_mode);

				// Test not found
				if (_test == _tests.end()) {
					error("Test %s not found", _mode);

					return false;
				} else {
					_test->second();
				}
			}

			return true;
		} catch (const std::exception & e) {
			error("%s threw %s: %s", _mode, typeid(e).name(), e.what());
		} catch (...) {
			error("%s threw an exception", _mode);
		}

		return false;
	}

private:
	struct cstring_compare
	{
		constexpr bool operator()(const char * _left, const char * _right) const
		{
			return std::strcmp(_left, _right) < 0;
		}
	};

	typedef std::map<const char*, std::function<void()>, cstring_compare> tests_type;

	static tests_type _tests;

	static void assert(bool _condition, const char * _message, va_list _args)
	{
		if (!_condition) {
			throw;
		}
	}
	static void error(const char * _message...)
	{

	}
};
