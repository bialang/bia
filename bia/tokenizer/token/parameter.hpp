#ifndef BIA_TOKENIZER_TOKEN_PARAMETER_HPP_
#define BIA_TOKENIZER_TOKEN_PARAMETER_HPP_

#include "error_info.hpp"
#include "token.hpp"

#include <bia/resource/manager.hpp>
#include <bia/string/encoding/encoder.hpp>
#include <vector>

namespace bia {
namespace tokenizer {
namespace token {

struct Parameter
{
	struct State
	{
		std::istream::pos_type input_pos;
		resource::Manager::state_type rm_state;
		std::size_t bundle_state;
	};

	std::istream& input;
	resource::Manager& manager;
	string::encoding::Encoder& encoder;
	std::vector<Token>& bundle;

	State backup() const
	{
		return { input.tellg(), manager.save_state(), bundle.size() };
	}
	/**
	 * Restores the state of all parameters.
	 *
	 * @param old the old states
	 */
	void restore(const State& old)
	{
		input.seekg(old.input_pos);
		manager.restore_state(old.rm_state);
		bundle.resize(old.bundle_state);
	}
	Error_info make_error(error::Code code, int offset = 0)
	{
		Error_info err{};
		err.code = code;
		return err;
	}
	void set_optional_error(Error_info err)
	{}
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
