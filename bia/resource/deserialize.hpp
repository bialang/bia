#ifndef BIA_RESOURCE_DESERIALIZE_HPP_
#define BIA_RESOURCE_DESERIALIZE_HPP_

#include "serializer.hpp"

#include <bia/util/gsl.hpp>
#include <bia/util/variant.hpp>
#include <istream>
#include <bia/memory/gc/gc.hpp>
#include <utility>
#include <vector>

namespace bia {
namespace resource {

typedef util::Variant<util::Span<const char*>> Resource;
typedef std::vector<Resource> Resources;

/// Deserializes the resource elements from the provided data. The resources point to sections in the data.
Resources deserialize(util::Span<const util::Byte*> data, memory::gc::GC& gc);

} // namespace resource
} // namespace bia

#endif
