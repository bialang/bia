#include "interpreter.hpp"
#include "interpreter_tokens.hpp"
#include "exception.hpp"


namespace bia
{
namespace grammar
{

void interpreter::set_rule(report::rule_type _rule_id, interpreter_rule && _rule)
{
	if (_rule_id < _Rule_count) {
		_rules[_rule_id] = std::move(_rule);
	} else {
		throw BIA_IMPLEMENTATION_EXCEPTION("Invalid rule id.");
	}
}

size_t interpreter::interpret(const char * _buffer, size_t _length, report_receiver & _receiver) const
{
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

	return _start_length - _length;
}

}
}