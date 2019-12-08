#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Token.h"

using namespace std;

vector<Token> read_file(string file_name);
int main(){
	vector <Token> token_list ;
	token_list = read_file("Example.txt");
	return 0;
}

vector<Token> read_file(string file_name){
    ifstream file;
    file.open(file_name);

	vector<Token>token_list;
	Token input;

    string line;
	int semi_index ;
    while (!file.eof()){
        getline(file,line);
		semi_index	= line.find(',');

		input.value = line.substr(0,semi_index);
		input.type	= line.substr(semi_index+1,line.length()-semi_index);

        token_list.push_back(input);
    }
    
    return token_list;     
}