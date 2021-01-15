#ifndef BIA_COMPILER_SYMBOL_BUILDER_HPP_
#define BIA_COMPILER_SYMBOL_BUILDER_HPP_

#include "../type/definition.hpp"

#include <bia/bytecode/op_code.hpp>
#include <bia/resource/view.hpp>
#include <bia/util/variant.hpp>

namespace bia {
namespace compiler {
namespace symbol {

struct Location
{
	std::size_t offset;
};

struct Variable
{
	Location location;
	type::Definition* definition;
};

class Manager;

class Builder
{
public:
	Builder(const Builder& copy) = delete;
	Builder(Builder&& move) noexcept;
	~Builder();

	void build();
	void definition(type::Definition* def) noexcept;
	type::Definition* definition() const noexcept;
	Location location() const noexcept;
	Builder& operator=(const Builder& copy) = delete;
	Builder& operator=(Builder&& move) noexcept;

private:
	friend Manager;
	Manager* _manager = nullptr;
	Location _location;
	type::Definition* _definition = nullptr;
	resource::View _name;

	Builder(Manager* manager, resource::view name, Location location);
	void _drop() noexcept;
};

} // namespace symbol
} // namespace compiler
} // namespace bia

#endif
