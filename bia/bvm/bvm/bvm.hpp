#ifndef BIA_BVM_BVM_HPP_
#define BIA_BVM_BVM_HPP_

#include "context.hpp"

#include <util/gsl.hpp>

namespace bia {
namespace bvm {

class bvm
{
public:
	static void execute(context& context, const util::byte* first, const util::byte* last);
};

} // namespace bvm
} // namespace bia

#endif