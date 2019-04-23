#include "pch.h"
#include "Connection.h"


Connection::Connection()
{
	//isEnabled();
}

Connection::Connection(Place* place, bool isEntryArc, bool isInhibitorArc, int weight)
{
	this->inhibitorArc = isInhibitorArc;
	this->entryArc = isEntryArc;
	this->place = place;
	this->weight = weight;
	//isEnabled();
}

Connection::~Connection()
{
}
bool Connection::isInhibitorArc()
{
	return inhibitorArc;
}
bool Connection::isEntryArc()
{
	return entryArc;
}

bool Connection::isEnabled()
{
	//se for um arco de entrada
	if (entryArc) {
		if (!isInhibitorArc()) {
			// ... e o n�mero de tokens no lugar for menor que o peso da conex�o
			if (place->size() < weight) {
				//DESABILITA a conec��o
				enabled = false;
			}
			else {
				enabled = true;
			}
		}
		//Se a conex�o FOR um arco inibidor ... 
		else {
			// ... e o lugar n�o estiver vazio
			if (place->isEmpty() == false) {
				//DESABILITA a conec��o
				enabled = false;
			}
			else {
				enabled = true;
			}
		}
	}
	//se for um arco de sa�da
	else if (!isEntryArc()){
		//e o lugar for uma parede
		if (place->isWall) {
			//DESABILITA a conec��o
			enabled = false;
		}
		else {
			enabled = true;
		}
	}
	return enabled;
}

bool Connection::getEnabled()
{
	return enabled;
}

void Connection::setEnabled(bool enabled)
{
	this->enabled = enabled;
}
