#include "interpreter_rule.hpp"
#include "exception.hpp"

#include <memory>


namespace bia
{
namespace grammar
{

interpreter_rule::interpreter_rule() noexcept
{
	_id = 0;
	_flags = F_NONE;
}

interpreter_rule::interpreter_rule(report::rule_type _id, uint32_t _flags, std::vector<bia_token_function> && _tokens) noexcept : _tokens(std::move(_tokens))
{
	this->_id = _id;
	this->_flags = _flags;
}

bool interpreter_rule::run_rule(stream::input_stream & _input, token_param _token_param) const
{
	const auto _begin_size = _token_param.bundle->size();
	const auto _begin_mark = _input.mark();
	auto _wrapper_function = [&](void*) {
		auto _added = _token_param.bundle->size() - _begin_size;

		if (_flags & F_WRAP_UP && _added) {
			// Wrap up
			if (_added > 1) {
				// Update begin
				auto _begin = _token_param.bundle->begin() + _begin_size;

				_begin->content.end = _token_param.bundle->end();
			} // Don't report empty children
			else if (_flags & F_DONT_REPORT_EMPTY) {
				_token_param.bundle->rollback(_begin_size);
			} // Emtpy child
			else {
				auto _begin = _token_param.bundle->begin() + _begin_size;

				_begin->type = report::TYPE::EMPTY_CHILD;
				_begin->content.end = _begin;
			}
		}
	};
	std::unique_ptr<void, decltype(_wrapper_function)> _auto_wrapper(&_wrapper_function, _wrapper_function);
	
	// Begin of wrap up
	begin_wrap_up(_token_param);

	// Match all tokens
	for (size_t i = 0, cond = _tokens.size(); i < cond; ++i) {
		// Set current id if for token
		_token_param.token_id = i + 1;

		do {
			token_output _output{};

			// Mark position in case of an error
			auto _mark = _input.mark();

			// Match token
			switch (_tokens[i](_input, _token_param, _output)) {
			case ACTION::REPORT:
			{
				_output.content.rule_id = _id;
				_output.content.token_id = _token_param.token_id;

				_token_param.bundle->add(_output.content);
			}
			case ACTION::DONT_REPORT:
			{
				// One match suffices
				if (_flags & F_OR) {
					return true;
				}

				// Move on
				break;
			}
			case ACTION::REPORT_AND_LOOP:
			{
				_output.content.rule_id = _id;
				_output.content.token_id = _token_param.token_id;

				_token_param.bundle->add(_output.content);
			}
			case ACTION::DONT_REPORT_AND_LOOP:
				continue;
			case ACTION::ERROR:
			{
				// Can't match rest of the rule
				_token_param.bundle->rollback(_begin_size);

				// OK, move on
				if (_flags & F_OR) {
					_input.reset(_mark);

					break;
				}
				
				// Hard reset
				_input.reset(_begin_mark);

				return false;
			}
			default:
				throw BIA_IMPLEMENTATION_EXCEPTION("Invalid case.");
			}

			break;
		} while (true);
	}

	return (_flags & F_OR) == 0;
}

report::rule_type interpreter_rule::get_id() const noexcept
{
	return _id;
}

void interpreter_rule::begin_wrap_up(token_param _token_param) const
{
	if (_flags & F_WRAP_UP) {
		report begin{};

		begin.type = report::TYPE::BEGIN;
		begin.rule_id = _id;
		begin.token_id = _token_param.token_id;

		_token_param.bundle->add(begin);
	}
}

}
}