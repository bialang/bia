#pragma once

#include <cstddef>
#include <cstdint>


namespace bia
{
namespace grammar
{

enum INTERPRETER_STRING : int32_t
{
	IS_GLOBAL,
	IS_VAR,
	IS_NEW,
	IS_FOR,
	IS_WHILE,
	IS_UNTIL,
	IS_DO,
	IS_BREAK,
	IS_CONTINUE,
	IS_IF,
	IS_ELSE,
	IS_TRUE,
	IS_FALSE,
	IS_IMPORT,
	IS_INCLUDE,
	IS_FROM,
	IS_AS,
	IS_PRINT,
	IS_PRINTLN,
	IS_COPYOF,
	IS_REFOF,
	IS_EQUALS,
	IS_ASSIGN,
	IS_DOT,
	IS_ARROW,
	IS_COMMA,
	IS_BRACKET_OPEN,
	IS_BRACKET_CLOSE,
	IS_SCOPE_OPEN,
	IS_SCOPE_CLOSE,
	IS_SQUARE_BRACKET_OPEN,
	IS_SQUARE_BRACKET_CLOSE,
	IS_LOGICAL_AND,
	IS_LOGICAL_OR,
};

struct keyword_global
{
	constexpr static const char * token() noexcept
	{
		return "global";
	}
	constexpr static size_t length() noexcept
	{
		return 6;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_GLOBAL;
	}
};

struct keyword_var
{
	constexpr static const char * token() noexcept
	{
		return "var";
	}
	constexpr static size_t length() noexcept
	{
		return 3;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_VAR;
	}
};

struct keyword_new
{
	constexpr static const char * token() noexcept
	{
		return "new";
	}
	constexpr static size_t length() noexcept
	{
		return 3;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_NEW;
	}
};

struct keyword_for
{
	constexpr static const char * token() noexcept
	{
		return "for";
	}
	constexpr static size_t length() noexcept
	{
		return 3;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_FOR;
	}
};

struct keyword_while
{
	constexpr static const char * token() noexcept
	{
		return "while";
	}
	constexpr static size_t length() noexcept
	{
		return 5;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_WHILE;
	}
};

struct keyword_until
{
	constexpr static const char * token() noexcept
	{
		return "until";
	}
	constexpr static size_t length() noexcept
	{
		return 5;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_UNTIL;
	}
};

struct keyword_do
{
	constexpr static const char * token() noexcept
	{
		return "do";
	}
	constexpr static size_t length() noexcept
	{
		return 2;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_DO;
	}
};

struct keyword_break
{
	constexpr static const char * token() noexcept
	{
		return "break";
	}
	constexpr static size_t length() noexcept
	{
		return 5;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_BREAK;
	}
};

struct keyword_continue
{
	constexpr static const char * token() noexcept
	{
		return "continue";
	}
	constexpr static size_t length() noexcept
	{
		return 8;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_CONTINUE;
	}
};

struct keyword_if
{
	constexpr static const char * token() noexcept
	{
		return "if";
	}
	constexpr static size_t length() noexcept
	{
		return 2;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_IF;
	}
};

struct keyword_else
{
	constexpr static const char * token() noexcept
	{
		return "else";
	}
	constexpr static size_t length() noexcept
	{
		return 4;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_ELSE;
	}
};

struct keyword_true
{
	constexpr static const char * token() noexcept
	{
		return "true";
	}
	constexpr static size_t length() noexcept
	{
		return 4;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_TRUE;
	}
};

struct keyword_false
{
	constexpr static const char * token() noexcept
	{
		return "false";
	}
	constexpr static size_t length() noexcept
	{
		return 5;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_FALSE;
	}
};

struct keyword_import
{
	constexpr static const char * token() noexcept
	{
		return "import";
	}
	constexpr static size_t length() noexcept
	{
		return 6;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_IMPORT;
	}
};

struct keyword_include
{
	constexpr static const char * token() noexcept
	{
		return "include";
	}
	constexpr static size_t length() noexcept
	{
		return 7;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_INCLUDE;
	}
};

struct keyword_from
{
	constexpr static const char * token() noexcept
	{
		return "from";
	}
	constexpr static size_t length() noexcept
	{
		return 4;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_FROM;
	}
};

struct keyword_as
{
	constexpr static const char * token() noexcept
	{
		return "as";
	}
	constexpr static size_t length() noexcept
	{
		return 2;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_AS;
	}
};

struct keyword_print
{
	constexpr static const char * token() noexcept
	{
		return "print";
	}
	constexpr static size_t length() noexcept
	{
		return 5;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_PRINT;
	}
};

struct keyword_copyof
{
	constexpr static const char * token() noexcept
	{
		return "copyof";
	}
	constexpr static size_t length() noexcept
	{
		return 6;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_COPYOF;
	}
};

struct keyword_refof
{
	constexpr static const char * token() noexcept
	{
		return "refof";
	}
	constexpr static size_t length() noexcept
	{
		return 5;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_REFOF;
	}
};

struct operator_assign
{
	constexpr static const char * token() noexcept
	{
		return "=";
	}
	constexpr static size_t length() noexcept
	{
		return 1;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_ASSIGN;
	}
};

struct operator_dot
{
	constexpr static const char * token() noexcept
	{
		return ".";
	}
	constexpr static size_t length() noexcept
	{
		return 1;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_DOT;
	}
};

struct operator_arrow
{
	constexpr static const char * token() noexcept
	{
		return "->";
	}
	constexpr static size_t length() noexcept
	{
		return 2;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_ARROW;
	}
};

struct operator_comma
{
	constexpr static const char * token() noexcept
	{
		return ",";
	}
	constexpr static size_t length() noexcept
	{
		return 1;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_COMMA;
	}
};

struct operator_bracket_open
{
	constexpr static const char * token() noexcept
	{
		return "(";
	}
	constexpr static size_t length() noexcept
	{
		return 1;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_BRACKET_OPEN;
	}
};

struct operator_bracket_close
{
	constexpr static const char * token() noexcept
	{
		return ")";
	}
	constexpr static size_t length() noexcept
	{
		return 1;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_BRACKET_CLOSE;
	}
};

struct operator_scope_open
{
	constexpr static const char * token() noexcept
	{
		return "{";
	}
	constexpr static size_t length() noexcept
	{
		return 1;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_SCOPE_OPEN;
	}
};

struct operator_scope_close
{
	constexpr static const char * token() noexcept
	{
		return "}";
	}
	constexpr static size_t length() noexcept
	{
		return 1;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_SCOPE_CLOSE;
	}
};

struct operator_square_bracket_open
{
	constexpr static const char * token() noexcept
	{
		return "[";
	}
	constexpr static size_t length() noexcept
	{
		return 1;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_SQUARE_BRACKET_OPEN;
	}
};

struct operator_square_bracket_close
{
	constexpr static const char * token() noexcept
	{
		return "]";
	}
	constexpr static size_t length() noexcept
	{
		return 1;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_SQUARE_BRACKET_CLOSE;
	}
};

struct operator_logical_and
{
	constexpr static const char * token() noexcept
	{
		return "&&";
	}
	constexpr static size_t length() noexcept
	{
		return 2;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_LOGICAL_AND;
	}
};

struct operator_logical_or
{
	constexpr static const char * token() noexcept
	{
		return "||";
	}
	constexpr static size_t length() noexcept
	{
		return 2;
	}
	constexpr static INTERPRETER_STRING string_id() noexcept
	{
		return IS_LOGICAL_OR;
	}
};

}
}