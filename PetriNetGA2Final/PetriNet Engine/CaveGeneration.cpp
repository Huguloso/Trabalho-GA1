#include "pch.h"
#include "CaveGeneration.h"


CaveGeneration::CaveGeneration(int width, int height)
{
	srand(time(0));
	this->width = width;
	this->height = height;
	this->map[height][width];
	this->gerar();
}


CaveGeneration::~CaveGeneration()
{

}

void CaveGeneration::print()
{
	std::cout << "\n";
	for (int i = 0; i < width; i++) {
		for (int y = 0; y < height; y++)
		{
			std::cout << map[i][y] << " ";
		}
		std::cout << "\n";
	}
}

/*
* Inicializa e randomiza n vezes o mapa
*/
void CaveGeneration::gerar()
{
	this->inicialize();
	//Roda 5 vezes a regra para gerar os mapas
	for (int i = 0; i < 5; i++) {
		this->smoothMap();
	}
}

/*
* Inicia colocando as bordas do mapa(paredes) e randomizando o meio
* de acordo com o percentual.
*/
void CaveGeneration::inicialize()
{
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
				this->map[x][y] = 1;
			}
			else {
				this->map[x][y] = (rand() % 101 < this->randomPercent) ? 1 : 0;
			}
		}
	}
}


/*
* Adiciona regra de acordo com a quantidade de paredes vizinhas.
* Caso haja mais de 4 parede em volta, transformamos em parede, caso contrário é caminho
*/
void CaveGeneration::smoothMap()
{
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int neighbourWallTiles = this->getSurroundingWallCount(x, y);

			if (neighbourWallTiles > 4)
				this->map[x][y] = 1;
			else if (neighbourWallTiles < 3)
				this->map[x][y] = 0;

		}
	}
}

/*
* Verifica a quantidade de vizinhos que são paredes
* @return wallCount Quantidade de paredes
*/
int CaveGeneration::getSurroundingWallCount(int gridX, int gridY)
{
	int wallCount = 0;
	for (int neighbourX = gridX - 1; neighbourX <= gridX + 1; neighbourX++) {
		for (int neighbourY = gridY - 1; neighbourY <= gridY + 1; neighbourY++) {
			if (neighbourX >= 0 && neighbourX < width && neighbourY >= 0 && neighbourY < height) {
				if (neighbourX != gridX || neighbourY != gridY) {
					wallCount += this->map[neighbourX][neighbourY];
				}
			}
			else {
				wallCount++;
			}
		}
	}

	return wallCount;
}
//método para transformar o mapa em uma rede de petri
void CaveGeneration::transformarEmPetri()
{
	for (int li = 0; li < width; li++) {
		for (int co = 0; co < height; co++) {
			eng.insertPlace(new Place(li * (width)+co));
			if (map[li][co] == 1) {
				eng.getPlace(li * (width)+co)->isWall = true;
			}
		}
	}
	for (int i = 0; i < eng.placeList.size(); i++) {
		if (i + 1 < eng.placeList.size())
			eng.conectarLugares(eng.getPlace(i), eng.getPlace(i + 1), i + 1);
		if ((i + width < eng.placeList.size()))
			eng.conectarLugares(eng.getPlace(i), eng.getPlace(i + width), 100 * (i + 1));
	}
}
//imprime a matriz de lugares
void CaveGeneration ::printPetri() {
	int aux = 0;

	for (int i = 0; i < eng.placeList.size(); i++) {
		if (eng.getPlace(i)->isWall) {
			cout << "[ ] ";
		}
		else if (eng.getPlace(i)->isWall == false) {
			if (eng.getPlace(i)->size() == 1) {
				cout << "(" << eng.getPlace(i)->getToken(0).id << ") ";
			}
			else {
				cout << "(" << eng.getPlace(i)->size() << ") ";
			}
		}
		aux++;
		if (aux >= width) {
			cout << endl;
			aux = 0;
		}
	}
}

//método para colocar um token em uma local aleatório
void CaveGeneration::posicionarNPC()
{
	//vetor de lugares que não são paredes
	vector<Place*> NotAWall;
	Token NPC('N');
	//srand(time(0));
	//for percorre a lista de lugares e adiciona os lugares navegávei ao vetor NotAWall
	for (auto &place : eng.placeList) {
		if (!place->isWall)
			NotAWall.push_back(place);
	}
	//sorteia a posição do token
	if (NotAWall.size() != 0) {
		int posPlayer = rand() % NotAWall.size();
		NotAWall[posPlayer]->addToken(NPC);
	}
	
}

void CaveGeneration::posicionarPlayer()
{
	//vetor de lugares que não são paredes
	vector<Place*> NotAWall;
	Token Player('P');
	//srand(time(0));
	//for percorre a lista de lugares e adiciona os lugares navegávei ao vetor NotAWall
	for (auto &place : eng.placeList) {
		if (!place->isWall)
			NotAWall.push_back(place);
	}
	//sorteia a posição do token
	if (NotAWall.size() != 0) {
		int posPlayer = rand() % NotAWall.size();
		NotAWall[posPlayer]->addToken(Player);
	}

}
