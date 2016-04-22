##Grammar##

SINGLE_INPUT -> newline SINGLE_INPUT
			   |SIMPLE_STMT SINGLE_INPUT
			   |COMPOUND_STMT SINGLE_INPUT
			   |€

STMT -> SIMPLE_STMT
	   |COMPOUND_STMT

SIMPLE_STMT -> SMALL_STMT newline

SMALL_STMT -> DEFVAR_STMT
			 |EXPR_STMT
			 |PRINT_STMT

PRINT_STMT-> print(expr_stmt)

DEFVAR_STMT -> id = EXPR_STMT

EXPR_STMT -> COMP EQ

EQ -> == COMP EQ
	 |!= COMP EQ
	 |€

COMP -> E _COMP

_COMP -> < E _COMP
		|> E _COMP
		|<= E _COMP
		|>= E _COMP
		|€

E -> T _E

_E -> + T _E
	 |- T _E
	 |€

T -> UNARY F _T

UNARY -> + UNARY
		|- UNARY
		|€

_T -> * UNARY F _T
	 |/ UNARY F _T
	 |% UNARY F _T

F  -> id
	 |value
	 |(EXPR_STMT)

COMPOUND_STMT -> IF_STMT
				|WHILE_STMT

IF_STMT -> if EXPR_STMT : SUITE

WHILE_STMT -> while EXPR_STMT : SUITE

SUITE -> SIMPLE_STMT
		|newline indent STMT _SUITE DEDENT

_SUITE -> STMT _SUITE
		 |€