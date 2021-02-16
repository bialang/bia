#ifndef BIA_COMPILER_COMPILER_HPP_
#define BIA_COMPILER_COMPILER_HPP_

#include "symbol/manager.hpp"

#include <bia/bytecode/instructor.hpp>
#include <bia/gc/memory/allocator.hpp>
#include <bia/tokenizer/token/receiver.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/variant.hpp>
#include <ostream>
#include <bia/resource/serializer.hpp>
#include <utility>

namespace bia {
namespace compiler {

class Compiler : public tokenizer::token::Receiver
{
public:
	using Token = tokenizer::token::Token;

	Compiler(util::Not_null<std::shared_ptr<gc::memory::Allocator>> allocator,
	         std::ostream& instructions, std::ostream& resource) noexcept;
	void receive(util::Span<const Token*> tokens, resource::Manager& manager) override;

private:
	bytecode::Instructor _instructor;
	symbol::Manager _symbols;
	resource::Serializer _serializer;
};

} // namespace compiler
} // namespace bia

#endif
