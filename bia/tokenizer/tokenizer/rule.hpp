#pragma once

#include "rule_id.hpp"
#include "token_bundle.hpp"

#include <stream/input_stream.hpp>
#include <string/encoding/encoder.hpp>
#include <vector>
#include <initializer_list>

namespace bia {
namespace tokenizer {

enum class TOKEN_ACTION
{
	FAILED,
	SUCCEEDED
};

class rule
{
public:
	struct parameter
	{
		string::encoding::encoder& encoder;
		token_bundle bundle;

		parameter(string::encoding::encoder& encoder) : encoder(encoder)
		{}
	};

	typedef TOKEN_ACTION (*rule_function_type)(stream::input_stream&, parameter&);
	typedef int flag_type;

	enum FLAG : flag_type
	{
		F_NONE = 0,
		F_OR   = 0x1,
	};

	rule() noexcept;
	rule(RULE_ID id, flag_type flags, std::initializer_list<rule_function_type> steps);
	void run(stream::input_stream& input, parameter& param) const;

private:
	RULE_ID id;
	flag_type flags;
	std::vector<rule_function_type> steps;
};

} // namespace tokenizer
} // namespace bia