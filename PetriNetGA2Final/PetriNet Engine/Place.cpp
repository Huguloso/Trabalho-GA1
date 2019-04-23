#include "pch.h"
#include "Place.h"


Place::Place()
{
	empty = true;
	isWall = false;
}
Place::Place(int id)
{
	empty = true;
	this->id = id;
	isWall = false;
}

Place::~Place()
{
}

Token Place::getToken(int pos) {
	return tokensList[pos];
}
void Place::addToken(Token token) {
	tokensList.push_back(token); //insere Token no final da lista
	empty = false;
}
void Place::removeToken(int pos)
{
	tokensList.erase(tokensList.begin() + pos);
	empty = tokensList.empty();
}
bool Place::isEmpty() {
	return empty;
}

int Place::size()
{
	return tokensList.size();
}

void Place::printId()
{
	cout << "Id do lugar: " << id << endl;
}
