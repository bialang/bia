#ifndef BIA_TOKENIZER_TOKEN_TOKEN_PARAMETER_HPP_
#define BIA_TOKENIZER_TOKEN_TOKEN_PARAMETER_HPP_

#include "../resource_manager.hpp"

#include <util/types.hpp>
#include <string/encoding/encoder.hpp>

namespace bia {
namespace tokenizer {
namespace token {

struct token_parameter
{
	struct state
	{
		util::byte_istream_type::pos_type input_pos;
		resource_manager::state rm_state;
	};

	util::byte_istream_type& input;
	resource_manager& resource_manager;
	string::encoding::encoder& encoder;

	state backup() const
	{
		return { input.tellg(), resource_manager.save_state() };
	}
	void restore(const state& old)
	{
		input.seekg(old.input_pos);
		resource_manager.restore_state(old.rm_state);
	}
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif