#ifndef BIA_BVM_MODULE_HPP_
#define BIA_BVM_MODULE_HPP_

#include <cstdint>
#include <bia/gc/gc.hpp>
#include <bia/gc/object/base.hpp>
#include <bia/member/member.hpp>
#include <bia/util/gsl.hpp>

namespace bia {
namespace bvm {
namespace module {

class module : public gc::object::base
{
public:
	typedef std::uint64_t version_type;

	virtual ~module()                                            = default;
	virtual version_type version() const noexcept                = 0;
	virtual util::Not_null<member::member*> create(gc::gc& gc)   = 0;
};

} // namespace module
} // namespace bvm
} // namespace bia

#endif
