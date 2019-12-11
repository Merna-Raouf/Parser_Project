#pragma once
#include <vector>
#include "Node.h"
#include "Token.h"
#include <fstream>

using namespace std;
class Parser
{
	vector <Token> token_list;

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
	vector<Token>read_file(string file_name);

};

