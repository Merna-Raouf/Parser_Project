#pragma once
#include "string"
#include <list>

using namespace std;

class Node
{
public:

	string val;
	list <Node *> children;

public:
	Node(string val);
	~Node(void);
	void append_child(Node* child);
};

