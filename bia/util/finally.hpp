#pragma once

#include <functional>
#include <utility>

namespace bia {
namespace util {

template<typename Lambda>
class Final_action
{
public:
	Final_action(const Lambda& lambda) : lambda(lambda)
	{
		run = true;
	}
	Final_action(Lambda&& lambda) : lambda(std::move(lambda))
	{
		run = true;
	}
	Final_action(const Final_action& copy) = delete;
	Final_action(Final_action&& move) : lambda(std::move(move.lambda))
	{
		run      = move.run;
		move.run = false;
	}
	~Final_action()
	{
		if (run) {
			lambda();
		}
	}
	void cancel(bool x = true) noexcept
	{
		run = !x;
	}
	bool cancelled() const noexcept
	{
		return !run;
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
