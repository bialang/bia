#pragma once

#include "rule_id.hpp"
#include "token_bundle.hpp"

#include <stream/input_stream.hpp>
#include <string/encoding/encoder.hpp>
#include <vector>

namespace bia {
namespace tokenizer {

enum class TOKEN_ACTION
{
	FAILED,
	SUCCEEDED
};

struct rule_parameter
{
	string::encoding::encoder& encoder;
	token_bundle bundle;

	rule_parameter(string::encoding::encoder& encoder) : encoder(encoder)
	{}
};

typedef TOKEN_ACTION (*rule_function_type)(stream::input_stream&, rule_parameter&);

class rule
{
public:
	typedef int flag_type;

	enum FLAG : flag_type
	{
		F_NONE = 0,
		F_OR   = 0x1,
	};

	void run(stream::input_stream& input, rule_parameter& parameter);

private:
	RULE_ID id;
	int flags;
	std::vector<rule_function_type> rules;
};

} // namespace tokenizer
} // namespace bia