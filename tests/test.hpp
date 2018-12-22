#pragma once

#include <map>
#include <cstring>
#include <exception>
#include <typeinfo>
#include <cstdarg>
#include <utility>
#include <functional>
#include <cstdio>
#include <stdexcept>
#include <string>


#define BEGIN_DECLARE_TESTS bool _tests_initialized = [] () {
#define END_DECLARE_TESTS return true; }();


class test
{
public:
	class assert_error : public std::runtime_error
	{
	public:
		using std::runtime_error::runtime_error;
	};

	static void add(const char * _name, void(*_test)())
	{
		_tests.emplace(std::make_pair(_name, [_test](void *& _object) {
			_test();
		}));
	}
	template<typename Class>
	static void add(const char * _name, void(Class::*_test)())
	{
		_tests.emplace(std::make_pair(_name, [_test] (void *& _object) {
			if (!_object) {
				_object = new Class();
			}

			(reinterpret_cast<Class*>(_object)->*_test)();
		}));
		_destructor = [](void * _object) {
			delete reinterpret_cast<Class*>(_object);
		};
	}
	static void assert_equals(const char * _actual, const char * _expected, const std::string & _message)
	{
		assert(!std::strcmp(_actual, _expected), _message);
	}
	template<typename Type>
	static void assert_equals(Type _actual, Type _expected, const std::string & _message)
	{
		assert(_actual == _expected, _message);
	}
	static void assert_true(bool _condition, const std::string & _message)
	{
		assert(_condition, _message);
	}
	static void assert_false(bool _condition, const std::string & _message)
	{
		assert(!_condition, _message);
	}
	static void fail(const std::string & _message)
	{
		assert(false, _message);
	}
	static bool test_main(const char * _mode)
	{
		void * _object = nullptr;

		try {
			// Test all
			if (!_mode) {
				for (auto & _test : _tests) {
					try {
						_test.second(_object);
					} catch (...) {
						_mode = _test.first;

						throw;
					}
				}
			} else {
				auto _test = _tests.find(_mode);

				// Test not found
				if (_test == _tests.end()) {
					error("Test %s not found", _mode);

					return false;
				} else {
					_test->second(_object);
				}
			}

			_destructor(_object);

			return true;
		} catch (const assert_error & e) {
			error("%s failed: %s", _mode, e.what());
		} catch (const std::exception & e) {
			error("%s threw %s: %s", _mode, typeid(e).name(), e.what());
		} catch (...) {
			error("%s threw an exception", _mode);
		}

		_destructor(_object);

		return false;
	}

private:
	struct cstring_compare
	{
		bool operator()(const char * _left, const char * _right) const
		{
			return std::strcmp(_left, _right) < 0;
		}
	};

	typedef std::map<const char*, std::function<void(void*&)>, cstring_compare> tests_type;

	static tests_type _tests;
	static void(*_destructor)(void*);

	static void assert(bool _condition, const std::string & _message)
	{
		if (!_condition) {
			throw assert_error(_message);
		}
	}
	static void error(const char * _message...)
	{
		va_list _args;
		va_start(_args, _message);

		fprintf(stderr, "[error]: ");
		vfprintf(stderr, _message, _args);
		putc('\n', stderr);

		va_end(_args);
	}
};
