#ifndef BIA_GC_MEMORY_VIEW_HPP_
#define BIA_GC_MEMORY_VIEW_HPP_

#include "iterator.hpp"

namespace bia {
namespace gc {
namespace memory {

class view
{
public:
	view(iterator first, iterator last) noexcept;
	iterator begin() const;
	iterator end() const;
	int compare(const view& other) const;
	bool operator==(const view& other) const;
	bool operator!=(const view& other) const;
	bool operator<(const view& other) const;
	bool operator>(const view& other) const;
	bool operator<=(const view& other) const;
	bool operator>=(const view& other) const;

private:
	iterator _first;
	iterator _last;
};

} // namespace memory
} // namespace gc
} // namespace bia

#endif