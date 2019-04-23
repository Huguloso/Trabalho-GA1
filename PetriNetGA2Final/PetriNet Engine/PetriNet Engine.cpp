#include "pch.h"
#include "Token.h"
#include "Place.h"
#include "PetriNet.h"
#include "CaveGeneration.h"
#include <iostream>

int main()
{
	srand(time(0));
	CaveGeneration geradorDeMalha(20, 20);
	geradorDeMalha.transformarEmPetri();
	geradorDeMalha.posicionarPlayer();
	geradorDeMalha.posicionarNPC();

	geradorDeMalha.printPetri();
	for (int i = 0; i < 8; i++) 
	{
		cout << endl;
		cout << "ciclo " << i + 1 << endl;
		geradorDeMalha.eng.execCycle();
		geradorDeMalha.printPetri();
		cout << endl;
	}
	system("pause");
}
