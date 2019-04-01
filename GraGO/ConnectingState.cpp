#include "ConnectingState.h"



ConnectingState::ConnectingState(StateManager* state, const Utilities& utilities, bool server):BaseState(state, utilities),
			 currentState(ConnectionState::Disconnected)
{
	networkConnection = new NetworkThread(server, utilities.applicationSettings.getBoardSize(), utilities.applicationSettings.getKomi());

	networkConnection->setCallback(std::bind(&ConnectingState::disconnected, this));

	//************* zmiany czysto wizualne
	
	img = new GUI::GUIImage(*utilities.textureManager.getResource(ResourceIDs::TextureID::wait));
	
	abortButton = new GUI::GUIButton(sf::Vector2f(utilities.renderWindow.getSize().x*0.4,utilities.renderWindow.getSize().y*0.8 ),
									 sf::Vector2f(utilities.renderWindow.getSize().x*0.2, utilities.renderWindow.getSize().y*0.1),	
									utilities.fontManager.getResource(ResourceIDs::FontID::mainFont)
									, "Przerwij");
	label = new GUI::GUILabel(sf::Vector2f(utilities.renderWindow.getSize().x*0.3, utilities.renderWindow.getSize().y*0.01),
		sf::Vector2f(utilities.renderWindow.getSize().x*0.4, utilities.renderWindow.getSize().y*0.2),
		utilities.fontManager.getResource(ResourceIDs::FontID::mainFont)
		, "Nawiazywanie polaczenia");
	abortButton->setCallback(std::bind(&NetworkThread::stop, networkConnection));
	
	img->setSize(utilities.renderWindow.getSize().x / 3, utilities.renderWindow.getSize().x / 3);
	img->setOrigin(img->getSize().x / 2, img->getSize().y / 2);
	img->setPosition(utilities.renderWindow.getSize().x/2, utilities.renderWindow.getSize().y/2);



	currentState = ConnectionState::Connecting;


	network = new std::thread(&ConnectingState::tryConnect, this);
	myColor = FieldColor::EMPTY;
	colorSet = false;
	gameSizeSet = false;
	komiSet = false;
}


ConnectingState::~ConnectingState()
{
	if (currentState < ConnectionState::Connected) {
		networkConnection->stop();
		network->join();
		delete network;
	}
}



void ConnectingState::update(sf::Event& e, sf::RenderWindow& window)
{
	auto runThread = [this] {
		networkConnection->loop();
	};
	auto disconnect = [this] {
		networkConnection->mutex.lock();
		networkConnection->stop();
		networkConnection->mutex.unlock();

		//network->join();

		getStateManager()->pushState(make_unique<AlertState>(getStateManager(), utilities, "Rozlaczono"));
	};
	switch (currentState) {
	case ConnectionState::Disconnected:
		
		getStateManager()->pushState(make_unique<AlertState>(getStateManager(), utilities, "Rozlaczono"));
		break;
	case ConnectionState::Connecting:
		img->setRotation(img->getRotation() + 3);
		break;

	case ConnectionState::Connected:
		if (network) {
			network->join();
			delete network;
		}
		currentState = ConnectionState::Running;
		abortButton->setCallback(disconnect);
		network = new std::thread(runThread);
		
	
	
		break;
	case ConnectionState::Running:
		if (colorSet && gameSizeSet && komiSet) {
			//przelacz
			
			getStateManager()->addTopToDelete();
			getStateManager()->pushState(make_unique<GameStateNetwork>(getStateManager(), utilities, networkConnection, network, myColor));
		}
		break;
	
	}
	//update button and circle
	label->update(e, window);
	abortButton->update(e, window);
	
}

void ConnectingState::draw() const
{

	label->draw(utilities.renderWindow, utilities.states);
	abortButton->draw(utilities.renderWindow, utilities.states);
	img->draw(utilities.renderWindow, utilities.states);
}





void ConnectingState::dataReceived()
{
	
	std::string s = networkConnection->getData();
	char action = s[0];
	BoardSize bs;
	switch (atoi(&action)) {
	case GameActions::GiveColor:
		

		if (s.substr(1, s.length() - 1) == "black") {
			myColor = FieldColor::BLACK;
			
		}

		else {
			myColor = FieldColor::WHITE;
		}
		colorSet = true;
		break;
	case GameActions::GameSize:
		
		bs = (BoardSize)atoi(s.substr(1, s.length() - 1).c_str());
		
		utilities.applicationSettings.setBoardSize(bs);
		gameSizeSet = true;
		break;
	case GameActions::SetKomi:
		
		if (s.substr(1, s.length() - 1) == "true") {
			utilities.applicationSettings.setKomi(true);
		
		}			
		else
			utilities.applicationSettings.setKomi(false);
		komiSet = true;
		break;
		
	}

}
void ConnectingState::disconnected() {
	currentState = Disconnected;
	
}


void ConnectingState::tryConnect(void)
{

	networkConnection->setReceivedCallback(std::bind(&ConnectingState::dataReceived, this));
	if (networkConnection->start(54000,utilities.applicationSettings.getIp())) {
		
		currentState = ConnectionState::Connected;
		
	}
	else {
		currentState = Disconnected;
		networkConnection->stop();
		std::string info;
		if (networkConnection->isServer())
			info = "Serwer zatrzymany";
		else
			info = "Przekroczono czas polaczenia";
		getStateManager()->pushState(make_unique<AlertState>(getStateManager(), utilities, info));
	}
}