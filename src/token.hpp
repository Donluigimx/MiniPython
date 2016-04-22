#ifndef TOKEN
#define TOKEN

namespace Token
{
	enum {
		NEWLINE = 0,
		TAB,
		IDENTIFIER,
		INTEGER,
		FLOAT,
		ADD,
		SUB,
		MUL,
		DIV,
		COLON,
		LESS,
		GREATER,
		LESS_OR_EQUAL,
		GREATER_OR_EQUAL,
		EQUAL,
		DOUBLE_EQUAL,
		NOT_EQUAL,
		PARENTHESES_O,
    	PARENTHESES_C,
    	INDENT,
    	DEDENT,
    	IF,
    	ELIF,
    	ELSE,
    	WHILE,
    	PRINT,
		END_OF_FILE,
    	ERROR = 666
	};
};

#endif
