#include "Node.h"


Node::Node(string val)
{
	this->val = val; 
}

Node::~Node(void)
{
	delete this;
}

void Node :: append_child(Node *child){
	this->children.push_back(child);
}
