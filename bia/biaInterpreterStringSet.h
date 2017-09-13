#pragma once


namespace bia
{
namespace api
{
namespace grammar
{

struct Keyword_var
{
	constexpr static const char * Token()
	{
		return "var";
	}
	constexpr static size_t Size()
	{
		return 3;
	}
};

struct Keyword_new
{
	constexpr static const char * Token()
	{
		return "new";
	}
	constexpr static size_t Size()
	{
		return 3;
	}
};

struct Keyword_for
{
	constexpr static const char * Token()
	{
		return "for";
	}
	constexpr static size_t Size()
	{
		return 3;
	}
};

struct Keyword_while
{
	constexpr static const char * Token()
	{
		return "while";
	}
	constexpr static size_t Size()
	{
		return 5;
	}
};

struct Keyword_range
{
	constexpr static const char * Token()
	{
		return "range";
	}
	constexpr static size_t Size()
	{
		return 5;
	}
};

struct Keyword_if
{
	constexpr static const char * Token()
	{
		return "if";
	}
	constexpr static size_t Size()
	{
		return 2;
	}
};

struct Keyword_else
{
	constexpr static const char * Token()
	{
		return "else";
	}
	constexpr static size_t Size()
	{
		return 4;
	}
};

struct Keyword_true
{
	constexpr static const char * Token()
	{
		return "true";
	}
	constexpr static size_t Size()
	{
		return 4;
	}
};

struct Keyword_false
{
	constexpr static const char * Token()
	{
		return "false";
	}
	constexpr static size_t Size()
	{
		return 5;
	}
};

struct Keyword_null
{
	constexpr static const char * Token()
	{
		return "null";
	}
	constexpr static size_t Size()
	{
		return 4;
	}
};

struct Keyword_import
{
	constexpr static const char * Token()
	{
		return "import";
	}
	constexpr static size_t Size()
	{
		return 6;
	}
};

struct Keyword_from
{
	constexpr static const char * Token()
	{
		return "from";
	}
	constexpr static size_t Size()
	{
		return 4;
	}
};

struct Keyword_as
{
	constexpr static const char * Token()
	{
		return "as";
	}
	constexpr static size_t Size()
	{
		return 2;
	}
};

struct Keyword_copyof
{
	constexpr static const char * Token()
	{
		return "copyof";
	}
	constexpr static size_t Size()
	{
		return 6;
	}
};

struct Keyword_print
{
	constexpr static const char * Token()
	{
		return "print";
	}
	constexpr static size_t Size()
	{
		return 5;
	}
};

struct Keyword_println
{
	constexpr static const char * Token()
	{
		return "println";
	}
	constexpr static size_t Size()
	{
		return 7;
	}
};

struct Operator_equals
{
	constexpr static const char * Token()
	{
		return "=";
	}
	constexpr static size_t Size()
	{
		return 1;
	}
};

struct Operator_times
{
	constexpr static const char * Token()
	{
		return "*";
	}
	constexpr static size_t Size()
	{
		return 1;
	}
};

struct Operator_divide
{
	constexpr static const char * Token()
	{
		return "/";
	}
	constexpr static size_t Size()
	{
		return 1;
	}
};

struct Operator_double_divide
{
	constexpr static const char * Token()
	{
		return "//";
	}
	constexpr static size_t Size()
	{
		return 2;
	}
};

struct Operator_modulus
{
	constexpr static const char * Token()
	{
		return "%";
	}
	constexpr static size_t Size()
	{
		return 1;
	}
};

struct Operator_semicolon
{
	constexpr static const char * Token()
	{
		return ";";
	}
	constexpr static size_t Size()
	{
		return 1;
	}
};

struct Operator_comma
{
	constexpr static const char * Token()
	{
		return ",";
	}
	constexpr static size_t Size()
	{
		return 1;
	}
};

struct Operator_bracket_open
{
	constexpr static const char * Token()
	{
		return "(";
	}
	constexpr static size_t Size()
	{
		return 1;
	}
};

struct Operator_bracket_close
{
	constexpr static const char * Token()
	{
		return ")";
	}
	constexpr static size_t Size()
	{
		return 1;
	}
};

struct Charset_whitespace
{
	constexpr static const char * Token()
	{
		return "\t\n\r ";
	}
	constexpr static size_t Size()
	{
		return 4;
	}
};

}
}
}