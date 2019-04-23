#pragma once
#include "Place.h"

class Connection
{
public:
	bool inhibitorArc;
	bool entryArc;
	bool enabled;
	Place* place;
	int weight;

	Connection();
	Connection(Place* place, bool isEntryArc, bool inhibitorArc, int weight);
	~Connection();
	bool isInhibitorArc();
	bool isEntryArc();
	bool isEnabled();
	bool getEnabled();
	void setEnabled(bool enabled);
};

