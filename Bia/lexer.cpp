#include "lexer.hpp"
#include "lexer_token.hpp"
#include "exception.hpp"
#include "utf8.hpp"


namespace bia
{
namespace grammar
{

void lexer::set_rule(grammar_rule && _rule)
{
	auto _rule_id = _rule.id();

	if (_rule_id < BGR_RULE_COUNT) {
		_rules[_rule_id] = std::move(_rule);
	} else {
		throw BIA_IMPLEMENTATION_EXCEPTION("Invalid rule id.");
	}
}

void lexer::lex(stream::buffer_input_stream & _input, report_receiver & _receiver, machine::machine_context & _context) const
{
	report_bundle _bundle;
	encoding::utf8 encoder;
	stream::buffer_input_stream::cursor_type _last_available = 0;

	while (_input.available() != _last_available) {
		_last_available = _input.available();
		_bundle.reset();

		// Remove all leading whitespaces
		lexer_token::whitespace_deleter<flags::starting_padding_opt_token, true>(_input, &encoder);

		// Mark input buffer start
		auto _mark = _input.mark();

		// Run root
		token_param _param{};

		_param.bundle = &_bundle;
		_param.rules = _rules;
		_param.token_id = 0;
		_param.context = &_context;
		_param.schein = &_receiver.schein();
		_param.encoder = &encoder;
		_param.default_codec = stream::string_stream::CODEC::UTF8;

		try {
			_rules[BGR_ROOT].run(_input, _param);
		} catch (const exception::limitation_error&) {
			// Reset
			auto _buffer = _input.buffer();

			fwrite(_buffer.first, 1, _buffer.second - _buffer.first, stderr);
			_input.reset(_mark);

			break;
		}

		// Report
		if (_bundle.size() > 0) {
			_receiver.report(_bundle.begin(), _bundle.end());
		}
	}
}

}
}