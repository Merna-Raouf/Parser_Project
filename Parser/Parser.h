#pragma once
#include <vector>
#include "Node.h"

using namespace std;
class Parser
{
	vector<string> token_val;
	vector<string> token_type;
	int index;
public:
	Parser(void);
	~Parser(void);

	Node* statement ();
	Node* read();
	Node* write();
	Node* assign();
	Node* exp();
	Node* match(string Tocheck);


};

