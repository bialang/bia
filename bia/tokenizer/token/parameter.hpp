#ifndef BIA_TOKENIZER_TOKEN_PARAMETER_HPP_
#define BIA_TOKENIZER_TOKEN_PARAMETER_HPP_

#include "bundle.hpp"

#include <bia/resource/manager.hpp>
#include <bia/string/encoding/encoder.hpp>
#include <bia/util/types.hpp>

namespace bia {
namespace tokenizer {
namespace token {

struct parameter
{
	struct state
	{
		util::byte_istream_type::pos_type input_pos;
		resource::manager::state_type rm_state;
		bundle::state_type bundle_state;
	};

	util::byte_istream_type& input;
	resource::manager& manager;
	string::encoding::encoder& encoder;
	class bundle& bundle;

	state backup() const
	{
		return { input.tellg(), manager.save_state(), bundle.save() };
	}
	/**
	 * Restores the state of all parameters.
	 *
	 * @param old the old states
	 */
	void restore(const state& old)
	{
		input.seekg(old.input_pos);
		manager.restore_state(old.rm_state);
		bundle.restore(old.bundle_state);
	}
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
