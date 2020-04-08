#ifndef BIA_BVM_BVM_HPP_
#define BIA_BVM_BVM_HPP_

#include <util/gsl.hpp>

namespace bia {
namespace bvm {

class bvm
{
public:
	void execute(const util::byte* first, const util::byte* last);
};

} // namespace bvm
} // namespace bia

#endif