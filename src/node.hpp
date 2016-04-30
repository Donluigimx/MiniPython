#ifndef NODE
#define NODE

#include <iostream>
#include <vector>
#include <fstream>
#include "token.hpp"

class Node {
private:

public:
	std::string symbol;
	int type;
	Node (int i, std::string s) : symbol(s), type(i) { };
	Node() { };
	virtual ~Node () { };
	virtual void print(std::ofstream &of);
};

class Suite: public Node {
private:

public:
	std::vector<Node*> nodes;
	Suite() { };
	virtual ~Suite() { };
	void print(std::ofstream &of);
};

class Expression: public Node {
private:

public:
	Expression *r, *l;
	Expression(int i, std::string s);
	virtual ~Expression () { };
	void print(std::ofstream &of);
};

class Assign: public Expression {
private:

public:
	Assign (Expression* rv, int i, std::string s);
	virtual ~Assign () { };
	void print(std::ofstream &of);
};

class ID: public Expression {
private:

public:
	ID (int i, std::string s): Expression(i, s) { };
	virtual ~ID () { };
	void print(std::ofstream &of);
};

class Value: public Expression {
private:

public:
	Value (int i, std::string s): Expression(i, s) { };
	virtual ~Value () { };
	void print(std::ofstream &of);
};

class Add: public Expression {
private:

public:
	Add (Expression* rv, int i, std::string s);
	virtual ~Add () { };
	void print(std::ofstream &of);
};

class Mul: public Expression {
private:

public:
	Mul (Expression* rv, int i, std::string s);
	virtual ~Mul () { };
	void print(std::ofstream &of);
};

class Comp: public Expression {
private:

public:
	Comp (Expression* rv, int i, std::string s);
	virtual ~Comp () { };
	void print(std::ofstream &of);
};

class Unary: public Expression {
private:

public:
	Unary (Expression* rv, int i, std::string s);
	virtual ~Unary () { };
	void print(std::ofstream &of);
};

class Else: public Node {
private:

public:
	Suite* suite;
	Else(int i, std::string s, Suite* su);
	virtual ~Else() { };
	void print(std::ofstream &of);
};

class If: public Node {
private:

public:
	Expression* expr;
	Suite* suite;
	//std::vector<If*> Elif;
	Else* Els;
	If (int i, std::string s, Expression* ex, Suite* su, Else* els);
	virtual ~If () { };
	void print(std::ofstream &of);
};

class While: public Node {
private:

public:
	Expression* expr;
	Suite* suite;
	While (int i, std::string s, Expression* ex, Suite* su);
	virtual ~While () { };
	void print(std::ofstream &of);
};

class Program: public Node{
private:

public:
	std::vector<Node*> nodes;
	Program() { };
	virtual ~Program() { };
	void print(std::ofstream &of);
};

class Print: public Node{
private:

public:
	Expression* expr;
	Print() { expr = nullptr; };
	virtual ~Print() { };
	void print(std::ofstream &of);
};

#endif
