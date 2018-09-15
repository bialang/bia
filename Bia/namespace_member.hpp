#pragma once

#include <utility>

#include "config.hpp"
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
	 * @since 3.68.138.785
	 * @date 14-Sep-18
	 *
	 * @param _members The known members.
	*/
	BIA_EXPORT namespace_member(member_map && _members) noexcept;
	/**
	 * Refer-Constructor.
	 *
	 * @since 3.68.138.785
	 * @date 14-Sep-18
	 *
	 * @param _data The data.
	*/
	BIA_EXPORT namespace_member(const data_type & _data) noexcept;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION print() const override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override;
	BIA_EXPORT virtual void BIA_MEMBER_CALLING_CONVENTION object_member(member * _destination, machine::string_manager::name_type _name) override;
	template<typename _Ty, typename... _Args>
	void emplace_member(machine::string_manager::name_type _name, _Args &&... _args)
	{
		_data.template emplace<_Ty, _Args...>(_name, std::forward<_Args>(_args)...);
	}

private:
	data_type _data;
};

}
}
}
