#pragma once

#include <cstddef>


namespace bia
{
namespace grammar
{

struct keyword_global
{
	constexpr static const char * token() noexcept
	{
		return "global";
	}
	constexpr static size_t size() noexcept
	{
		return 6;
	}
};

struct keyword_local
{
	constexpr static const char * token() noexcept
	{
		return "local";
	}
	constexpr static size_t size() noexcept
	{
		return 5;
	}
};

struct keyword_new
{
	constexpr static const char * token() noexcept
	{
		return "new";
	}
	constexpr static size_t size() noexcept
	{
		return 3;
	}
};

struct keyword_for
{
	constexpr static const char * token() noexcept
	{
		return "for";
	}
	constexpr static size_t size() noexcept
	{
		return 3;
	}
};

struct keyword_while
{
	constexpr static const char * token() noexcept
	{
		return "while";
	}
	constexpr static size_t size() noexcept
	{
		return 5;
	}
};

struct keyword_until
{
	constexpr static const char * token() noexcept
	{
		return "until";
	}
	constexpr static size_t size() noexcept
	{
		return 5;
	}
};

struct keyword_do
{
	constexpr static const char * token() noexcept
	{
		return "do";
	}
	constexpr static size_t size() noexcept
	{
		return 2;
	}
};

struct keyword_if
{
	constexpr static const char * token() noexcept
	{
		return "if";
	}
	constexpr static size_t size() noexcept
	{
		return 2;
	}
};

struct keyword_else
{
	constexpr static const char * token() noexcept
	{
		return "else";
	}
	constexpr static size_t size() noexcept
	{
		return 4;
	}
};

struct keyword_true
{
	constexpr static const char * token() noexcept
	{
		return "true";
	}
	constexpr static size_t size() noexcept
	{
		return 4;
	}
};

struct keyword_false
{
	constexpr static const char * token() noexcept
	{
		return "false";
	}
	constexpr static size_t size() noexcept
	{
		return 5;
	}
};

struct keyword_import
{
	constexpr static const char * token() noexcept
	{
		return "import";
	}
	constexpr static size_t size() noexcept
	{
		return 6;
	}
};

struct keyword_include
{
	constexpr static const char * token() noexcept
	{
		return "include";
	}
	constexpr static size_t size() noexcept
	{
		return 7;
	}
};

struct keyword_from
{
	constexpr static const char * token() noexcept
	{
		return "from";
	}
	constexpr static size_t size() noexcept
	{
		return 4;
	}
};

struct keyword_as
{
	constexpr static const char * token() noexcept
	{
		return "as";
	}
	constexpr static size_t size() noexcept
	{
		return 2;
	}
};

struct keyword_print
{
	constexpr static const char * token() noexcept
	{
		return "print";
	}
	constexpr static size_t size() noexcept
	{
		return 5;
	}
};

struct operator_equals
{
	constexpr static const char * token() noexcept
	{
		return "=";
	}
	constexpr static size_t size() noexcept
	{
		return 1;
	}
};

struct operator_times
{
	constexpr static const char * token() noexcept
	{
		return "*";
	}
	constexpr static size_t size() noexcept
	{
		return 1;
	}
};

struct operator_divide
{
	constexpr static const char * token() noexcept
	{
		return "/";
	}
	constexpr static size_t size() noexcept
	{
		return 1;
	}
};

struct operator_double_divide
{
	constexpr static const char * token() noexcept
	{
		return "//";
	}
	constexpr static size_t size() noexcept
	{
		return 2;
	}
};

struct operator_modulus
{
	constexpr static const char * token() noexcept
	{
		return "%";
	}
	constexpr static size_t size() noexcept
	{
		return 1;
	}
};

struct operator_dot
{
	constexpr static const char * token() noexcept
	{
		return ".";
	}
	constexpr static size_t size() noexcept
	{
		return 1;
	}
};

struct operator_arrow_access
{
	constexpr static const char * token() noexcept
	{
		return "->";
	}
	constexpr static size_t size() noexcept
	{
		return 2;
	}
};

struct operator_comma
{
	constexpr static const char * token() noexcept
	{
		return ",";
	}
	constexpr static size_t size() noexcept
	{
		return 1;
	}
};

struct operator_bracket_open
{
	constexpr static const char * token() noexcept
	{
		return "(";
	}
	constexpr static size_t size() noexcept
	{
		return 1;
	}
};

struct operator_bracket_close
{
	constexpr static const char * token() noexcept
	{
		return ")";
	}
	constexpr static size_t size() noexcept
	{
		return 1;
	}
};

struct operator_scope_open
{
	constexpr static const char * token() noexcept
	{
		return "{";
	}
	constexpr static size_t size() noexcept
	{
		return 1;
	}
};

struct operator_scope_close
{
	constexpr static const char * token() noexcept
	{
		return "}";
	}
	constexpr static size_t size() noexcept
	{
		return 1;
	}
};

struct operator_square_bracket_open
{
	constexpr static const char * token() noexcept
	{
		return "[";
	}
	constexpr static size_t size() noexcept
	{
		return 1;
	}
};

struct operator_square_bracket_close
{
	constexpr static const char * token() noexcept
	{
		return "]";
	}
	constexpr static size_t size() noexcept
	{
		return 1;
	}
};

struct operator_logical_and
{
	constexpr static const char * token() noexcept
	{
		return "&&";
	}
	constexpr static size_t size() noexcept
	{
		return 2;
	}
};

struct operator_logical_or
{
	constexpr static const char * token() noexcept
	{
		return "||";
	}
	constexpr static size_t size() noexcept
	{
		return 2;
	}
};

}
}