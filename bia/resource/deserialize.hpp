#ifndef BIA_RESOURCE_DESERIALIZE_HPP_
#define BIA_RESOURCE_DESERIALIZE_HPP_

#include "serializer.hpp"

#include <bia/gc/gc.hpp>
#include <bia/gc/root.hpp>
#include <bia/util/gsl.hpp>
#include <istream>
#include <utility>

namespace bia {
namespace resource {

/**
 * Deserializes the resource stream into useable resources.
 *
 * @param[in] input the resource stream
 * @param[in] gc the garbage collector
 * @returns the allocated resources
 * @throw see gc::gc::construct()
 */
std::unique_ptr<gc::root> deserialize(std::istream& input, gc::gc& gc);
std::pair<serializer::size_type, serializer::size_type>
    deserialize_binding(util::span<const util::byte*>& input);

} // namespace resource
} // namespace bia

#endif
