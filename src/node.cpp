#include <iostream>
#include <vector>
#include "node.hpp"

void Node::print(std::ofstream &of) {
	of << "FATAL ERROR NODE" << std::endl;
	of.close();
	exit(1);
}

Expression::Expression(int i, std::string s): Node(i, s) {
	this->r = nullptr;
	this->l = nullptr;
}

void Expression::print(std::ofstream &of) {
	of << "FATAL ERROR EXPRESSION" << std::endl;
	of.close();
	exit(1);
}

Assign::Assign(Expression* rv, int i, std::string s): Expression(i,s) {
	this->l = nullptr;
	this->r = rv;
}

void Assign::print(std::ofstream &of) {
	of << "<ASIGNACION>\n";
	if(this->l != nullptr)
		this->l->print(of);
	if(this->r != nullptr)
		this->r->print(of);
	of << "</ASIGNACION>\n";
}

void ID::print(std::ofstream &of) {
	of << "<ID>" << this->symbol << "</ID>\n";
}

void Value::print(std::ofstream &of) {
	if(this->type == Token::INTEGER)
		of << "<ENTERO>" << this->symbol << "</ENTERO>\n";
	else if (this->type == Token::FLOAT)
		of << "<REAL>" << this->symbol << "</REAL>\n";
}

Add::Add(Expression* rv, int i, std::string s): Expression(i,s) {
	this-> r = rv;
	this-> l = nullptr;
}

void Add::print(std::ofstream &of) {
	of << "<SUMA value=\"" << this->symbol << "\">\n";
	if(this->l != nullptr)
		this->l->print(of);
	if(this->r != nullptr)
		this->r->print(of);
	of << "</SUMA>\n";
}

Mul::Mul(Expression* rv, int i, std::string s): Expression(i,s) {
	this->r = rv;
	this->l = nullptr;
}

void Mul::print(std::ofstream &of) {
	of << "<MULT value=\"" << this->symbol << "\">\n";
	if(this->l != nullptr)
		this->l->print(of);
	if(this->r != nullptr)
		this->r->print(of);
	of << "</MULT>\n";
}

Comp::Comp(Expression* rv, int i, std::string s): Expression(i,s) {
	this->r = rv;
	this->l = nullptr;
}

void Comp::print(std::ofstream &of) {
	std::string aux = this->symbol;
	if(aux[0] == '>') {
		aux.erase(0,1);
		aux = "&gt;"+aux;
	} else if (aux[0] == '<') {
		aux.erase(0,1);
		aux = "&lt;"+aux;
	}
	of << "<EXPRESION value=\"" << aux << "\">\n";
	if(this->l != nullptr)
		this->l->print(of);
	if(this->r != nullptr)
		this->r->print(of);
	of << "</EXPRESION>\n";
}

Unary::Unary(Expression* rv, int i, std::string s): Expression(i,s) {
	this->r = rv;
	this->l = nullptr;
}

void Unary::print(std::ofstream &of) {
	of << "<SIGNO value=\"" << this->symbol << "\">\n";
	if(this->l != nullptr)
		this->l->print(of);
	if(this->r != nullptr)
		this->r->print(of);
	of << "</SIGNO>\n";
}

If::If (int i, std::string s, Expression* ex, Suite* su, Else* els): Node(i,s) {
	this->expr = ex;
	this->Els = els;
	this->suite = su;
}

void If::print(std::ofstream &of) {
	of << "<SI>\n";
	if(this->expr != nullptr)
		this->expr->print(of);
	of << "<BLOQUE>\n";
	if(this->suite != nullptr)
		this->suite->print(of);
	/*for(auto a: this->Elif)
		a->print(of);*/
	of << "</BLOQUE>\n";
	if(this->Els != nullptr)
		this->Els->print(of);
	of << "</SI>\n";
}

Else::Else(int i, std::string s, Suite* su): Node(i,s) {
	this->suite = su;
}

void Else::print(std::ofstream &of) {
	of << "<OTRO>\n";
	if(this->suite != nullptr)
		this->suite->print(of);
	of << "</OTRO>\n";
}

While::While(int i, std::string s, Expression* ex, Suite* su): Node(i,s) {
	this->expr = ex;
	this->suite = su;
}

void While::print(std::ofstream &of) {
	of << "<MIENTRAS>\n";
	if(this->expr != nullptr)
		this->expr->print(of);
	of << "<BLOQUE>\n";
	if(this->suite != nullptr)
		this->suite->print(of);
	of << "</BLOQUE>\n";
	of << "</MIENTRAS>\n";
}

void Program::print(std::ofstream &of) {
	of << "<PROGRAMA>\n";
	for(auto a: this->nodes){
		a->print(of);
	}
	of << "</PROGRAMA>\n";
}

void Suite::print(std::ofstream &of) {
	//of << "<BLOQUE>\n";
	for(auto a: this->nodes)
		a->print(of);
	//of << "</BLOQUE>\n";
}

void Print::print(std::ofstream &of) {
	of << "<IMPRIME>\n";
	if(this->expr != nullptr) {
		of << "<EXPRESION>\n";
		expr->print(of);
		of << "</EXPRESION>\n";
	}
	of << "</IMPRIME>\n";
}
