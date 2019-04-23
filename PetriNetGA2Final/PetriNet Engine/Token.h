#pragma once
#include <iostream>
#include<string>

using namespace std;

class Token {
public:
	char id;

	Token();
	~Token();
	Token(char id);
	void printId();
};
