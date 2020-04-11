#ifndef BIA_COMPILER_COMPILER_HPP_
#define BIA_COMPILER_COMPILER_HPP_

#include "variable_manager.hpp"

#include <bytecode/writer/instruction.hpp>
#include <ostream>
#include <tokenizer/token/receiver.hpp>
#include <util/variant.hpp>
#include <utility>

namespace bia {
namespace compiler {

class compiler : public tokenizer::token::receiver
{
public:
	using token = tokenizer::token::token;

	compiler(std::ostream& output) noexcept;
	void finish();
	void receive(util::not_null<const token*> first, util::not_null<const token*> last) override;

private:
	enum class expression_value
	{
		local_member,
		global_member,
		integer,
		floating_point
	};

	typedef util::variant<std::int64_t, double> constant_variant_type;

	bytecode::writer::instruction _writer;
	variable_manager _variables;

	const token* _decl(const token* first, const token* last);
	/*std::pair<const token*,
	          util::variant<bytecode::local_member, bytecode::global_member, std::int64_t, double>>
	    _expression(const token* first, const token* last);*/
};

} // namespace compiler
} // namespace bia

#endif