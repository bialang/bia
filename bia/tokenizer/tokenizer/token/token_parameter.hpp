#ifndef BIA_TOKENIZER_TOKEN_TOKEN_PARAMETER_HPP_
#define BIA_TOKENIZER_TOKEN_TOKEN_PARAMETER_HPP_

#include "../resource_manager.hpp"

#include <istream>
#include <string/encoding/encoder.hpp>

namespace bia {
namespace tokenizer {
namespace token {

struct token_parameter
{
	struct state
	{
		std::istream::pos_type input_pos;
	};

	std::istream& input;
	resource_manager& resource_manager;
	string::encoding::encoder& encoder;

	state backup() const
	{
		return { input.tellg() };
	}
	void restore(const state& old)
	{
		input.seekg(old.input_pos);
	}
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif