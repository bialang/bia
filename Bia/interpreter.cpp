#include "interpreter.hpp"
#include "interpreter_token.hpp"
#include "exception.hpp"

#include "utf8.hpp"

namespace bia
{
namespace grammar
{

void interpreter::set_rule(interpreter_rule && _rule)
{
	auto _rule_id = _rule.get_id();

	if (_rule_id < BGR_RULE_COUNT) {
		_rules[_rule_id] = std::move(_rule);
	} else {
		throw BIA_IMPLEMENTATION_EXCEPTION("Invalid rule id.");
	}
}

void interpreter::interpret(stream::input_stream & _input, report_receiver & _receiver) const
{
	report_bundle _bundle;
	encoding::utf8 encoder;

	while (_input.available()) {
		_bundle.reset();

		// Remove all leading whitespaces
		interpreter_token::whitespace_deleter<flags::starting_padding_opt_token, true>(_input, &encoder);

		// Mark input buffer start
		auto _mark = _input.mark();

		// Run root
		token_param _param;

		_param.bundle = &_bundle;
		_param.rules = _rules;
		_param.token_id = 0;
		_param.encoder = &encoder;

		try {
			_rules[BGR_ROOT].run_rule(_input, _param);
		} catch (const exception::limitation_error & ex) {
			// Reset
			_input.reset(_mark);

			break;
		}

		// Report
		_receiver.report(_bundle.begin(), _bundle.end());
	}
}

}
}