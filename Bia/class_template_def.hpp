#pragma once

#include <utility>

#include "object_variable.hpp"
#include "share_def.hpp"
#include "allocator.hpp"
#include "initiator.hpp"
#include "member_map_def.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename Type>
class class_template : public object_variable
{
public:
	struct data_pair
	{
		member_map first;
		machine::memory::allocation<force::initiator> second;

		~data_pair();
	};

	typedef utility::share<data_pair> data_type;

	class_template();
	/**
	 * Refer-Constructor.
	 *
	 * @since 3.67.135.752
	 * @date 5-Aug-18
	 *
	 * @param _data The data.
	*/
	class_template(const data_type & _data) noexcept;
	/**
	 * Destructor.
	 *
	 * @since 3.67.135.752
	 * @date 5-Aug-18
	 *
	 * @throws See data_pair::~data_pair().
	*/
	~class_template() = default;
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const override;
	virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override;
	virtual void BIA_MEMBER_CALLING_CONVENTION execute(member * _destination) override;
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_count(member * _destination, void * _reserved, parameter_count_t _count, machine::stack * _stack) override;
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_format(member * _destination, const char * _format, parameter_count_t _count, machine::stack * _stack) override;
	template<typename... Arguments>
	void set_constructor();
	virtual void BIA_MEMBER_CALLING_CONVENTION object_member(member * _destination, member_map::name_type _name) override;
	virtual int flags() const override;
	/**
	 * Returns the member map.
	 *
	 * @since 3.68.140.788
	 * @date 16-Sep-18
	 *
	 * @return A reference to the member map.
	*/
	member_map & members() noexcept;

private:
	data_type _data;
};

}
}
}
