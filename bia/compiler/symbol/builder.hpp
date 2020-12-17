#ifndef BIA_COMPILER_SYMBOL_BUILDER_HPP_
#define BIA_COMPILER_SYMBOL_BUILDER_HPP_

#include "../type/definition.hpp"

#include <bia/bytecode/op_code.hpp>
#include <bia/resource/view.hpp>
#include <bia/util/variant.hpp>

namespace bia {
namespace compiler {
namespace symbol {

typedef util::variant<bytecode::member::local, bytecode::member::args> location_type;

struct variable
{
	location_type location;
	type::definition* definition;
};

class manager;

class builder
{
public:
	builder(const builder& copy) = delete;
	builder(builder&& move) noexcept;
	~builder();

	void build();
	void definition(type::definition* def) noexcept;
	type::definition* definition() const noexcept;
	location_type location() const noexcept;
	builder& operator=(const builder& copy) = delete;

	builder& operator=(builder&& move) noexcept;

private:
	friend manager;
	manager* _manager = nullptr;
	location_type _location;
	type::definition* _definition = nullptr;
	resource::view _name;

	builder(manager* manager, resource::view name, location_type location);
	void _drop() noexcept;
};

} // namespace symbol
} // namespace compiler
} // namespace bia

#endif
