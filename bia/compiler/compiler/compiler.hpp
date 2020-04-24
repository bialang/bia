#ifndef BIA_COMPILER_COMPILER_HPP_
#define BIA_COMPILER_COMPILER_HPP_

#include "variable_manager.hpp"

#include <bytecode/writer/instruction.hpp>
#include <ostream>
#include <resource/serializer.hpp>
#include <tokenizer/token/receiver.hpp>
#include <util/variant.hpp>
#include <util/gsl.hpp>
#include <utility>

namespace bia {
namespace compiler {
namespace elve {

class present;

}

class compiler : public tokenizer::token::receiver
{
public:
	using token = tokenizer::token::token;

	compiler(std::ostream& instructions, std::ostream& resource) noexcept;
	void finish();
	void receive(util::span<const token> tokens) override;

private:
	bytecode::writer::instruction _writer;
	resource::serializer _resources;
	variable_manager _variables;

	const token* _decl(util::span<const token> tokens);
	const token* _import(util::span<const token> tokens);
	elve::present _create_present() noexcept;
};

} // namespace compiler
} // namespace bia

#endif