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

	Final_action(const Lambda& lambda) : lambda{ lambda }
	{
		run = true;
	}
	Final_action(Lambda&& lambda) : lambda{ std::move(lambda) }
	{
		run = true;
	}
	Final_action(const Final_action& copy) = delete;
	Final_action(Final_action&& move) : lambda{ std::move(move.lambda) }
	{
		run      = move.run;
		move.run = false;
	}
	~Final_action() noexcept
	{
		if (run) {
			lambda();
		}
	}
	void cancel() noexcept
	{
		run = false;
	}
	bool cancelled() const noexcept
	{
		return !run;
	}
	Final_action& operator=(const Final_action& copy) = delete;
	/// Move operator.
	Final_action& operator=(Final_action&& move)
	{
		lambda   = std::move(move.lambda);
		run      = move.run;
		move.run = false;
		return *this;
	}

private:
	Lambda lambda;
	bool run;
};

template<typename Lambda>
inline Final_action<Lambda> finallay(Lambda&& lambda)
{
	return { std::forward<Lambda>(lambda) };
}

} // namespace util
} // namespace bia
