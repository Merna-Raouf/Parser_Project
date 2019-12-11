#pragma once
#include "string"
#include <list>

using namespace std;

class Node
{
public:

	string value;
	string type;
	list <Node *> children;

	Node(string value);
	Node(string value,string type);
	~Node(void);
	void append_child(Node* child);
};

