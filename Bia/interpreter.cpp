#include "interpreter.hpp"
#include "interpreter_token.hpp"
#include "exception.hpp"


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

	while (_input.available()) {
		_bundle.reset();

		// Remove all leading whitespaces
		{
			token_output _output{};

			//
		}

		// Mark input buffer start
		auto _mark = _input.mark();

		// Run root
		token_param _param;

		_param.bundle = &_bundle;
		_param.rules = _rules;
		_param.token_id = 0;

		try {
			_rules[BGR_ROOT].run_rule(_input, _param);
		} catch (const exception::limitation_error & ex) {
			// Reset
			_input.reset(_mark);
		}

		// Report
		_receiver.report(_bundle.begin(), _bundle.end());
	}
	/*
	const auto _start_length = _length;
	report_bundle _bundle;

	// Interpretation loop
	while (_length) {
		_bundle.clear();

		// Remove leading whitespace
		{
			token_output _output{};

			whitespace_deleter<STARTING_PADDING_OPTIONAL_TOKEN, true>(_buffer, _length, _output);
		}

		// Start with rule 0
		auto _processed = _rules[0].run_rule(_buffer, _length, { &_bundle, _rules, 0 });

		// Report
		if (_processed) {
			_receiver.report(_bundle.begin(), _bundle.end());

			_buffer += _processed;
			_length -= _processed;
		} else {
			break;
		}
	}

	return _start_length - _length;*/
}

}
}