#pragma once

#include <cstddef>
#include <cstdint>


namespace bia
{
namespace grammar
{

enum KEYWORD_ID : int32_t
{
	KI_AUTO,
	KI_FUNCTION,
	KI_NEW,
	KI_FOR,
	KI_WHILE,
	KI_UNTIL,
	KI_DO,
	KI_RETURN,
	KI_BREAK,
	KI_CONTINUE,
	KI_GOTO,
	KI_EXIT_SCOPE,
	KI_DELETE,
	KI_IF,
	KI_ELSE,
	KI_TRUE,
	KI_FALSE,
	KI_IMPORT,
	KI_INCLUDE,
	KI_FROM,
	KI_AS,
	KI_COPYOF,
	KI_REFOF,
	KI_EQUALS,
	KI_ASSIGN,
	KI_DOT,
	KI_ARROW,
	KI_COMMA,
	KI_BRACKET_OPEN,
	KI_BRACKET_CLOSE,
	KI_SCOPE_OPEN,
	KI_SCOPE_CLOSE,
	KI_SQUARE_BRACKET_OPEN,
	KI_SQUARE_BRACKET_CLOSE,
	KI_LOGICAL_AND,
	KI_LOGICAL_OR,
};

struct keyword_auto
{
	constexpr static const char * token() noexcept
	{
		return "auto";
	}
	constexpr static size_t length() noexcept
	{
		return 4;
	}
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_AUTO;
	}
};

struct keyword_function
{
	constexpr static const char * token() noexcept
	{
		return "fun";
	}
	constexpr static size_t length() noexcept
	{
		return 3;
	}
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_FUNCTION;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_NEW;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_FOR;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_WHILE;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_UNTIL;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_DO;
	}
};

struct keyword_return
{
	constexpr static const char * token() noexcept
	{
		return "return";
	}
	constexpr static size_t length() noexcept
	{
		return 6;
	}
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_RETURN;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_BREAK;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_CONTINUE;
	}
};

struct keyword_goto
{
	constexpr static const char * token() noexcept
	{
		return "goto";
	}
	constexpr static size_t length() noexcept
	{
		return 4;
	}
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_GOTO;
	}
};

struct keyword_exit_scope
{
	constexpr static const char * token() noexcept
	{
		return "exit_scope";
	}
	constexpr static size_t length() noexcept
	{
		return 10;
	}
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_EXIT_SCOPE;
	}
};

struct keyword_delete
{
	constexpr static const char * token() noexcept
	{
		return "delete";
	}
	constexpr static size_t length() noexcept
	{
		return 6;
	}
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_DELETE;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_IF;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_ELSE;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_TRUE;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_FALSE;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_IMPORT;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_INCLUDE;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_FROM;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_AS;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_COPYOF;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_REFOF;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_ASSIGN;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_DOT;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_ARROW;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_COMMA;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_BRACKET_OPEN;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_BRACKET_CLOSE;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_SCOPE_OPEN;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_SCOPE_CLOSE;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_SQUARE_BRACKET_OPEN;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_SQUARE_BRACKET_CLOSE;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_LOGICAL_AND;
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
	constexpr static KEYWORD_ID string_id() noexcept
	{
		return KI_LOGICAL_OR;
	}
};

}
}