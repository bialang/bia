#pragma once

#include <atomic>
#include <cstdint>

namespace bia {
namespace gc {

struct object_info
{
	/* the current mark */
	std::atomic_bool marked;
	/* whether this object is a leaf or a node */
	bool leaf;
};

} // namespace gc
} // namespace bia