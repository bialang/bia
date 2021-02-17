#ifndef BIA_RESOURCE_DESERIALIZE_HPP_
#define BIA_RESOURCE_DESERIALIZE_HPP_

#include "serializer.hpp"

#include <bia/util/gsl.hpp>
#include <bia/util/variant.hpp>
#include <istream>
#include <utility>
#include <vector>

namespace bia {
namespace resource {

typedef util::Variant<util::Span<const char*>> Resource;
typedef std::vector<Resource> Resources;

/// Deserializes the resource elements from the provided data. The resources point to sections in the data.
Resources deserialize(util::Span<const util::Byte*> data);

} // namespace resource
} // namespace bia

#endif
