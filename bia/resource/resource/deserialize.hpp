#ifndef BIA_RESOURCE_DESERIALIZE_HPP_
#define BIA_RESOURCE_DESERIALIZE_HPP_

#include <gc/gc.hpp>
#include <gc/root.hpp>
#include <istream>

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

} // namespace resource
} // namespace bia

#endif