#include "pch.h"
#include "Token.h"



Token::Token()
{
}


Token::~Token()
{
}

Token::Token(char id) {
	this->id = id;
}
void Token::printId() {
	cout << "Id do token:" << id << endl;
}
