#include "Node.h"


Node::Node(string val)
{
    this->value = val;
    this->type = "";
}

Node::Node(string value,string type)
{
    this->value = value;
    this->type = type;
    this->drawn=false;
}

Node::~Node(void)
{
    delete this;
}

void Node :: append_child(Node *child){
    this->children.push_back(child);
}
