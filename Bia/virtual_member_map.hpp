#pragma once

#include <map>
#include <vector>

#include "config.hpp"
#include "member.hpp"
#include "machine_context.hpp"
#include "report.hpp"
#include "op_code.hpp"


namespace bia
{
namespace machine
{
namespace virtual_machine
{

class virtual_member_map
{
public:
	typedef std::vector<framework::member*> member_list_t;

	member_index_t get_or_insert(grammar::report::member_t _name);
	member_list_t to_member_list(machine_context & _context) const;
private:
	std::map<grammar::report::member_t, member_index_t> _member_index;
};

}
}
}