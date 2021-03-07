#ifndef BIA_COMPILER_SYMBOL_MANAGER_HPP_
#define BIA_COMPILER_SYMBOL_MANAGER_HPP_

#include <bia/internal/type/definition.hpp>
#include <bia/internal/type/system.hpp>
#include <bia/memory/allocator.hpp>
#include <bia/resource/view.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/variant.hpp>
#include <map>
#include <vector>

namespace bia {
namespace compiler {
namespace symbol {

enum class Default_int_size
{
	size_32 = 32,
	size_64 = 64,
};

struct Location
{
	std::uint32_t offset;
};

struct Variable
{
	Location location;
	const internal::type::Definition* definition;
};

/// A symbol is either a variable or a type.
typedef util::Variant<Variable, internal::type::Definition*> Symbol;

class Manager
{
public:
	typedef util::Span<const char*> string_type;
	typedef std::uint16_t index_type;

	Manager(util::Not_null<std::shared_ptr<memory::Allocator>> allocator, Default_int_size default_int_size);
	void open_scope();
	void close_scope();
	Variable create_temporary(util::Not_null<const internal::type::Definition*> type);
	void free_temporary(Variable variable);
	bool promote_temporary(const resource::View& name, const Variable& variable);
	/// Returns the symbol or an empty variant if not found.
	Symbol symbol(const resource::View& name);
	/// Returns the symbol or an empty variant if not found.
	Symbol symbol(const string_type& name);
	bool is_tos(const Variable& variable) const
	{
		BIA_EXPECTS(variable.definition);
		const auto size = util::aligned(variable.definition->size(), alignof(std::max_align_t));
		return variable.location.offset + size == _stack;
	}
	std::uint32_t stack_position() const noexcept
	{
		return _stack;
	}
	Variable push(Variable variable)
	{
		// TODO
		return variable;
	}
	void pop(Variable variable)
	{
		free_temporary(variable);
	}

private:
	typedef util::Variant<resource::View, string_type> map_key_type;
	struct Comparator
	{
		bool operator()(const map_key_type& left, const map_key_type& right) const;
	};
	typedef std::map<map_key_type, Symbol, Comparator> map_type;

	/// All defined symbols.
	map_type _symbols;
	/// Variables that were declared but not defined.
	std::map<resource::View, Location> _declared;
	/// All scopes with the latest ones at the back.
	std::vector<std::vector<map_type::const_iterator>> _scopes;
	internal::type::System _type_system;
	/// Size of the int and uint types.
	Default_int_size _default_int_size;
	std::uint32_t _stack = 0;

	void _accept_declared(const resource::View& name, Variable var);
	void _decline_declared(const resource::View& name);
	void _introduce_native_types();
	void _drop(map_type::const_iterator it);
};

} // namespace symbol
} // namespace compiler
} // namespace bia

#endif
