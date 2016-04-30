#include <iostream>
#include <cstring>
#include <fstream>
#include "syntactic.hpp"
#include "token.hpp"

Syntactic::Syntactic(char* filename) {
	lexic = new Lexic(filename);
	tree = Translation_Unit();
}

Node* Syntactic::Translation_Unit() {
	Program* program = new Program();
	Node* node = nullptr;
	while (lexic->type != Token::END_OF_FILE) {
		node = Single_Unit();
		if(node != nullptr){
			program->nodes.push_back(node);
		}

	}
	return program;
}

Node* Syntactic::Single_Unit() {
	Node* node = nullptr;
	if (lexic->type == Token::NEWLINE) {
		lexic->Next();
	} else if (lexic->type == Token::IF || lexic->type == Token::WHILE) {
		node = Compound_Stmt();
		//Check(Token::NEWLINE); Idk if Franco knows that
	} else {
		node = Simple_Stmt();
	}
	return node;
}

Node* Syntactic::Simple_Stmt() {
	Node* node = nullptr;
	node = Small_Stmt();
	Check(Token::NEWLINE);
	return node;
}

Node* Syntactic::Small_Stmt() {
	Node* node = nullptr;
	if (lexic->type == Token::PRINT) {
		node = Print_Stmt();
	} else {
		node = Expr_Stmt();
	}
	return node;
}

Print* Syntactic::Print_Stmt() {
	Print* pr = new Print();
	Check(Token::PRINT);
	Check("(");
	if( lexic->type != Token::PARENTHESES_C)
		pr->expr = Expr();
	Check(")");
	return pr;
}

Expression* Syntactic::Expr_Stmt() {
	Expression* ope = nullptr;
    Expression* oper = nullptr;
	ope = Expr();
	oper = _Expr_Stmt();
	if(oper != nullptr) {
		if (dynamic_cast<ID*>(ope) == NULL)
			Error();
		oper->l = ope;
	} else {
		oper = ope;
	}

	return oper;
}

Expression* Syntactic::_Expr_Stmt() {
	Expression* expr = nullptr;
	std::string aux;
	int auxt;
	if( lexic->type == Token::EQUAL ) {
		aux = lexic->symbol;
		auxt = lexic->type;
		lexic->Next();
		expr = new Assign(Expr_Stmt(),auxt,aux);
	}

	return expr;
}

Expression* Syntactic::Expr() {
	Expression* ope = nullptr;
    Expression* oper = nullptr;

	ope = comp();
	oper = Eq();

	if(oper != nullptr)
		oper->l = ope;
	else
		oper = ope;

	return oper;
}

Expression* Syntactic::Eq() {
	Expression* ope = nullptr;
    Expression* aux = nullptr;
    Expression* aux2 = nullptr;

	std::string auxs;
	int auxt;

	if (lexic->type == Token::DOUBLE_EQUAL ||
		lexic->type == Token::NOT_EQUAL) {
			auxs = lexic->symbol;
			auxt = lexic->type;
			lexic->Next();
			aux = comp();
			aux2 = Eq();
			if(aux2 != nullptr)
				aux2->l = aux;
			else
				aux2 = aux;
			ope = new Comp(aux2,auxt,auxs);
	 }

	 return ope;
}

Expression* Syntactic::comp() {
	Expression* ope = nullptr;
    Expression* oper = nullptr;

	ope = E();
	oper = _Comp();

	if(oper != nullptr)
		oper->l = ope;
	else
		oper = ope;

	return oper;
}

Expression* Syntactic::_Comp() {
	Expression* ope = nullptr;
    Expression* aux = nullptr;
    Expression* aux2 = nullptr;

	std::string auxs;
	int auxt;

	if (lexic->type == Token::LESS ||
		lexic->type == Token::LESS_OR_EQUAL ||
	 	lexic->type == Token::GREATER ||
	 	lexic->type == Token::GREATER_OR_EQUAL) {
			auxs = lexic->symbol;
			auxt = lexic->type;
			lexic->Next();
			aux = E();
			aux2 = _Comp();
			if(aux2 != nullptr)
				aux2->l = aux;
			else
				aux2 = aux;
			ope = new Comp(aux2,auxt,auxs);
		}

	return ope;
}

Expression* Syntactic::E() {
	Expression* ope = nullptr;
    Expression* oper = nullptr;

	ope = T();
	oper = _E();

	if(oper != nullptr)
		oper->l = ope;
	else
		oper = ope;

	return oper;
}

Expression* Syntactic::_E() {
	Expression* ope = nullptr;
    Expression* aux = nullptr;
    Expression* aux2 = nullptr;

	std::string auxs;
	int auxt;

	if (lexic->type == Token::ADD ||
		lexic->type == Token::SUB) {
			auxs = lexic->symbol;
			auxt = lexic->type;
			lexic->Next();
			aux = T();
			aux2 = _E();
			if(aux2 != nullptr)
				aux2->l = aux;
			else
				aux2 = aux;
			ope = new Add(aux2,auxt,auxs);
		}

	return ope;
}

Expression* Syntactic::T() {
	Expression* ope = nullptr;
    Expression* oper = nullptr;

	ope = F();
	oper = _T();

	if(oper != nullptr)
		oper->l = ope;
	else
		oper = ope;

	return oper;
}

