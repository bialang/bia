#ifndef BIA_COMPILER_SYMBOL_MANAGER_HPP_
#define BIA_COMPILER_SYMBOL_MANAGER_HPP_

#include "../type/definition.hpp"
#include "builder.hpp"

#include <bia/resource/view.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/variant.hpp>
#include <map>
#include <vector>

namespace bia {
namespace compiler {
namespace symbol {

class manager
{
public:
	typedef std::uint16_t index_type;

	enum class domain
	{
		local,
		argument
	};

	manager();
	void open_scope();
	void close_scope();
	builder declare(const resource::view& name);

private:
	friend builder;
	typedef util::span<const char*> string_type;
	typedef util::variant<resource::view, string_type> map_key_type;
	struct comparator
	{
		bool operator()(const map_key_type& left, const map_key_type& right) const;
	};
	typedef std::map<map_key_type, variable, comparator> map_type;

	map_type _variables;
	std::map<resource::view, location_type> _declared;
	std::vector<std::vector<map_type::const_iterator>> _scopes;
	std::uint16_t _index = 0;

	void _accept_declared(const resource::view& name, variable var);
	void _decline_declared(const resource::view& name);
};

} // namespace symbol
} // namespace compiler
} // namespace bia

#endif
