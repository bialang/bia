#include "compiler.hpp"
#include "interpreter_ids.hpp"


namespace bia
{
namespace compiler
{

using namespace bia::grammar;

compiler::compiler(stream::output_stream & _output)// : _toolset(_output), _context(_context), _machine_schein(_context.get_allocator())
{
}

void compiler::report(const grammar::report * _begin, const grammar::report * _end)
{
	handle_root(_begin);
}

const grammar::report * compiler::handle_root(const grammar::report * _report)
{

	switch (_report->rule_id) {
	case BGR_ROOT_HELPER_0:
	{
		auto _end = _report->content.end;

		++_report;

		// Handle all reports
		while (_report < _end) {
			_report = handle_root(_report) + 1;
		}

		return _end;
	}
	case BGR_VARIABLE_DECLARATION:
		//return HandleVariableDeclaration(p_pReport->content.children);
	case BGR_IF:
		//return HandleIf(p_pReport->content.children);
	case BGR_PRINT:
		//return HandlePrint(p_pReport->content.children);
	case BGR_TEST_LOOP:
		//return HandleTestLoop(p_pReport->content.children);
	case BGR_IMPORT:
		//return HandleImport(p_pReport->content.children);
	case BGR_VALUE:
		// HandleValue<false>(p_pReport->content.children, [] {});
	default:
		BIA_COMPILER_DEV_INVALID;
	}
}

const grammar::report *  compiler::handle_number(const grammar::report * _report)
{
	using TYPE = report::TYPE;

	switch (_report->type) {
	case TYPE::INT_VALUE:
		set_return(_report->content.intValue);

		break;
	case TYPE::FLOAT_VALUE:
		set_return(_report->content.floatValue);

		break;
	case TYPE::DOUBLE_VALUE:
		set_return(_report->content.doubleValue);

		break;
	default:
		BIA_COMPILER_DEV_INVALID;
	}

	return _report;
}

const grammar::report * compiler::handle_raw_value(const grammar::report * _report)
{
	switch (_report[1].token_id) {
	case BV_NUMBER:
		break;
	case BV_TRUE:
		set_return(true);

		break;
	case BV_FALSE:
		set_return(false);

		break;
	case BV_MEMBER:
		handle_member(_report + 1);

		break;
	default:
		BIA_COMPILER_DEV_INVALID;
	}

	return _report->content.end;
}

const grammar::report * compiler::handle_member(const grammar::report * _report)
{
	

	return _report->content.end;
}

const grammar::report * compiler::handle_instantiation(const grammar::report * _report)
{
	// Set identifier
	set_return(_report[1].content.member);

	// Handle parameters

	// Instantiate

	return _report->content.end;
}

}
}