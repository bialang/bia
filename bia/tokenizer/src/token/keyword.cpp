#include "tokenizer/token/keyword.hpp"

namespace bia {
namespace tokenizer {
namespace token {

exception::syntax_details keyword(const char* keyword, std::istream& input,
                                  string::encoding::encoder& encoder, resource_manager& resource_manager)
{
	while (*keyword) {
		auto pos = input.tellg();

		if (encoder.read(input) != *keyword) {
			return { pos, "invalid keyword" };
		}
	}

	return {};
}

} // namespace token
} // namespace tokenizer
} // namespace bia
