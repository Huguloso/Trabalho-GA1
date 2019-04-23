#pragma once
#include <vector>
#include "Connection.h"

class Transition
{
public:

	int id;
	bool enabled;
	bool hasChanged;
	vector<Connection*> connInList;
	vector<Connection*> connOutList;

	Transition(); 
	Transition(int id);
	~Transition();
	
	void insertConnection(Connection* conn);
	bool isEnabled();
};

