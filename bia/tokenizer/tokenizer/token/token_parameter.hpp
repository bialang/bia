#ifndef BIA_TOKENIZER_TOKEN_TOKEN_PARAMETER_HPP_
#define BIA_TOKENIZER_TOKEN_TOKEN_PARAMETER_HPP_

#include "../resource/manager.hpp"
#include "../resource/state.hpp"

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
		resource::state rm_state;
	};

	util::byte_istream_type& input;
	resource::manager& manager;
	string::encoding::encoder& encoder;

	state backup() const
	{
		return { input.tellg(), manager.save_state() };
	}
	void restore(const state& old)
	{
		input.seekg(old.input_pos);
		manager.restore_state(old.rm_state);
	}
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif