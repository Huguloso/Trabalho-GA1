#pragma once
#include <vector>
#include "Token.h"

class Place
{
public:
	Place();
	Place(int id);
	~Place();

	int id;
	bool empty;
	vector<Token> tokensList;
	bool isWall;

	Token getToken(int pos);
	void addToken(Token token);
	void removeToken(int pos);
	bool isEmpty();
	int size();
	void printId();
};

