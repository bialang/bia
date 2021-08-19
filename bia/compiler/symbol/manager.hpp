#ifndef BIA_COMPILER_SYMBOL_MANAGER_HPP_
#define BIA_COMPILER_SYMBOL_MANAGER_HPP_

#include <bia/internal/namespace.hpp>
#include <bia/internal/string_key.hpp>
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

struct Local_variable : internal::Global_variable
{};

/// A symbol is either a variable or a type.
typedef util::Variant<internal::Global_variable, Local_variable, const internal::type::Definition_base*>
  Symbol;

class Manager
{
public:
	typedef util::Span<const char*> string_type;
	typedef std::uint16_t index_type;

	Manager(util::Not_null<std::shared_ptr<memory::Allocator>> allocator,
	        const internal::Namespace& global_namespace, Default_int_size default_int_size);
	void open_scope();
	void close_scope();
	error::Code drop_symbol(const internal::String_key& name);
	Local_variable create_temporary(util::Not_null<const internal::type::Definition_base*> type);
	void free_temporary(Local_variable variable);
	bool promote_temporary(const resource::View& name, const Local_variable& variable);
	/// Returns the symbol or an empty variant if not found.
	Symbol symbol(const internal::String_key& name);
	bool is_tos(const Local_variable& variable) const
	{
		BIA_EXPECTS(variable.definition);
		const auto size = util::aligned(variable.definition->size(), alignof(std::max_align_t));
		return variable.offset + size == _stack;
	}
	std::uint32_t stack_position() const noexcept
	{
		return _stack;
	}
	Local_variable push(Local_variable variable)
	{
		// TODO
		return variable;
	}
	void pop(Local_variable variable)
	{
		free_temporary(variable);
	}

private:
	typedef std::map<internal::String_key, Symbol, internal::String_comparator> map_type;

	const internal::Namespace& _global_namespace;
	/// All defined symbols.
	map_type _symbols;
	/// Variables that were declared but not defined.
	std::map<resource::View, std::size_t> _declared;
	/// All scopes with the latest ones at the back.
	std::vector<std::vector<map_type::const_iterator>> _scopes;
	/// Size of the int and uint types.
	Default_int_size _default_int_size;
	std::uint32_t _stack = 0;

	void _accept_declared(const resource::View& name, Local_variable var);
	void _decline_declared(const resource::View& name);
	// void _introduce_native_types();
	void _drop(map_type::const_iterator it);
};

} // namespace symbol
} // namespace compiler
} // namespace bia

#endif
