#include "NetworkThread.h"





std::string NetworkThread::getData()
{
	
	return tcpConnection->getLastMessage();
	
}

NetworkThread::NetworkThread(bool isServer, BoardSize s,bool komi):server(isServer),bs(s),k(komi)
{
	if (server) {
		tcpConnection = new TcpServer();
		
		
	}
	else {
		tcpConnection = new TcpClient();
		
	}


	
}
NetworkThread::~NetworkThread()
{
	tcpConnection->closeConnection();
	
	delete tcpConnection;
}

void NetworkThread::sendData(sf::Packet& packet)
{
	sf::Socket::Status status = tcpConnection->sendData(packet);
	switch (status) {
	case sf::Socket::Done:
		
		
		break;

	case sf::Socket::Disconnected:
	case sf::Socket::Error:
		stop();	
	}
}

void NetworkThread::setReceivedCallback(EventCallback cb)
{
	tcpConnection->setCallback(cb);
}



bool NetworkThread::start(unsigned int port, std::string ip)
{
	bool success =  tcpConnection->start(port, ip);
	if (server) { //wysyla rozmiar planszy
		char x[3];
		_itoa_s(static_cast<int>(bs), x, 10);
		sf::Packet p;
		std::string tmp = "1";
		tmp += x;
		p << tmp;
		tcpConnection->sendData(p);
		tcpConnection->message = tmp;
		tcpConnection->callback();

		tmp = "5"; //wysyla czy korzysatc z reguly komi
		tmp += (k ? "true" : "false");
		sf::Packet p2;
		p2 << tmp;
		tcpConnection->sendData(p2);
		tcpConnection->message = tmp;
		tcpConnection->callback();
		
	}
	return success;

}

void NetworkThread::stop()
{
	
	tcpConnection->closeConnection();
	
}

void NetworkThread::loop()
{
	bool close=false;
	while (!close) {
		tcpConnection->loop();
		mutex.lock();
		
		close = tcpConnection->close;
		mutex.unlock();
	}	
	
	callback(); //rownowazne z utrata polaczenia

}

