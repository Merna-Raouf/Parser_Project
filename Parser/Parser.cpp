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
Node* Parser :: write()
{
	Node* WRITE=match("WRITE");
	if(WRITE!=NULL)
	{
		Node* EXP=exp();
		if(EXP!=NULL)
			WRITE->append_child(EXP);
	}

}
Node* Parser :: assign(){

}

Node* Parser :: repeat()
{
	Node* REPEAT=match("REPEAT");
	
	if(REPEAT!=NULL)
	{
		Node* STAT=statement_seq();
		if(STAT!=NULL)
		{
			Node* UNTIL=match("UNTIL");
			if(UNTIL!=NULL)
			{
				Node* EXP=exp();
				if(EXP!=NULL)
				{
					REPEAT->append_child(STAT);
					REPEAT->append_child(EXP);
				}
				else
					return NULL;
			}
			else
				return NULL;
		}
		else
			return NULL;
	}

}

Node* Parser :: exp()
{
	
	 Node* SIMPLE=SimpleExp();
	 if(SIMPLE==NULL)
		 return NULL;


	 Node* LESS=match("LESSTHAN") ;
	 Node* EQ=match("EQUAL");

	 if(LESS !=NULL )
	 {
		 Node* SIMPLE2=SimpleExp();

		  if(SIMPLE2==NULL)
				return NULL;
			
		 LESS->append_child(SIMPLE);
		 LESS->append_child(SIMPLE2);

	 }

	 
	 else if(EQ !=NULL )
	 {
		 Node* SIMPLE2=SimpleExp();

		  if(SIMPLE2==NULL)
				return NULL;
			
		 EQ->append_child(SIMPLE);
		 EQ->append_child(SIMPLE2);

	 }
	 
}
Node* Parser :: SimpleExp()
{
	Node* TERM=term();
		if(TERM==NULL)
			return NULL;
		
	Node* PLUS=match("PLUS") ;
	Node* MINUS=match("MINUS");
	while(PLUS!=NULL || MINUS!=NULL)
	{
	
		 if(PLUS !=NULL )
		 {
			 Node* TERM2=term();

			  if(TERM2==NULL)
					return NULL;
			
			 PLUS->append_child(TERM);
			 PLUS->append_child(TERM);
			 Node* TERM=MINUS;

		 }

	 
		 else if(MINUS !=NULL )
		 {
			 Node* TERM2=term();

			  if(TERM2==NULL)
					return NULL;
			
			 MINUS->append_child(TERM);
			 MINUS->append_child(TERM);
			 Node* TERM=MINUS;
		 }

		 Node* PLUS=match("PLUS") ;
		 Node* MINUS=match("MINUS");
	}
	
}
Node* Parser :: term()
{
	Node* FACT=factor();
	if(FACT==NULL)
			return NULL;
		
	Node* MUL=match("MULT") ;
	Node* DIV=match("DIV");
	
	while(MUL!=NULL || DIV!=NULL)
	{
	
		 if(MUL!=NULL )
		 {
			 Node* FACT2=factor();

			  if(FACT2==NULL)
					return NULL;
			
			 MUL->append_child(FACT);
			 MUL->append_child(FACT2);
			 Node* FACT=MUL; 	
		 }

	 
		 else if(DIV !=NULL )
		 {
			Node* FACT2=factor();

			  if(FACT2==NULL)
					return NULL;
			 DIV->append_child(FACT);
			 DIV->append_child(FACT2);
			 Node* FACT=DIV; 
		 }
		
		
		Node* MUL=match("MULT") ;
		Node* DIV=match("DIV");
	}
	
}
Node* Parser :: factor()
{
	Node* OPEN=match("OPENBRACKET");
	Node* EXP;
	Node* CLOSE;
	
	if(OPEN!=NULL)
	{
		EXP=exp();
		if(EXP!=NULL)
		{
			 CLOSE=match("CLOSEDBRACKET"); 
				if(CLOSE==NULL)
					return NULL;
		}
		else
			return NULL;

		
	}
	Node* NUM=match("NUMBER");
	Node* ID=match("IDENTIFIER ");
	
	if(NUM!=NULL)
		return NUM;

	else if(ID!=NULL)
		return ID;

	else
		return NULL;
		
}

