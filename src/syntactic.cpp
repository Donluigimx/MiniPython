#include <iostream>
#include <cstring>
#include <fstream>
#include "syntactic.hpp"
#include "token.hpp"

Syntactic::Syntactic(char* filename) {
	lexic = new Lexic(filename);
	Translation_Unit();
}

void Syntactic::Translation_Unit() {
	while (lexic->type != Token::END_OF_FILE)
		Single_Unit();
}
void Syntactic::Single_Unit() {
	if (lexic->type == Token::NEWLINE) {
		lexic->Next();
	} else if (lexic->type == Token::IF || lexic->type == Token::WHILE) {
		Compound_Stmt();
		//Check(Token::NEWLINE); Idk if Franco knows that
	} else {
		Simple_Stmt();
	}
}

void Syntactic::Simple_Stmt() {
	Small_Stmt();
	Check(Token::NEWLINE);
}

void Syntactic::Small_Stmt() {
	if (lexic->type == Token::PRINT) {
		Print_Stmt();
	} else {
		Expr_Stmt();
	}
}

void Syntactic::Print_Stmt() {
	Check(Token::PRINT);
	Check("(");
	if( lexic->type != Token::PARENTHESES_C)
		Expr();
	Check(")");
}

void Syntactic::Expr_Stmt() {
	Expr();
	_Expr_Stmt();
}

void Syntactic::_Expr_Stmt() {
	if( lexic->type == Token::EQUAL ) {
		lexic->Next();
		Expr_Stmt();
	}
}

void Syntactic::Expr() {
	Comp();
	Eq();
}

void Syntactic::Eq() {
	if (lexic->type == Token::DOUBLE_EQUAL ||
		lexic->type == Token::NOT_EQUAL) {
			lexic->Next();
			Comp();
			Eq();
	 }
}

void Syntactic::Comp() {
	E();
	_Comp();
}

void Syntactic::_Comp() {
	if (lexic->type == Token::LESS ||
		lexic->type == Token::LESS_OR_EQUAL ||
	 	lexic->type == Token::GREATER ||
	 	lexic->type == Token::GREATER_OR_EQUAL) {
			lexic->Next();
			E();
			_Comp();
		}
}

void Syntactic::E() {
	T();
	_E();
}

void Syntactic::_E() {
	if (lexic->type == Token::ADD ||
		lexic->type == Token::SUB) {
			lexic->Next();
			T();
			_E();
		}
}

void Syntactic::T() {
	Unary();
	F();
	_T();
}

void Syntactic::_T() {
	if (lexic->type == Token::MUL ||
		lexic->type == Token::DIV) {
			lexic->Next();
			Unary();
			F();
			_T();
		}
}

void Syntactic::Unary() {
	if (lexic->type == Token::ADD ||
		lexic->type == Token::SUB) {
			lexic->Next();
			Unary();
		}
}

void Syntactic::F() {
	if(lexic->type == Token::IDENTIFIER)
		lexic->Next();
	else if(lexic->type == Token::INTEGER || lexic->type == Token::FLOAT)
		lexic->Next();
	else if(lexic->type == Token::PARENTHESES_O) {
		lexic->Next();
		Expr();
		Check(")");
	} else
		Error();
}

void Syntactic::Compound_Stmt() {
	if(lexic->type == Token::IF) {
		If_Stmt();
	} else {
		While_Stmt();
	}
}

void Syntactic::If_Stmt() {
	Check(Token::IF);
	Comp_Stmt();
	Check(":");
	Suite();
	while(lexic->type == Token::NEWLINE)
		lexic->Next();
	_If_Stmt();
}

void Syntactic::_If_Stmt() {
	if(lexic->type == Token::ELIF) {
		lexic->Next();
		Comp_Stmt();
		Check(":");
		Suite();
		while(lexic->type == Token::NEWLINE)
			lexic->Next();
		_If_Stmt();
	} else if (lexic->type == Token::ELSE) {
		lexic->Next();
		Check(":");
		Suite();
		while(lexic->type == Token::NEWLINE)
			lexic->Next();
	}
}

void Syntactic::While_Stmt() {
	Check(Token::WHILE);
	Comp_Stmt();
	Check(":");
	Suite();
	while(lexic->type == Token::NEWLINE)
		lexic->Next();
}

void Syntactic::Comp_Stmt() {
	E();
	List_Comp();
	Expr();
}

void Syntactic::List_Comp() {
	if (lexic->type == Token::DOUBLE_EQUAL ||
		lexic->type == Token::NOT_EQUAL ||
		lexic->type == Token::LESS ||
		lexic->type == Token::LESS_OR_EQUAL ||
	 	lexic->type == Token::GREATER ||
	 	lexic->type == Token::GREATER_OR_EQUAL) {
			lexic->Next();
		} else {
			Error();
		}
}

void Syntactic::Suite() {
	if (lexic->type == Token::NEWLINE) {
		lexic->Next();
		Check(Token::INDENT);
		Stmt();
		_Suite();
		Check(Token::DEDENT);
	} else {
		Simple_Stmt();
	}
}

void Syntactic::_Suite() {
	if (lexic->type != Token::DEDENT) {
		Stmt();
		_Suite();
	}
}

void Syntactic::Stmt() {
	if (lexic->type == Token::IF || lexic->type == Token::WHILE) {
		Compound_Stmt();
		//Check(Token::NEWLINE); Idk if Franco knows that
	} else {
		Simple_Stmt();
	}
}

void Syntactic::Check(std::string c) {
	if (lexic->symbol == c) {
		lexic->Next();
	} else {
		Error();
	}
}

void Syntactic::Check(int c) {
	if (lexic->type == c) {
		lexic->Next();
	} else {
		Error();
	}
}

void Syntactic::Error() {
	std::ofstream outFile(outFileName, std::ios_base::out);

    outFile << 0;
    outFile.close();
    exit(0);
}
