#include "pch.h"
#include "Transition.h"


Transition::Transition()
{
	hasChanged = false;
	enabled = true;
}
Transition::Transition(int id)
{
	this->id = id;
	hasChanged = false;
	enabled = true;
}
Transition::~Transition()
{
}
bool Transition::isEnabled()
{

	for (auto &connIn : connInList) {
		if (connIn->getEnabled() == false) {
			enabled = false;
		}
	}
	for (auto &connOut : connOutList) {
		if (connOut->getEnabled() == false) {
			enabled = false;
		}
	}
	return enabled;
}
void Transition::insertConnection(Connection* conn)
{
	if (conn->isEntryArc()) {
		connInList.push_back(conn);
	}
	else {
		connOutList.push_back(conn);
	}
}




