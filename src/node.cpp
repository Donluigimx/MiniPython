#include <iostream>
#include <vector>
#include <map>
#include "node.hpp"

std::map<std::string, int> symbolTable;

int Node::eend = 0;
int Node::ttrue = 0;
int Node::wwhile = 0;
int Node::bbgin = 0;
int Node::iif = 0;
int Node::eelse = 0;

void Node::print(std::ofstream &of) {
	of << "FATAL ERROR NODE" << std::endl;
	of.close();
	exit(1);
}

void Node::code(std::ofstream &of) {
	of << "ERRRRRRRRRROOOOOOOOOOOR" << std::endl;
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

void Expression::code(std::ofstream &of) {
	of << "ERRRRRRRRRROOOOOOOOOOOR" << std::endl;
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

void Assign::code(std::ofstream &of) {
	//if (this->l != nullptr)
		//this->l->code(of);
	if (this->r != nullptr)
		this->r->code(of);
	of << "pop eax\nmov " << this->l->symbol << ", eax\n";
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

void ID::code(std::ofstream &of) {
	of << "push " << this->symbol << "\n";
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

void Value::code(std::ofstream &of) {
	of << "push " << this->symbol << "\n";
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

void Add::code(std::ofstream &of) {
	if (this->l != nullptr)
		this->l->code(of);
	if (this->r != nullptr)
		this->r->code(of);

	of << "pop ebx\npop eax\n";
	if (this->symbol == "+")
		of << "add eax, ebx\n";
	if (this->symbol == "-")
		of << "sub eax, ebx\n";
	of << "push eax\n";
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

void Mul::code(std::ofstream &of) {
	if (this->l != nullptr)
		this->l->code(of);
	if (this->r != nullptr)
		this->r->code(of);

	of << "pop ebx\npop eax\nxor edx, edx\n";
	if (this->symbol == "*")
		of << "mul ebx\n";
	if (this->symbol == "/")
		of << "div ebx\n";
	of << "push eax\n";
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

void Comp::code(std::ofstream &of) {
	std::string sym;
	int aend = Comp::eend++;
	int atrue = Comp::ttrue++;
	if (this->l != nullptr)
		this->l->code(of);
	if (this->r != nullptr)
		this->r->code(of);

	if (this->symbol == "<")
		sym = "jl";
	else if (this->symbol == "<=")
		sym = "jle";
	else if (this->symbol == ">")
		sym = "jg";
	else if (this->symbol == ">=")
		sym = "jge";
	else if (this->symbol == "==")
		sym = "je";
	else if (this->symbol == "!=")
		sym = "jne";

	//of << "BEGIN" << Node::bbgin << ":\n";
	of << "pop ebx\npop eax\ncmp eax, ebx\n";
	of << sym << " TRUE_" << atrue << "\n";
	of << "push 0\njmp END_" << aend << "\n";
	of << "TRUE_" << atrue << ":\n";
	of << "push 1\n";
	of << "END_" << aend << ":\n";
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

void Unary::code(std::ofstream &of) {
	if (this->symbol == "-")
		of << "pop eax\nneg eax\npush eax\n";
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

void If::code(std::ofstream &of) {
	int aif = If::iif++;

	this->expr->code(of);
	of << "pop eax\ncmp eax, 0\nje IF_" << aif << "\n";
	this->suite->code(of);
	of << "IF_" << aif << ":\n";
	if (this->Els != nullptr)
		this->Els->code(of);
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

void Else::code(std::ofstream &of) {
	this->suite->code(of);
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

void While::code(std::ofstream &of) {
	int awhile = While::wwhile++;
	int abgin = While::bbgin++;

	of << "jmp WHILE_" << awhile << "\n";
	of << "BEGIN_" << abgin << ":\n";
	this->suite->code(of);
	of << "WHILE_" << awhile << ":\n";
	this->expr->code(of);
	of << "pop eax\ncmp eax, 1\nje BEGIN_" << abgin << "\n";
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

void Program::code(std::ofstream &of) {
	of << ".386\n.model flat, stdcall\noption casemap:none;labels are case-sensitive now";
	of << "\n\ninclude \\masm32\\macros\\macros.asm\ninclude \\masm32\\include\\masm32.inc\n";
	of << "include \\masm32\\include\\kernel32.inc\n\n";
	of << "includelib \\masm32\\lib\\masm32.lib\n";
	of << "includelib \\masm32\\lib\\kernel32.lib\n\n";
	of << ".data\n.data?\n";

	for (auto a: symbolTable) {
		of << a.first << " dword ?\n";
	}
	of << "\n.code\nmain:\n\n";
	for (auto a: this->nodes) {
		a->code(of);
	}
	of << "exit\n\nend main\n";
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

void Suite::code(std::ofstream &of) {
	for (auto a: this->nodes) {
		a->code(of);
	}
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

void Print::code(std::ofstream &of) {
	if (this->expr != nullptr)
		this->expr->code(of);
	of << "pop eax\n";
	of << "print str$(eax)\nprint chr$(10)\n";
}
