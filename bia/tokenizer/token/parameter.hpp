#ifndef BIA_TOKENIZER_TOKEN_PARAMETER_HPP_
#define BIA_TOKENIZER_TOKEN_PARAMETER_HPP_

#include "../reader.hpp"
#include "error_info.hpp"
#include "token.hpp"

#include <bia/resource/manager.hpp>
#include <vector>

namespace bia {
namespace tokenizer {
namespace token {

struct Parameter
{
	class Ranger
	{
	public:
		Range range() const noexcept
		{
			return { _start, _parent->reader.location() };
		}

	private:
		friend class Parameter;
		Parameter* _parent;
		Location _start;

		Ranger(Parameter& parent) noexcept : _parent{ &parent }, _start{ parent.reader.location() }
		{}
	};

	struct State
	{
		Reader::Backup reader_state;
		resource::Manager::state_type rm_state;
		std::size_t bundle_state;
	};

	Reader& reader;
	resource::Manager& manager;
	std::vector<Token>& bundle;

	State backup() const
	{
		return { reader.backup(), manager.save_state(), bundle.size() };
	}
	/**
	 * Restores the state of all parameters.
	 *
	 * @param old the old states
	 */
	void restore(const State& old)
	{
		reader.restore(old.reader_state);
		manager.restore_state(old.rm_state);
		bundle.resize(old.bundle_state);
	}
	Ranger begin_range()
	{
		return { *this };
	}
	Error_info make_error(error::Code code, Range range)
	{
		Error_info err{};
		err.code  = code;
		err.range = range;
		return err;
	}
	void set_optional_error(Error_info err)
	{}
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
