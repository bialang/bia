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

/// A symbol is either a variable or a type.
typedef util::Variant<Variable, type::Definition*> Symbol_type;

class Manager
{
public:
	typedef util::span<const char*> string_type;
	typedef std::uint16_t index_type;

	Manager();
	void open_scope();
	void close_scope();
	Builder declare(const resource::View& name);
	/// Returns the symbol or an empty variant if not found.
	Symbol_type symbol(const resource::View& name);
	/// Returns the symbol or an empty variant if not found.
	Symbol_type symbol(const string_type& name);

private:
	friend Builder;
	typedef util::Variant<resource::View, string_type> map_key_type;
	struct Comparator
	{
		bool operator()(const map_key_type& left, const map_key_type& right) const;
	};
	typedef std::map<map_key_type, Symbol_type, Comparator> map_type;

	/// All defined symbols.
	map_type _symbols;
	/// Variables that were declared but not defined.
	std::map<resource::View, Location> _declared;
	/// All scopes with the latest ones at the back.
	std::vector<std::vector<map_type::const_iterator>> _scopes;
	/// ID counter for all newly declared types.
	unsigned int _type_index = 0;

	void _accept_declared(const resource::view& name, Variable var);
	void _decline_declared(const resource::view& name);
};

} // namespace symbol
} // namespace compiler
} // namespace bia

#endif
