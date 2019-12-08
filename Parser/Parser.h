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

	Node* statement_seq ();
	Node* statement ();
	Node* read();
	Node* write();
	Node* if_Con();
	Node* assign();
	Node* exp();
	Node* SimpleExp();
	Node* term();
	Node* factor();
	Node* repeat();
	Node* match(string Tocheck);


};

