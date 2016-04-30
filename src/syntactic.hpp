#ifndef SYNTACTIC
#define SYNTACTIC

#include <iostream>
#include <cstring>
#include "node.hpp"
#include "lexic.hpp"

class Syntactic {
public:
	Syntactic(char*);
	virtual ~Syntactic() { };
	Node* tree;
private:
	Lexic *lexic;

	Node* Translation_Unit();

	Node* Single_Unit();
	Node* Stmt();
	Node* Small_Stmt();
	Node* Simple_Stmt();
	Node* Compound_Stmt();
	Expression* Expr_Stmt();
	Expression* _Expr_Stmt();
	Expression* Expr();
	Print* Print_Stmt();
	Expression* comp();
	Expression* _Comp();
	Expression* Eq();
	Expression* E();
	Expression* _E();
	Expression* T();
	Expression* _T();
	Expression* unary();
	Expression* F();
	If* If_Stmt();
	Else* _If_Stmt();
	While* While_Stmt();
	Suite* suite();
	Suite* _Suite();
	Expression* Comp_Stmt();
	Expression* List_Comp();

	void Check(std::string);
	void Check(int);

	void Error();
};

#endif
