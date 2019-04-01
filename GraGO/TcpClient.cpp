#include "TcpClient.h"



TcpClient::TcpClient():close(false)
{

}

bool TcpClient::start(unsigned int port, sf::IpAddress ip )
{
	return connect(port,ip);
}

bool TcpClient::connect(unsigned int port, sf::IpAddress ip )
{
	close = false;
	if (socket.connect(ip, port) != sf::Socket::Done)
	{
		
		return false;
	}
	
	return true;
}

sf::Socket::Status TcpClient::sendData(sf::Packet& packet)
{	
	return socket.send(packet);
}

void TcpClient::receiveData()
{
	sf::Packet packet;

	if (socket.receive(packet) != sf::Socket::Done)
	{
		closeConnection();
		
	}
	else {
		message.clear();
		packet >> message;
		
		
		callback();
	}
	
}

void TcpClient::loop()
{
	
	receiveData();
	
	
}

void TcpClient::closeConnection()
{
	close = true;
	socket.disconnect();
}


TcpClient::~TcpClient()
{
	close = true;
	socket.disconnect();
}
