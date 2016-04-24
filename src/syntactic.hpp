#ifndef SYNTACTIC
#define SYNTACTIC

#include <iostream>
#include <cstring>
#include "lexic.hpp"

class Syntactic {
public:
	Syntactic();
	virtual ~Syntactic() { };

private:
	Lexic *lexic;

	void Single_Unit();
	void Stmt();
	void Small_Stmt();
	void Simple_Stmt();
	void Compound_Stmt();
	void Expr_Stmt();
	void _Expr_Stmt();
	void Expr();
	void Print_Stmt();
	void Comp();
	void _Comp();
	void Eq();
	void E();
	void _E();
	void T();
	void _T();
	void Unary();
	void F();
	void If_Stmt();
	void While_Stmt();
	void Suite();
	void _Suite();

	void Check(std::string);
	void Check(int);
};

#endif