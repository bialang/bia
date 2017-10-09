#pragma once


namespace bia
{
namespace api
{
namespace grammar
{

enum BIA_GRAMMAR_RULE : size_t
{
	BGR_ROOT,

	BGR_VARIABLE_DECLARATION,
	BGR_VARIABLE_DECLARATION_HELPER_0,
	BGR_IF,
	BGR_IF_HELPER_0,

	BGR_VALUE_RAW,
	BGR_INSTANTIATION,
	BGR_PARAMETER,
	BGR_PARAMETER_ITEM_ACCESS,
	BGR_PARAMETER_HELPER_0,
	BGR_PARAMETER_HELPER_1,

	BGR_MATH_FACTOR,
	BGR_MATH_FACTOR_HELPER_0,
	BGR_MATH_TERM,
	BGR_MATH_TERM_HELPER_0,
	BGR_MATH_TERM_HELPER_1,

	BGR_MATH_EXPRESSION,
	BGR_MATH_EXPRESSION_HELPER_0,

	BGR_VALUE,
	BGR_VALUE_HELPER_0,
	BGR_VALUE_HELPER_1,
	BGR_MEMBER,
	BGR_MEMBER_HELPER_0,
	BGR_MEMBER_HELPER_1,
	BGR_MEMBER_HELPER_2,

	BGR_RULE_COUNT
};

enum BIA_VALUE
{
	BV_NUMBER = 1,
	BV_TRUE,
	BV_FALSE,
	BV_NULL,
	BV_MEMBER
};

enum BIA_MEMBER
{
	BM_INSTANTIATION = 1,
	BM_STRING,
	BM_IDENTIFIER,
};

enum BIA_VALUE_OPERATOR
{
	BVO_LOGICAL_AND = 1,
	BVO_LOGICAL_OR
};

enum NUMBER_ID
{
	NI_INTEGER,
	NI_DOUBLE,
	NI_FLOAT,

	NI_NUMBER_ID_MASK = 0xf
};

}
}
}