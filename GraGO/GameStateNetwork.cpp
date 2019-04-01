#include "GameStateNetwork.h"



void GameStateNetwork::endGame()
{
	getStateManager()->pushState(make_unique<GameOverState>(getStateManager(), utilities, game.getWinner(),false));
}

GameStateNetwork::GameStateNetwork(StateManager* state, const Utilities& utilities, NetworkThread* nt, std::thread* runningThread,FieldColor color) :
	GameState(state, utilities), networkConnection(*nt), currentState(Running), network(runningThread),myColor(color)
{
	networkConnection.setCallback(std::bind(&GameStateNetwork::disconnected, this));
	networkConnection.setReceivedCallback(std::bind(&GameStateNetwork::dataReceived, this));
	gameView.exit->setCallback(std::bind(&GameStateNetwork::disconnect, this));
	gameView.exit->setText("Rozlacz");
	
	
	refreshMutex.lock();

	if (myColor == FieldColor::WHITE) //czarny zaczyna
	{
		sf::Event e;
		gameView.update(e, utilities.renderWindow); //zapobiega bi³ym kwadratom zamiast pol
		gameView.lockAllButtons();
	}
	for (int i = 0; i < gameView.game->getBoardSize(); i++) {
		for (int j = 0; j < gameView.game->getBoardSize(); j++) {
			auto x = [this, i, j]() {putStone(i, j); }; //wyrazenie lambda
			gameView.interactiveElements[i][j]->setCallback(x);
		}
		
	}
	
	refreshMutex.unlock();
}



GameStateNetwork::~GameStateNetwork()
{
	if (currentState >= ConnectionState::Connected) {
		networkConnection.stop();
		network->join();
		delete network;
	}
}

void GameStateNetwork::update(sf::Event& e, sf::RenderWindow& window)
{

	
	switch (currentState) {
	case ConnectionState::Disconnected:
		
		network->join();
		getStateManager()->pushState(make_unique<AlertState>(getStateManager(), utilities, "Rozlaczono"));
		break;
	
	case ConnectionState::Running:

		if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::P && game.getWhoMoves()==(Moves)myColor) {

			game.pass();
			gameView.refreshLabelsInfo();
			gameView.pass(game.getWhoMoves());

			e.key.code = sf::Keyboard::A;
			sf::Packet p;
			p << "3";
			networkConnection.sendData(p);
			gameView.lockAllButtons();

		}

		

		break;
	}

	gameView.update(e, window);

}

void GameStateNetwork::draw() const
{
	
	GameState::draw();
	
}

void GameStateNetwork::processData(std::string s)
{
	char action = s[0];
	unsigned int x, y;
	switch (atoi(&action)) {
		case GameActions::GiveColor:
			
			
			if (s.substr(1, s.length() - 1) == "black") {
				myColor = FieldColor::BLACK;
				
			}
				
			else {
				myColor = FieldColor::WHITE;
				
			}
		break;
		case GameActions::Move:
			
			x = atoi(s.substr(1, s.find(':', 1) - 1).c_str());
			y = atoi(s.substr(s.find(':', 1) + 1).c_str());
			
			
			gameView.unlockAllButtons();
			gameView.putStone(x, y);
			
		break;
		case GameActions::Pass:
			game.pass();
			gameView.refreshLabelsInfo();
			gameView.pass(game.getWhoMoves());
			gameView.unlockAllButtons();
			
		break;
		
			
	}
}



void GameStateNetwork::dataReceived()
{
	
	processData(networkConnection.getData());

}
void GameStateNetwork::disconnected() {
	
	
	currentState = Disconnected;
		
	
}

void GameStateNetwork::disconnect()
{
	
		networkConnection.mutex.lock();
		networkConnection.stop();
		networkConnection.mutex.unlock();

		network->join();

		getStateManager()->pushState(make_unique<AlertState>(getStateManager(), utilities, "Rozlaczono"));
	
}

void GameStateNetwork::putStone(unsigned int x, unsigned int y)
{
	if (gameView.putStone(x, y)) {

		sf::Packet p;
		std::string tmp;
		tmp = "2";
		char nX[3], nY[3];
		_itoa_s(x, nX, 10);
		_itoa_s(y, nY, 10);
		tmp += nX;
		tmp += ":";
		tmp += nY;
		
		p << tmp;
		networkConnection.sendData(p);
		gameView.lockAllButtons();
	}
	
}


