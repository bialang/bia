#ifndef BIA_COMPILER_COMPILER_HPP_
#define BIA_COMPILER_COMPILER_HPP_

#include "flags.hpp"
#include "type/system.hpp"
#include "variable_manager.hpp"

#include <bia/bytecode/writer/instruction.hpp>
#include <bia/resource/serializer.hpp>
#include <bia/tokenizer/token/receiver.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/variant.hpp>
#include <ostream>
#include <utility>

namespace bia {
namespace compiler {

class compiler : public tokenizer::token::receiver
{
public:
	using token = tokenizer::token::token;

	compiler(std::ostream& instructions, std::ostream& resource) noexcept;
	void finish();
	void receive(util::span<const token*> tokens, resource::manager& manager) override;

private:
	bytecode::writer::instruction _writer;
	resource::serializer _resources;
	variable_manager _variables;
	type::system _type_system;
	flags _flags;
};

} // namespace compiler
} // namespace bia

#endif
