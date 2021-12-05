#ifndef BIA_RESOURCE_DESERIALIZE_HPP_
#define BIA_RESOURCE_DESERIALIZE_HPP_

#include "serializer.hpp"

#include <bia/member/object/string.hpp>
#include <bia/memory/gc/gc.hpp>
#include <bia/memory/gc/types.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/variant.hpp>
#include <istream>
#include <utility>
#include <vector>

namespace bia {
namespace resource {

typedef util::Variant<memory::gc::GC_able<member::object::String*>, memory::gc::GC_able<memory::gc::Regex*>>
  Resource;
typedef std::vector<Resource> Resources;

/// Deserializes the resource elements from the provided data. The resources point to sections in the data.
Resources deserialize(util::Span<const util::Byte*> data, memory::gc::GC& gc);

} // namespace resource
} // namespace bia

#endif
