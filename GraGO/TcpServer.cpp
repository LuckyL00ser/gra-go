#include "TcpServer.h"



TcpServer::TcpServer()
{
	srand(time(NULL));
	
}

bool TcpServer::start(unsigned int port, sf::IpAddress ip)
{
	
	if (listener.listen(port) != sf::Socket::Done) // rozpoczynamy nas³uchiwanie na porcie 'port'
	{
		
		return false;
	}


	if (listener.accept(socket) != sf::Socket::Done) {
		
		return false;
	}
	//polaczenie nawiazane

	serverIsBlackPlayer = rand() % 2;
	sf::Packet firstMessage;

	firstMessage << (serverIsBlackPlayer ? "0white" : "0black"); // akcja nr 0 - przypisanie koloru gracza
	sendData(firstMessage);

	message=(serverIsBlackPlayer ? "0black" : "0white");
	callback();
	

	return true;

}

void TcpServer::loop()
{
	
	TcpClient::loop();

	
			
	
}

void TcpServer::closeConnection()
{
	TcpClient::closeConnection();
	listener.close();
}




TcpServer::~TcpServer()
{
	
	listener.close();
}
