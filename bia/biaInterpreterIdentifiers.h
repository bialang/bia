#pragma once


namespace bia
{
namespace api
{
namespace grammar
{

enum BIA_GRAMMAR_RULE
{
	BGR_ROOT,
	BGR_VARIABLE_DECLARATION,
	BGR_VALUE,
	BGR_STRING
};

enum BIA_VALUE
{
	BV_NUMBER,
	BV_STRING,
	BV_TRUE,
	BV_FALSE,
	BV_NULL
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