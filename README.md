##Grammar##

SINGLE_INPUT -> newline
			   |SIMPLE_STMT
			   |COMPOUND_STMT

STMT -> SIMPLE_STMT
	   |COMPOUND_STMT

SIMPLE_STMT -> SMALL_STMT newline

SMALL_STMT -> EXPR_STMT
			 |PRINT_STMT

PRINT_STMT-> print(EXPR)

EXPR_STMT -> EXPR _EXPR_STMT

_EXPR_STMT -> = EXPR_STMT
			 |€

EXPR -> COMP EQ

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

IF_STMT -> if COMP_STMT : SUITE _IF_STMT

_IF_STMT -> elif COMP_STMT : SUITE _IF_STMT
		   |else : SUITE
		   |€

WHILE_STMT -> while COMP_STMT : SUITE

SUITE -> SIMPLE_STMT
		|newline indent STMT _SUITE dedent

_SUITE -> STMT _SUITE
		 |€

COMP_STMT -> E LIST_COMP EXPR

LIST_COMP -> < | > | <= | >= | == | !=
