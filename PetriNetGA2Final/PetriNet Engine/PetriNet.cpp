#include "pch.h"
#include "PetriNet.h"


PetriNet::PetriNet()
{
}

PetriNet::~PetriNet()
{
}

void PetriNet::execCycle()
{
	//novo token
	Token newToken;
	//map dos lugares com suas conex�es
	map <int, vector<Connection*>> placesConn;
	//vetor das conex�es habilitadas de um lugar
	vector <Connection*> connHabilitadasNPC;
	vector <Connection*> connHabilitadasPlayer;
	//percorre a lista de transi��es
	for (auto &transition : transitionList) {
		//percorre a lista de transi��es de entrada
		for (auto &connIn : transition->connInList) {
			//adiciona elas � lista de conex�es dos lugares
			placesConn[connIn->place->id].push_back(connIn);
		}
		//percorre a lista de conex�es de sa�da 
		for (auto &connOut : transition->connOutList) {
			//verifica se est�o habilitadas
			connOut->isEnabled();
		}
	}

	//percorre o map
	for (auto &placeConn : placesConn) {
		//se o lugar possui uma ou mais conex�es
		if (placeConn.second.size() > 0) {
			//percorre o vetor de conex�es de cada lugar
			for (auto &conn : placeConn.second) {
				//se existe uma conex�o habilitada e o token qu est� no lugar for um NPC
				if (conn->isEnabled() == true && conn->place->getToken(0).id == 'N') {
					//... manda ela pro vetor de coneX�es habilitadas do lugar
					connHabilitadasNPC.push_back(conn);
				}
				//se existe uma conex�o habilitada e o token qu est� no lugar for um Player
				else if(conn->isEnabled() == true && conn->place->getToken(0).id == 'P'){
					//... manda ela pro vetor de coneX�es habilitadas do lugar
					connHabilitadasPlayer.push_back(conn);
				}
			}
		}
	}
	//se o tamanho do vetor de conex�es habilitadas for maior que 0
	if (connHabilitadasNPC.size() > 0) {
		//cria um n�mero aleat�rio e um contador
		int connN = rand() % connHabilitadasNPC.size();
		int cont = 0;
		//percorre o vetor de conex�es habilitadas
		for (auto &connHabilitada : connHabilitadasNPC) {
			//se o contador for diferente do n�mero sorteado a conex�o � desabilitada(assim s� h� uma conex�o para ser feita)
			if (connN != cont) {
				connHabilitada->setEnabled(false);
			}
			cont++;
		}
	}
	//se o tamanho do vetor de conex�es habilitadas for maior que 0
	if (connHabilitadasPlayer.size() > 0) {
		int cont = 0;
		int selecaoPlayer;
		cout << "Para onde ir" << endl;
		cin >> selecaoPlayer;
		//percorre o vetor de conex�es habilitadas
		for (auto &connHabilitada : connHabilitadasPlayer) {
			//se o contador for diferente do n�mero sorteado a conex�o � desabilitada(assim s� h� uma conex�o para ser feita)
			if (selecaoPlayer != cont) {
				connHabilitada->setEnabled(false);
			}
			cont++;
		}
	}
	//esvazia o vetor
	connHabilitadasNPC.empty();
	connHabilitadasPlayer.empty();

		
	//percorre a lista de transi��es
	for (auto &transition : transitionList) {
		//se permitir a transi��o
		if (transition->isEnabled()) {
			//percorre as conex�es de entrada
			for (auto &connIn : transition->connInList) {
				//se o lugar da conex�o N�O estiver vazio
				if (!connIn->place->isEmpty()) {
					//remove o n�mero de tokens de acordo com o peso da conex�o
					for (int i = 0; i < connIn->weight; i++) {
						newToken.id = connIn->place->getToken(0).id;
						connIn->place->removeToken(0);
					}
				}

			}
			//percorre as conex�es de sa�da
			for (auto &connOut : transition->connOutList) {
				//adiciona tokens confomre o peso da conex�o
				for (int i = 0; i < connOut->weight; i++) {
					connOut->place->addToken(newToken);
				}
			}
		}
		//todas conex�es voltam a estarem HABILITADAS
		transition->enabled = true;
	}
	
}

//m�todo que conecta dois lugares criando uma transi��o de ida e outra de volta
void PetriNet::conectarLugares(Place * place1, Place * place2, int idTransition)
{
	//cira transi��o do place 1 para o 2
	Transition* transition = new Transition(idTransition);
	insertTransition(transition);
	transition->insertConnection(new Connection(place1, true, false, 1));
	transition->insertConnection(new Connection(place2, false, false, 1));
	//cria transi��o do place 2 para o 1
	transition = new Transition(-idTransition);
	insertTransition(transition);
	transition->insertConnection(new Connection(place2, true, false, 1));
	transition->insertConnection(new Connection(place1, false, false, 1));
}

void PetriNet::insertTransition(Transition* transition)
{
	transitionList.push_back(transition);
}
void PetriNet::insertPlace(Place* place)
{
	placeList.push_back(place);
}
Transition* PetriNet::getTransition(int pos)
{
	return transitionList[pos];
}
Place* PetriNet::getPlace(int pos)
{
	return placeList[pos];
}