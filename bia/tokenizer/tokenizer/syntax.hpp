#pragma once

#include "lexer.hpp"

#include <memory>

namespace bia {
namespace tokenizer {

class syntax
{
public:
	static void initialize();
	static void finalize();
	static const lexer& default_syntax() noexcept;

private:
	static std::unique_ptr<lexer> default_lexer;
};

}
}