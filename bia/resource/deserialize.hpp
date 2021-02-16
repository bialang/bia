#ifndef BIA_RESOURCE_DESERIALIZE_HPP_
#define BIA_RESOURCE_DESERIALIZE_HPP_

#include "serializer.hpp"

#include <bia/gc/gc.hpp>
#include <bia/gc/root.hpp>
#include <bia/util/gsl.hpp>
#include <istream>
#include <bia/util/variant.hpp>
#include <vector>
#include <utility>

namespace bia {
namespace resource {

typedef util::Variant<util::Span<const char*>> Resource;
typedef std::vector<Resource> Resources;

/// Deserializes the resource elements from the provided data. The resources point to sections in the data.
Resources deserialize(util::Span<const util::Byte*> data);

} // namespace resource
} // namespace bia

#endif
