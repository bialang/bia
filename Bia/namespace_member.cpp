#include "namespace_member.hpp"
#include "member_map.hpp"

#include <utility>


namespace bia
{
namespace framework
{
namespace object
{

namespace_member::namespace_member(member_map && _members) noexcept : _data(std::move(_members))
{
}

namespace_member::namespace_member(const data_type & _data) noexcept : _data(_data)
{
}

void BIA_MEMBER_CALLING_CONVENTION namespace_member::print() const
{
  printf("<namespace_member at %p>\n", this);
}

void BIA_MEMBER_CALLING_CONVENTION namespace_member::copy(member * _destination)
{
  BIA_NOT_IMPLEMENTED;
}

void BIA_MEMBER_CALLING_CONVENTION namespace_member::refer(member * _destination)
{
  _destination->replace_this<namespace_member>(_data);
}

void BIA_MEMBER_CALLING_CONVENTION namespace_member::object_member(member * _destination, machine::string_manager::name_t _name)
{
  _data.get(_name)->refer(_destination);
}

}
}
}
