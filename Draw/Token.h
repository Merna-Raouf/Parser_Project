#pragma once

#include <string>

using namespace std;

class Token
{
public:
	string value;
	string type;
	Token(void);
	Token(string value , string type);
	~Token(void);
};

