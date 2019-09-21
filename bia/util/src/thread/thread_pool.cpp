#include <util/thread/thread_pool.hpp>

#include <thread>


namespace bia
{
namespace util
{
namespace thread
{

unsigned int thread_pool::hardware_concurrency() noexcept
{
	return std::thread::hardware_concurrency();
}

}
}
}