#pragma once

#include <utility>
#include <functional>


namespace bia
{
namespace util
{

class finally
{
public:
	typedef std::function<void()> exit_type;

	finally(const exit_type& exit) : exit(exit)
	{
		run = true;
	}
	finally(exit_type&& exit) : exit(std::move(exit))
	{
		run = true;
	}
	finally(const finally& copy) = delete;
	finally(finally&& move) : exit(std::move(move.exit))
	{
		run = move.run;

		move.exit = {};
		move.run = false;
	}
	~finally()
	{
		if (run && exit) {
			exit();
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
	exit_type exit;
	bool run;
};

}
}