Expression* Syntactic::_T() {
	Expression* ope = nullptr;
    Expression* aux = nullptr;
	Expression* aux2 = nullptr;

	std::string auxs;
	int auxt;

	if (lexic->type == Token::MUL ||
		lexic->type == Token::DIV) {
			auxs = lexic->symbol;
			auxt = lexic->type;
			lexic->Next();
			aux = F();
			aux2 = _T();
			if(aux2 != nullptr)
				aux2->l = aux;
			else
				aux2 = aux;
			ope = new Mul(aux2,auxt,auxs);
		}

	return ope;
}

Expression* Syntactic::unary() {
	Expression* ope = nullptr;
    Expression* aux = nullptr;

	std::string auxs;
	int auxt;

	if (lexic->type == Token::ADD ||
		lexic->type == Token::SUB) {
			auxs = lexic->symbol;
			auxt = lexic->type;
			lexic->Next();
			aux = unary();
			ope = new Unary(aux,auxt,auxs);
		}

	return ope;
}

Expression* Syntactic::F() {
	Expression* value = nullptr;
	Expression* una = nullptr;
	Expression* aux = nullptr;

	una = unary();
	if(lexic->type == Token::IDENTIFIER) {
		value = new ID(lexic->type,lexic->symbol);
		lexic->Next();
	}
	else if(lexic->type == Token::INTEGER || lexic->type == Token::FLOAT) {
		value = new Value(lexic->type,lexic->symbol);
		lexic->Next();
	}
	else if(lexic->type == Token::PARENTHESES_O) {
		lexic->Next();
		value = Expr();
		Check(")");
	} else {
		Error();
	}

	if(una != nullptr) {
		aux = una;
		while(aux->r != nullptr)
			aux = aux->r;
		aux->r = value;
		value = una;
	}
	return value;
}

Node* Syntactic::Compound_Stmt() {
	Node* node = nullptr;
	if(lexic->type == Token::IF) {
		node = If_Stmt();
	} else {
		node = While_Stmt();
	}
	return node;
}

If* Syntactic::If_Stmt() {
	If* node = nullptr;
	Expression* expr = nullptr;
	Suite* suit = nullptr;
	Else* els = nullptr;
	std::string auxs = lexic->symbol;
	int auxt = lexic->type;

	Check(Token::IF);
	expr = Comp_Stmt();
	Check(":");
	suit = suite();
	while(lexic->type == Token::NEWLINE)
		lexic->Next();
	els = _If_Stmt();
	node = new If(auxt,auxs,expr,suit,els);

	return node;
}

Else* Syntactic::_If_Stmt() {
	Else* node = nullptr;
	Suite* sui = nullptr;
	std::string auxs = lexic->symbol;
	int auxt = lexic->type;
	/*if(lexic->type == Token::ELIF) {
		lexic->Next();
		Comp_Stmt();
		Check(":");
		Suite();
		while(lexic->type == Token::NEWLINE)
			lexic->Next();
		_If_Stmt();
	} else*/ if (lexic->type == Token::ELSE) {
		lexic->Next();
		Check(":");
		sui = suite();
		while(lexic->type == Token::NEWLINE)
			lexic->Next();
		node = new Else(auxt,auxs,sui);
	}
	return node;
}

While* Syntactic::While_Stmt() {
	While* node = nullptr;
	Expression* expr = nullptr;
	Suite* sui = nullptr;

	std::string auxs = lexic->symbol;
	int auxt = lexic->type;
	Check(Token::WHILE);
	expr = Comp_Stmt();
	Check(":");
	sui = suite();
	while(lexic->type == Token::NEWLINE)
		lexic->Next();
	node = new While(auxt,auxs,expr,sui);
	return node;
}

Expression* Syntactic::Comp_Stmt() {
	Expression* exp = nullptr;
	Expression* comp = nullptr;
	Expression* expr = nullptr;
	exp = E();
	comp = List_Comp();
	expr = Expr();
	comp->l = exp;
	comp->r = expr;
	return comp;
}

Expression* Syntactic::List_Comp() {
	Expression* exp = new Comp(nullptr, lexic->type, lexic->symbol);
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
	return exp;
}

Suite* Syntactic::suite() {
	Suite* node = nullptr;
	Node* stm = nullptr;
	Suite* suite = nullptr;

	if (lexic->type == Token::NEWLINE) {
		lexic->Next();
		Check(Token::INDENT);
		stm = Stmt();
		suite = _Suite();
		Check(Token::DEDENT);
		node = new Suite();
		node->nodes.push_back(stm);
		if(suite != nullptr) {
			for(auto a: suite->nodes)
				node->nodes.push_back(a);
			delete suite;
		}
	} else {
		stm = Simple_Stmt();
		node = new Suite();
		node->nodes.push_back(stm);
	}
	return node;
}

Suite* Syntactic::_Suite() {
	Suite* node = nullptr;
	Node* stm = nullptr;
	Suite* suite = nullptr;
	if (lexic->type != Token::DEDENT) {
		stm = Stmt();
		suite = _Suite();
		node = new Suite();
		node->nodes.push_back(stm);
		if(suite != nullptr) {
			for(auto a: suite->nodes)
				node->nodes.push_back(a);
			delete suite;
		}
	}

	return node;
}

Node* Syntactic::Stmt() {
	Node* node = nullptr;
	if (lexic->type == Token::IF || lexic->type == Token::WHILE) {
		node = Compound_Stmt();
		//Check(Token::NEWLINE); Idk if Franco knows that
	} else {
		node = Simple_Stmt();
	}
	return node;
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
