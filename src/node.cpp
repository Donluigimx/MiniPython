#include <iostream>
#include <vector>
#include <map>
#include "node.hpp"

std::map<std::string, int> symbolTable;

void Node::print(std::ofstream &of) {
	of << "FATAL ERROR NODE" << std::endl;
	of.close();
	exit(1);
}

Expression::Expression(int i, std::string s): Node(i, s) {
	this->r = nullptr;
	this->l = nullptr;
	this->dataType = '\0';
}

void Expression::print(std::ofstream &of) {
	of << "FATAL ERROR EXPRESSION" << std::endl;
	of.close();
	exit(1);
}

int Expression::semanticAnalysis() {
	return 0;
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

int Assign::semanticAnalysis() {
	int val = this->r->semanticAnalysis();
	auto it = symbolTable.find(this->l->symbol);
	if (this->r->dataType != 'e') {
		if (it != symbolTable.end())
			symbolTable.erase(it);
		if (this->r->dataType == 'i')
			symbolTable.insert(std::pair<std::string, int>(this->l->symbol,Token::INTEGER));
		else if (this->r->dataType == 'f')
			symbolTable.insert(std::pair<std::string, int>(this->l->symbol,Token::FLOAT));
	}
	return val;
}

void ID::print(std::ofstream &of) {
	of << "<ID>" << this->symbol << "</ID>\n";
}

int ID::semanticAnalysis() {
	int val;
	auto it = symbolTable.find(this->symbol);
	if (it != symbolTable.end()) {
		if (it->second == Token::INTEGER) {
			this->dataType = 'i';
			val = 1;
		} else if (it->second == Token::FLOAT) {
			this->dataType = 'f';
			val = 1;
		} else {
			this->dataType = 'e';
			val = 0;
		}
	} else {
		this->dataType = 'e';
		val = 0;
	}
	
	return val;
}

void Value::print(std::ofstream &of) {
	if(this->type == Token::INTEGER)
		of << "<ENTERO>" << this->symbol << "</ENTERO>\n";
	else if (this->type == Token::FLOAT)
		of << "<REAL>" << this->symbol << "</REAL>\n";
}

int Value::semanticAnalysis() {
	if(this->type == Token::INTEGER)
		this->dataType = 'i';
	else if (this->type == Token::FLOAT)
		this->dataType = 'f';

	return 1;
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

int Add::semanticAnalysis() {
	int vall = this->l->semanticAnalysis();
	int valr = this->r->semanticAnalysis();
	int val;
	if( vall == 0 || valr == 0)
		val = 0;
	else
		val = vall;

	if( this->l->dataType == this->r->dataType)
		this->dataType = this->r->dataType;
	else
		this->dataType = 'e';

	return val;
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

int Mul::semanticAnalysis() {
	int vall = this->l->semanticAnalysis();
	int valr = this->r->semanticAnalysis();
	int val;
	if( vall == 0 || valr == 0)
		val = 0;
	else
		val = vall;

	if( this->l->dataType == this->r->dataType)
		this->dataType = this->r->dataType;
	else
		this->dataType = 'e';

	return val;
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

int Comp::semanticAnalysis() {
	int vall = this->l->semanticAnalysis();
	int valr = this->r->semanticAnalysis();
	int val;
	if( vall == 0 || valr == 0)
		val = 0;
	else
		val = vall;

	if( this->l->dataType == this->r->dataType)
		this->dataType = this->r->dataType;
	else
		this->dataType = 'e';

	return val;
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

int Unary::semanticAnalysis() {
	int val = this->r->semanticAnalysis();
	this->dataType = this->r->dataType;

	return val;
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

int If::semanticAnalysis() {
	int vale = this->expr->semanticAnalysis();
	int vals = this->suite->semanticAnalysis();
	int valel = 1;
	int val;

	if (this->Els != nullptr)
		valel = this->Els->semanticAnalysis();

	if (vale == 0 || vals == 0 || valel == 0)
		val = 0;
	else
		val = 1;

	return val;
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

int Else::semanticAnalysis() {
	int val = this->suite->semanticAnalysis();
	return val;
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

int While::semanticAnalysis() {
	int vale = this->expr->semanticAnalysis();
	int vals = this->suite->semanticAnalysis();
	int val;

	if (vale == 0 || vals == 0)
		val = 0;
	else
		val = 1;

	return val;
}

void Program::print(std::ofstream &of) {
	of << "<PROGRAMA>\n";
	for(auto a: this->nodes){
		a->print(of);
	}
	of << "</PROGRAMA>\n";
}

int Program::semanticAnalysis() {
	int val;
	for (auto a: this->nodes) {
		val = a->semanticAnalysis();
		if (val == 0)
			break;
	}
	return val;
}

void Suite::print(std::ofstream &of) {
	//of << "<BLOQUE>\n";
	for(auto a: this->nodes)
		a->print(of);
	//of << "</BLOQUE>\n";
}

int Suite::semanticAnalysis() {
	int val;
	for (auto a: this->nodes) {
		val = a->semanticAnalysis();
		if (val == 0)
			break;
	}
	return val;
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

int Print::semanticAnalysis() {
	int val = 1;

	if(this->expr != nullptr)
		val = this->expr->semanticAnalysis();

	return val;
}
