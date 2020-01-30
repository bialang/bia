#pragma once

#include <functional>
#include <utility>

namespace bia {
namespace util {

template<typename Lambda>
class finally
{
public:
	finally(const Lambda& lambda) : lambda(lambda)
	{
		run = true;
	}
	finally(Lambda&& lambda) : lambda(std::move(lambda))
	{
		run = true;
	}
	finally(const finally& copy) = delete;
	finally(finally&& move) : lambda(std::move(move.lambda))
	{
		run      = move.run;
		move.run = false;
	}
	~finally()
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
inline finally<Lambda> make_finally(Lambda&& lambda)
{
	return { std::forward<Lambda>(lambda) };
}

} // namespace util
} // namespace bia