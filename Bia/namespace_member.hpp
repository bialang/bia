#pragma once

#include "object_variable.hpp"
#include "member_map.hpp"


namespace bia
{
namespace framework
{
namespace object
{

class namespace_member : public object_variable
{
public:
	typedef member_map data_type;

	/**
	 * Constructor.
	 *
	 * @remarks A new share will be created for the object.
	 *
	 * @since 3.67.135.753
	 * @date 7-Aug-18
	 *
	 * @param _members The known members.
	*/
	namespace_member(member_map && _members) noexcept;
	/**
	 * Refer-Constructor.
	 *
	 * @since 3.67.135.753
	 * @date 7-Aug-18
	 *
	 * @param _data The data.
	*/
	namespace_member(const data_type & _data) noexcept;
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const override;
	virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION object_member(member * _destination, machine::string_manager::name_type _name) override;

private:
	data_type _data;
};

}
}
}
