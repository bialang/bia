#ifndef BIA_TOKENIZER_TOKEN_PARAMETER_HPP_
#define BIA_TOKENIZER_TOKEN_PARAMETER_HPP_

#include "../reader.hpp"
#include "token.hpp"

#include <bia/error/bia_error.hpp>
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
		error::Bia_range range() const noexcept
		{
			return { _start, _parent->reader.location() };
		}

	private:
		friend class Parameter;
		Parameter* _parent;
		error::Bia_location _start;

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
	error::Bia make_error(error::Code code, error::Bia_range range)
	{
		error::Bia err{};
		err.code  = code;
		err.range = range;
		return err;
	}
	void set_optional_error(error::Bia err)
	{}
};

} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
