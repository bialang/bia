#ifndef BIA_BVM_CONTEXT_HPP_
#define BIA_BVM_CONTEXT_HPP_

#include "instruction_pointer.hpp"

#include <member/member.hpp>

namespace bia {
namespace bvm {

class context
{
public:
private:
	instruction_pointer _ip;
	member::member::test_type _test_register;
};

} // namespace bvm
} // namespace bia

#endif