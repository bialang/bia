#ifndef BIA_MEMORY_GC_ROOT_HPP_
#define BIA_MEMORY_GC_ROOT_HPP_

#include <bia/util/gsl.hpp>
#include <cstddef>
#include <memory>
#include <mutex>

namespace bia {
namespace memory {
namespace gc {

class GC;

/// Defines the root for the search tree for the marking phase during garbage collection. This class is not
/// thread-safe.
class Root
{
public:
	Root(const Root& copy) = delete;
	~Root() noexcept;
	void* at(std::size_t index);
	void put(std::size_t index, void* ptr);
	Root& operator=(const Root& copy) = delete;

private:
	friend GC;
	typedef util::Span<void**> Data;

	GC* _parent = nullptr;
	Data _data;
	std::mutex _mutex;

	Root(GC* parent, std::size_t size) noexcept;
};

} // namespace gc
} // namespace memory
} // namespace bia

#endif
