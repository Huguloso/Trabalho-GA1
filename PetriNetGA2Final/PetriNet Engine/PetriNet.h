#pragma once
#include <vector>
#include<map>
#include "Place.h"
#include "Transition.h"

class PetriNet
{
public:

	std::vector<Place*> placeList;
	std::vector<Transition*> transitionList;

	PetriNet();
	~PetriNet();
	void insertTransition(Transition* transition);
	void insertPlace(Place* place);
	Transition* getTransition(int pos);
	Place* getPlace(int pos);
	void execCycle();
	void conectarLugares(Place* place1, Place* place2, int idTansition);
};

