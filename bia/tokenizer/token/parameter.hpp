#ifndef BIA_TOKENIZER_TOKEN_PARAMETER_HPP_
#define BIA_TOKENIZER_TOKEN_PARAMETER_HPP_

#include "error_info.hpp"
#include "token.hpp"

#include <bia/resource/manager.hpp>
#include <bia/string/encoding/encoder.hpp>
#include <bia/util/types.hpp>
#include <vector>

namespace bia {
namespace tokenizer {
namespace token {

struct parameter
{
	struct state
	{
		util::byte_istream_type::pos_type input_pos;
		resource::manager::state_type rm_state;
		std::size_t bundle_state;
	};

	util::byte_istream_type& input;
	resource::manager& manager;
	string::encoding::encoder& encoder;
	std::vector<token>& bundle;

	state backup() const
	{
		return { input.tellg(), manager.save_state(), bundle.size() };
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
		bundle.resize(old.bundle_state);
	}
	error_info make_error(error::code code, int offset = 0)
	{
		error_info err{};
		err.code = code;
		return err;
	}
	void set_optional_error(error_info err)
	{}
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
