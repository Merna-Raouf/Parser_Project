#ifndef TOKEN_H
#define TOKEN_H

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

#endif // TOKEN_H
