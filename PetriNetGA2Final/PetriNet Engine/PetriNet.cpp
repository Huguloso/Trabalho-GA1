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
	//map dos lugares com suas conexões
	map <int, vector<Connection*>> placesConn;
	//vetor das conexões habilitadas de um lugar
	vector <Connection*> connHabilitadasNPC;
	vector <Connection*> connHabilitadasPlayer;
	//percorre a lista de transições
	for (auto &transition : transitionList) {
		//percorre a lista de transições de entrada
		for (auto &connIn : transition->connInList) {
			//adiciona elas à lista de conexões dos lugares
			placesConn[connIn->place->id].push_back(connIn);
		}
		//percorre a lista de conexões de saída 
		for (auto &connOut : transition->connOutList) {
			//verifica se estão habilitadas
			connOut->isEnabled();
		}
	}

	//percorre o map
	for (auto &placeConn : placesConn) {
		//se o lugar possui uma ou mais conexões
		if (placeConn.second.size() > 0) {
			//percorre o vetor de conexões de cada lugar
			for (auto &conn : placeConn.second) {
				//se existe uma conexão habilitada e o token qu está no lugar for um NPC
				if (conn->isEnabled() == true && conn->place->getToken(0).id == 'N') {
					//... manda ela pro vetor de coneXões habilitadas do lugar
					connHabilitadasNPC.push_back(conn);
				}
				//se existe uma conexão habilitada e o token qu está no lugar for um Player
				else if(conn->isEnabled() == true && conn->place->getToken(0).id == 'P'){
					//... manda ela pro vetor de coneXões habilitadas do lugar
					connHabilitadasPlayer.push_back(conn);
				}
			}
		}
	}
	//se o tamanho do vetor de conexôes habilitadas for maior que 0
	if (connHabilitadasNPC.size() > 0) {
		//cria um número aleatório e um contador
		int connN = rand() % connHabilitadasNPC.size();
		int cont = 0;
		//percorre o vetor de conexões habilitadas
		for (auto &connHabilitada : connHabilitadasNPC) {
			//se o contador for diferente do número sorteado a conexão é desabilitada(assim só há uma conexão para ser feita)
			if (connN != cont) {
				connHabilitada->setEnabled(false);
			}
			cont++;
		}
	}
	//se o tamanho do vetor de conexôes habilitadas for maior que 0
	if (connHabilitadasPlayer.size() > 0) {
		int cont = 0;
		int selecaoPlayer;
		cout << "Para onde ir" << endl;
		cin >> selecaoPlayer;
		//percorre o vetor de conexões habilitadas
		for (auto &connHabilitada : connHabilitadasPlayer) {
			//se o contador for diferente do número sorteado a conexão é desabilitada(assim só há uma conexão para ser feita)
			if (selecaoPlayer != cont) {
				connHabilitada->setEnabled(false);
			}
			cont++;
		}
	}
	//esvazia o vetor
	connHabilitadasNPC.empty();
	connHabilitadasPlayer.empty();

		
	//percorre a lista de transições
	for (auto &transition : transitionList) {
		//se permitir a transição
		if (transition->isEnabled()) {
			//percorre as conexões de entrada
			for (auto &connIn : transition->connInList) {
				//se o lugar da conexão NÃO estiver vazio
				if (!connIn->place->isEmpty()) {
					//remove o número de tokens de acordo com o peso da conexão
					for (int i = 0; i < connIn->weight; i++) {
						newToken.id = connIn->place->getToken(0).id;
						connIn->place->removeToken(0);
					}
				}

			}
			//percorre as conexões de saída
			for (auto &connOut : transition->connOutList) {
				//adiciona tokens confomre o peso da conexão
				for (int i = 0; i < connOut->weight; i++) {
					connOut->place->addToken(newToken);
				}
			}
		}
		//todas conexões voltam a estarem HABILITADAS
		transition->enabled = true;
	}
	
}

//método que conecta dois lugares criando uma transição de ida e outra de volta
void PetriNet::conectarLugares(Place * place1, Place * place2, int idTransition)
{
	//cira transição do place 1 para o 2
	Transition* transition = new Transition(idTransition);
	insertTransition(transition);
	transition->insertConnection(new Connection(place1, true, false, 1));
	transition->insertConnection(new Connection(place2, false, false, 1));
	//cria transição do place 2 para o 1
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