#pragma once

#include <cstdint>
#include <map>

#include "output_stream.hpp"
#include "op_code.hpp"
#include "report.hpp"
#include "index_map.hpp"
#include "string_manager.hpp"
#include "name_manager.hpp"
#include "member.hpp"


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

	typedef stream::output_stream::cursor_type position_t;
	typedef void(virtual_translator::*ccr_function_t)(const index&, const index&);



	virtual_translator(stream::output_stream & _output);
	void open_scope();
	//void close_scope(member_index_t _variable_count);
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
	void instantiate_int(const index & _member, int64_t _value);
	void instantiate_double(const index & _member, double _value);
	void instantiate_string(const index & _member, string_manager::utf8_index_t _value);
	void test(const index & _member);
	void execute(const index & _member, const index * _destination);
	void execute_count(const index & _member, const index * _destination, framework::member::parameter_count_t _count);
	void execute_format(const index & _member, const index * _destination, const char * _format, framework::member::parameter_count_t _count);
	void pass_parameter(const index & _member);
	void pass_test();
	template<typename Type>
	void pass_immediate(Type _value)
	{
		op_code::write_i_type(*_output, OC_PUSH_IMMEDIATE, _value);
	}
	void clone(const index & _member, const index & _destination);
	void refer(const index & _member, const index & _destination);
	void copyof(const index & _member, const index & _destination);
	void operator_call(const index & _member, const index * _destination, framework::operator_t _operator, const index & _right);
	void operator_call_immediate(const index & _member, const index * _destination, framework::operator_t _operator, int64_t _value);
	void operator_call_immediate(const index & _member, const index * _destination, framework::operator_t _operator, double _value);
	void operator_call_immediate_reverse(const index & _member, const index * _destination, framework::operator_t _operator, int64_t _value);
	void operator_call_immediate_reverse(const index & _member, const index * _destination, framework::operator_t _operator, double _value);
	void test_call(const index & _member);
	void test_call(const index & _member, framework::operator_t _operator, const index & _right);
	void test_call_immediate(const index & _member, framework::operator_t _operator, int64_t _value);
	void test_call_immediate(const index & _member, framework::operator_t _operator, double _value);
	void test_call_immediate_reverse(const index & _member, framework::operator_t _operator, int64_t _value);
	void test_call_immediate_reverse(const index & _member, framework::operator_t _operator, double _value);
	//position_t create_local_variables();
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
	const utility::index_map & member_map() noexcept;
	/**
	 * Converts the member name to an index.
	 *
	 * @since 3.72.149.810
	 * @date 14-Jan-19
	 *
	 * @param _name The name of the member.
	 *
	 * @throws See utility::index_map::get_or_insert().
	 *
	 * @return Its index.
	*/
	member_index to_member(grammar::report::member_t _name);
	/**
	 * Converts the index to a temp member index.
	 *
	 * @since 3.72.149.810
	 * @date 14-Jan-19
	 *
	 * @param _index The index value.
	 *
	 * @return The temp member index.
	*/
	temp_index to_temp(member_index_t _index) noexcept;
	/**
	 * Converts the index to a local member index.
	 *
	 * @since 3.72.149.810
	 * @date 14-Jan-19
	 *
	 * @param _index The index value.
	 *
	 * @return The local member index.
	*/
	local_index to_local(member_index_t _index) noexcept;

private:
	/** The current output stream. */
	stream::output_stream * _output;
	/** The end position of the setup. */
	position_t _setup_end_pos;
	/** The position before the temp member creation. */
	position_t _temp_member_pos;
	/** The index map for all global variables. */
	utility::index_map _member_map;
};

}
}
}