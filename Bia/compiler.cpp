#include "compiler.hpp"
#include "output_stream_buffer.hpp"
#include "interpreter_token.hpp"


namespace bia
{
namespace compiler
{

compiler::compiler(stream::output_stream & _output, machine::machine_context & _context) :_toolset(_output), _context(_context), _machine_schein(_context.get_allocator())
{
}

void compiler::report(const grammar::report * _begin, const grammar::report * _end)
{
	handle_root(_begin);
}

void compiler::handle_number(const grammar::report * _report)
{
	switch (_report->custom_parameter & grammar::NI_NUMBER_ID_MASK) {
	case grammar::NI_INTEGER:
		set_return(grammar::interpreter_token::parse_integer(_report->content.token.string, _report->content.token.length, _report->custom_parameter));

		break;
	case grammar::NI_FLOAT:
		set_return(grammar::interpreter_token::parse_floating_point<float>(_report->content.token.string, _report->content.token.length, _report->custom_parameter));

		break;
	case grammar::NI_DOUBLE:
		set_return(grammar::interpreter_token::parse_floating_point<double>(_report->content.token.string, _report->content.token.length, _report->custom_parameter));

		break;
	default:
		BIA_COMPILER_DEV_INVALID;
	}
}

const grammar::report * compiler::handle_raw_value(grammar::report_range _reports)
{
	switch (_reports.begin[1].token_id) {
	case grammar::BV_NUMBER:
		break;
	case grammar::BV_TRUE:
		set_return(true);

		break;
	case grammar::BV_FALSE:
		set_return(false);

		break;
	case grammar::BV_MEMBER:
		handle_member(_reports.begin[1].content.children);

		break;
	default:
		BIA_COMPILER_DEV_INVALID;
	}

	return _reports.end + 1;
}

const grammar::report * compiler::handle_member(grammar::report_range _reports)
{
	return _reports.end + 1;
}

}
}