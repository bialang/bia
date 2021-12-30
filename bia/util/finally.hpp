#pragma once

#include <bia/util/type_traits/is_invokable.hpp>
#include <functional>
#include <type_traits>
#include <utility>

namespace bia {
namespace util {

template<typename Lambda>
class Final_action
{
public:
	static_assert(type_traits::Is_invokable<Lambda>::value, "Lambda must be a Callable and take no arguments");

	Final_action() noexcept = default;
	Final_action(const Lambda& lambda) : _lambda{ lambda }
	{
		_run = true;
	}
	Final_action(Lambda&& lambda) : _lambda{ std::move(lambda) }
	{
		_run = true;
	}
	Final_action(const Final_action& copy) = delete;
	Final_action(Final_action&& move) : _lambda{ std::move(move._lambda) }
	{
		std::swap(_run, move._run);
	}
	~Final_action() noexcept
	{
		if (_run) {
			_lambda();
		}
	}
	void cancel() noexcept
	{
		_run = false;
	}
	bool cancelled() const noexcept
	{
		return !_run;
	}
	template<typename Other>
	typename std::enable_if<std::is_assignable<Lambda&, Other>::value, Final_action&>::type
	  operator=(Other&& function)
	{
		if (_run) {
			_lambda();
		}
		_lambda = std::forward<Other>(function);
		_run    = true;
		return *this;
	}
	Final_action& operator=(const Final_action& copy) = delete;
	Final_action& operator                            =(Final_action&& move)
	{
		_lambda   = std::move(move._lambda);
		_run      = move._run;
		move._run = false;
		return *this;
	}

private:
	Lambda _lambda;
	bool _run = false;
};

template<typename Lambda>
inline Final_action<Lambda> finallay(Lambda&& lambda)
{
	return { std::forward<Lambda>(lambda) };
}

} // namespace util
} // namespace bia
