#include <iostream>
#include <vector>
#include <string>
#include "Token.h"
#include "Parser.h"

using namespace std;

string removeSpaces(string str); 
vector<Token> read_file(string file_name);

int main(){
	
	Parser p1;
	p1.read_file("Example.txt");
	Node* Output = p1.statement_seq();

	return 0;
}

