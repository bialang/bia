#pragma once


namespace bia
{
namespace machine
{

enum class OP : unsigned char
{
	TERMINATE,	/**	Terminates the script.	*/
	OBJECTIFY,	/**	Creates or sets an object with the specified name from the data stored in the accumulator. The accumulator will be cleared. (8b hash64/4b hash32/1b size/(size)b name)	  */
	OBJECTIFY_MULTIPLE,	/**	Creates or sets multiple object (at least one) with the specified name from the data stored in the accumulator. (1b additional/{8b hash64/4b hash32/1b size/(size)b name})  */
	INSTANTIATE,	/**	Instantiates an object from the params and stores it in the accumulator. Uses the global template table. (1b param_count/8b hash64/4b hash32/1b size/(size)b name)	  */
	INSTANTIATE_ACCUMULATOR,	/**	Instantiates an object from the params and stores it in the accumulator. The template table is the accumulator. (1b param_count/8b hash64/4b hash32/1b size/(size)b name)	   */
	INCREMENT,	/**	Incrementes the specified object. (8b hash64/4b hash32/1b size/(size)b name)	*/
	DECREMENT,	/**	Decrements the specified object. (8b hash64/4b hash32/1b size/(size)b name)	*/
	STORE,	/**	Stores the last pushed object in the accumulator.	*/
	LOAD,	/**	Loads an object into the accumulator. (8b hash64/4b hash32/1b size/(size)b name)	*/
	LOAD_COPY,	/**	Loads an object into the accumulator. (8b hash64/4b hash32/1b size/(size)b name)	*/
	LOAD_FROM_ACCUMULATOR,	/**	Loads an object from the accumulator into the accumulator. (8b hash64/4b hash32)  */
	LOAD_LONG,	/**	Loads a constant int into the accumulator. (8b value)	*/
	LOAD_LONG_0,	/**	Loads	a constant zero into the accumulator.	*/
	LOAD_LONG_N1,	/**	Loads	a constant negative one into the accumulator.	*/
	LOAD_LONG_1,	/**	Loads	a constant one into the accumulator.	*/
	LOAD_LONG_2,	/**	Loads a constant two into the accumulator.	*/
	LOAD_LONG_3,	/**	Loads a constant three into the accumulator.	*/
	LOAD_LONG_5,	/**	Loads a constant five into the accumulator.	*/
	LOAD_LONG_10,	/**	Loads a constant ten into the accumulator.	*/
	LOAD_LONG_100,	/**	Loads a constant 100 into the accumulator.	*/
	LOAD_LONG_1000,	/**	Loads a constant 1000 into the accumulator.	*/
	LOAD_LONG_1000000,	/**	Loads a constant 1000.	*/
	LOAD_FLOAT,	/**	Loads a constant float into the accumulator. (4b value)	*/
	LOAD_FLOAT_0,
	LOAD_FLOAT_N1,
	LOAD_FLOAT_1,
	LOAD_DOUBLE,	/**	Loads a constant double into the accumulator. (8b value)	*/
	LOAD_DOUBLE_0,
	LOAD_DOUBLE_N1,
	LOAD_DOUBLE_1,
	LOAD_STRING,	/**	Loads a constant string.	(4b size/(size)b string)	*/
	LOAD_STRING_EMPTY,	/**	Loads an empty string. (no params)	*/
	PUSH_ACCUMULATOR,	/**	Pushes the accumulator onto the parameter stack. Does reset the accumulator. (no params)   */
	PUSH,	/**	Pushes the specified object onto the stack. (8b hash64/4b hash32/1b size/(size)b name)	*/
	PUSH_COPY,	/**	Pushes the specified object onto the stack. (8b hash64/4b hash32/1b size/(size)b name)	*/
	PUSH_LONG,	/**	Pushes a long constant. (8b value)	*/
	PUSH_LONG_0,	/**	Pushes a long zero.	*/
	PUSH_LONG_N1,	/**	Pushes a long negative one.	*/
	PUSH_LONG_1,	/**	Pushes a long one.	*/
	PUSH_LONG_2,	/**	Pushes a long two.	*/
	PUSH_LONG_3,	/**	Pushes a long three.	*/
	PUSH_LONG_5,	/**	Pushes a long five.	*/
	PUSH_LONG_10,	/**	Pushes a long ten.	*/
	PUSH_LONG_100,	/**	Pushes a long 100.	*/
	PUSH_LONG_1000,	/**	Pushes a long 1000.	*/
	PUSH_LONG_1000000,	/**	Pushes a long 1000000.	*/
	PUSH_FLOAT,	/**	Pushes a float constant. (4b value)	*/
	PUSH_FLOAT_0,
	PUSH_FLOAT_N1,
	PUSH_FLOAT_1,
	PUSH_DOUBLE,	/**	Pushes a double constant. (8b value)	*/
	PUSH_DOUBLE_0,
	PUSH_DOUBLE_N1,
	PUSH_DOUBLE_1,
	PUSH_STRING,	/**	Pushes a constant string. (4b size/(size)b string/1b zero-terminator)	*/
	PUSH_STRING_EMPTY,	/**	Pushes an empty string. (no params)	*/
	CALL,	/**	Calls a function/variable on the accumulator. (1b param_count/8b hash64/4b hash32/1b size/(size)b name)	*/
	CALL_GLOBAL,	/**	Calls a global member. (1b paramCount/8b hash64/4b hash32/1b size/(size)b name)	*/
	CALL_OPERATOR,	/**	Calls an operator on the accumulator. (4b operator_id)	*/
	CALL_SELF_OPERATOR,
	JUMP_CONDITIONAL,	/**	Jumps to the specified offset if the accumulator is non-zero. (8b offset)	*/
	JUMP_CONDITIONAL_NOT,	/**	Jumps to the specified offset if the accumulator is zero. (8b offset)	*/
	JUMP,	/**	Jumps to the specified offset. (8b offset)	*/
	PRINT_OBJECT,	/**	Prints the specified object. (8b hash64/4b hash32/1b size/(size)b name)	*/
	PRINT_ACCUMULATOR,	/**	Prints the accumulator. (no params)	*/
	DEFINE_FUNCTION, /**	Defines a function. (2b size/(size)b name/4b function_size)	*/
	MAKE_PARAMETER,	/**	Makes a parameter. (2b size/(size)b name)	*/
	RETURN,	/**	Returns an object. (8b hash64/4b hash32/1b size/(size)b name)	*/
	RETURN_ACCUMULATOR,	/**	Returns the accumulator. (no params)	*/
	RETURN_VOID,	/**	Returns void from a function. (no params)	*/
	//DELETE,	/**	Deletes the first found object. (8b hash64/4b hash32)	*/
	IMPORT,	/**	Imports a module. (2b size/(size)b module/1b zero-terminator/1b size1/(size1)b alias/1b zero-terminator/1b size2/(size2)b specific)	*/
	INCLUDE,	/**	Includes a script.	*/
	RANGE_END,
	RANGE_LONG,	/**	A range loop of the type long. The iterator must is the accumulator. (8b end/8b step/4b loop_size)	*/
	RANGE_DOUBLE,	/**	A range loop of the type double. The iterator must is the accumulator. (8b end/8b step/4b loop_size)	*/
	RANGE_FLOAT,	/**	A range loop of the type float. The iterator must is the accumulator. (4b end/4b step/4b loop_size)	*/
};

}
}