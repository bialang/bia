#ifndef BIA_BVM_BVM_HPP_
#define BIA_BVM_BVM_HPP_

#include "context.hpp"

#include <gc/root.hpp>
#include <util/gsl.hpp>

namespace bia {
namespace bvm {

class bvm
{
public:
	static void execute(context& context, util::span<const util::byte> instructions, gc::root& resources);
};

} // namespace bvm
} // namespace bia

#endif