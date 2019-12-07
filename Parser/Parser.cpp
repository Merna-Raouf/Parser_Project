#include "Parser.h"


Parser::Parser(void)
{
	index = 0;
}

Parser::~Parser(void)
{
}
Node* Parser:: match(string Tocheck){
	if(token_type[index] == Tocheck)
		return ( new Node(token_val[index++]) ) ;
	else 
		return NULL;
}

Node* Parser :: statement (){

}
Node* Parser :: read(){

}
Node* Parser :: write(){

}
Node* Parser :: assign(){

}
Node* Parser :: exp(){

}
Node* Parser ::* match(string Tocheck){

}
