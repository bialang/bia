#ifndef BIA_COMPILER_MANAGER_VARIABLE_HPP_
#define BIA_COMPILER_MANAGER_VARIABLE_HPP_

#include <bia/resource/view.hpp>
#include <cstdint>
#include <map>
#include <set>
#include <utility>

namespace bia {
namespace compiler {
namespace manager {

class variable
{
public:
	typedef std::uint16_t index_type;

	std::pair<index_type, bool> find(const resource::view& identifer);
	index_type add(resource::view identifer);
	index_type add_overshadower(resource::view identifer);
	index_type add_tmp(bool tos);
	index_type latest_index() const;
	bool is_tos(index_type index) const noexcept;
	std::uint8_t remove_tmp(index_type index);
	std::uint8_t remove_overshadower(const resource::view& identifer);

private:
	std::map<resource::view, index_type> _variables;
	std::map<resource::view, index_type> _overshadower;
	std::set<index_type> _holes;
	index_type _next = 0;
};

} // namespace manager
} // namespace compiler
} // namespace bia

#endif
