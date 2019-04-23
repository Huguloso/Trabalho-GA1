#pragma once
#include <iostream>
#include <ctime>
#include "PetriNet.h"
#include "pch.h"
class CaveGeneration
{
public:
	CaveGeneration(int height, int width);
	~CaveGeneration();
	void print();
	void gerar();

	int width;
	int height;
	int randomPercent = 35;
	int map[20][30];
	PetriNet eng;

	void inicialize();
	void smoothMap();
	int getSurroundingWallCount(int x, int y);
	void transformarEmPetri();
	void printPetri();

	void posicionarNPC();
	void posicionarPlayer();
};
