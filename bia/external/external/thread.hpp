#pragma once

#include <functional>
#include <memory>

namespace bia {
namespace external {

class thread final
{
public:
	thread(std::function<void()> target);
	~thread();
	static void yield();
	void join();
	void start();
	void interrupt();
	void daemon(bool daemon);
	bool daemon() const noexcept;
	bool alive() const noexcept;
	bool interrupted() const noexcept;

private:
	struct impl;

	std::unique_ptr<impl> pimpl;
};

} // namespace external
} // namespace bia