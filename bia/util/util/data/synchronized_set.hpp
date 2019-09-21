#pragma once

#include <memory>
#include <mutex>


namespace bia
{
namespace util
{
namespace data
{


template<typename Container, typename Mutex>
class synchronized_set
{
public:
	typedef Container::value_type value_type;

	synchronized_set(std::size_t container_count)
	{
		containers = new Container*[container_count] {};
		this->container_count = container_count;

		for (std::size_t i = 0; i < container_count; ++i) {
			containers[i] = new Container();
		}
	}
	void insert(const value_type& x)
	{

	}
	void insert(value_type&& x)
	{

	}
	void erase(const value_type& x)
	{

	}
private:
	Mutex mutex;
	Container* containers[];
	std::size_t container_count;
};

}
}
}