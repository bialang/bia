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
	struct index
	{
		member_index_t value;
		virtual ~index() = default;

	protected:
		index() = default;
	};

	struct member_index : index
	{
	};

	enum class JUMP
	{
		JUMP,
		JUMP_IF_TRUE,
		JUMP_IF_FALSE
	};

	typedef stream::output_stream::cursor_type position_t;



	virtual_translator(stream::output_stream & _output);
	void open_scope();
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
	void finalize(member_index_t _temp_count);
	void pass_parameter(const index & _index);
	position_t jump(JUMP _type, position_t _destination = 0, position_t _overwrite_pos = -1);
	/**
	 * Retruns the output stream of the translator.
	 *
	 * @since 3.72.149.810
	 * @date 12-Jan-19
	 *
	 * @return A reference to the output stream.
	*/
	stream::output_stream & output_stream() noexcept;
	member_index member(void * _address);

private:
	/** The current output stream. */
	stream::output_stream * _output;
	/** The end position of the setup. */
	position_t _setup_end_pos;
	/** The position before the temp member creation. */
	position_t _temp_member_pos;
	std::map<void*, int> _member_index;
};

}
}
}