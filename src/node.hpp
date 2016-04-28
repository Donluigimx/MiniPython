#ifndef NODE
#define NODE

#include <iostream>
#include <vector>
class Node {
private:

public:
	std::string symbol;
	std::string type;
	Node (int i, std::string s) : symbol(s), type(i) { };
	virtual ~Node () { };
	virtual void print();
};

class Expression: public Node {
private:

public:
	Expression *r, *l;
	Expression(int i, std::string s);
	virtual ~Expression ();
	void print();
};

class Assign: public Expression {
private:

public:
	Assign (Expression* rv, Expression* lv, int i, std::string s);
	virtual ~Assign ();
	void print();
};

class ID: public Expression {
private:

public:
	ID (int i, std::string s): Expression(i, s) { };
	virtual ~ID ();
	void print();
};

class Value: public Expression {
private:

public:
	Value (int i, std::string s): Expression(i, s) { };
	virtual ~Value ();
	void print();
};

class Add: public Expression {
private:

public:
	Add (Expression* rv, int i, std::string s);
	virtual ~Add ();
	void print();
};

class Mul: public Expression {L
private:

public:
	Mul (Expression* rv, int i, std::string s);
	virtual ~Mul ();
	void print();
};

class Comp: public Expression {
private:

public:
	Comp (Expression* rv, int i, std::string s);
	virtual ~Comp ();
	void print();
};

class Unary: public Expression {
private:

public:
	Unary (Expression* rv, int i, std::string s);
	virtual ~Unary ();
	void print();
};

class If: public Node {
private:

public:
	Expression* expr;
	Suite* suite;
	std::std::vector<If*> Elif;
	Else* Els;
	If (int i, std::string s);
	virtual ~If ();
	void print();
};

class Else: public Node {
private:

public:
	Suite* suite;
	Else(int i, std::string s);
	virtual ~Else();
	void print();
};

class Suite: public Node {
private:

public:
	std::vector<Node*> Nodes;
	Suite();
	virtual ~Suite();
	void print();
};

class While: public Node {
private:

public:
	Expression* expr;
	Suite* suite;
	While (int i, std::string s);
	virtual ~While ();
	void print();
};

class Program: public Node{
private:

public:
	std::vector<Node*> Program;
	Program();
	virtual ~Program();
	void print();
};

#endif
