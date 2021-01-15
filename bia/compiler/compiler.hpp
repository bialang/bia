#ifndef BIA_COMPILER_COMPILER_HPP_
#define BIA_COMPILER_COMPILER_HPP_

#include "symbol/manager.hpp"

#include <bia/bytecode/instructor.hpp>
#include <bia/tokenizer/token/receiver.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/variant.hpp>
#include <ostream>
#include <utility>

namespace bia {
namespace compiler {

class Compiler : public tokenizer::token::Receiver
{
public:
	using token = tokenizer::token::Token;

	Compiler(std::ostream& instructions) noexcept;
	void receive(util::span<const token*> tokens, resource::Manager& manager) override;

private:
	bytecode::Instructor _instructor;
	symbol::Manager _symbols;
};

} // namespace compiler
} // namespace bia

#endif
