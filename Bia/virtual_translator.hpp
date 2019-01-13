#pragma once

#include <map>

#include "output_stream.hpp"
#include "op_code.hpp"


namespace bia
{
namespace machine
{
namespace virtual_machine
{

class virtual_translator
{
public:
	enum class JUMP
	{
		JUMP,
		JUMP_IF_TRUE,
		JUMP_IF_FALSE
	};

	typedef stream::output_stream::cursor_type position_type;
	typedef int32_t temp_index_type;
	typedef int32_t local_index_type;



	virtual_translator(stream::output_stream & _output)
	{
		this->_output = &_output;

		_temp_member_pos = _output.position();

		_output.write_all(OC_CREATE_TEMP_MEMBERS, temp_index_type(0));

		_setup_end_pos = _output.position();
	}
	void open_scope()
	{
	}
	/**
	 * Finalizes the ouput result.
	 *
	 * @remarks This function may only be called with the original output stream.
	 *
	 * @since 3.72.149.810
	 * @date 12-Jan-19
	 *
	 * @param _temp_count The count of temporary members.
	 *
	 * @throws See stream::output_stream::position(), stream::output_stream::write_all(), stream::output_stream::set_position() and stream::output_stream::set_beginning().
	*/
	void finalize(temp_index_type _temp_count)
	{
		// Update first instruction
		if (_temp_count) {
			// Update
			auto _current_pos = _output->position();

			_output->set_position(_temp_member_pos);
			_output->write_all(OC_CREATE_TEMP_MEMBERS, _temp_count);
			_output->set_position(_current_pos);
		} // Skip temp member creation
		else {
			_output->set_beginning(_setup_end_pos);
		}

		_output->write_all(OC_RETURN);
	}
	position_type jump(JUMP _type, position_type _destination = 0, position_type _overwrite_pos = -1)
	{
		BIA_NOT_IMPLEMENTED;
	}
	/**
	 * Retruns the output stream of the translator.
	 *
	 * @since 3.72.149.810
	 * @date 12-Jan-19
	 *
	 * @return A reference to the output stream.
	*/
	stream::output_stream & output_stream() noexcept
	{
		return *_output;
	}

private:
	/** The current output stream. */
	stream::output_stream * _output;
	/** The end position of the setup. */
	position_type _setup_end_pos;
	/** The position before the temp member creation. */
	position_type _temp_member_pos;
	std::map<void*, int> _member_index;
};

}
}
}