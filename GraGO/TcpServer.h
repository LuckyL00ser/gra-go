#pragma once
#include <SFML\Network.hpp>
#include <time.h>
#include "TcpClient.h"
//! Klasa reprezentuje serwer dla połączenia sieciowego typu TCP.
	/*!
		Obiekt tej klasy zarządza obiektem klasy TcpListener inicjując nasłuchwanie na protokole TCP
		i tym samym hosting gry. Sama komunikacja identyczna jest jak dla obiektu klasy TcpSocket stąd klasa
		ta dziedziczy z klasy bazowe TcpClient.
	*/
class TcpServer: public TcpClient
{
private:
	sf::TcpListener listener; //tylko jedno polaczenie
	
	bool serverIsBlackPlayer;

public:
	//! Konstruktor
	TcpServer();
	//! Metoda informująca o kolorze gracza który jest serwerem.
	/*!
		\return bool Zwraca prawdę jeśli gracz hostujący grę jest graczem czarnym.
	*/
	bool getifServerIsBlack()const { return serverIsBlackPlayer; }
	//! Metoda inicjuje połączenie.
	/*!
		Jest to klasa serwera zatem połączenie rozpoczyna się od nasłuchiwania na przychodzące połączenie
		ze strony innego gracza będącego klientem. Operacja nasłuchiwania jest blokująca, czeka na przyjście połączenia
		zatem sugeruje się wywoływanie tej funkcji w osobnym wątku. Metoda losuje gracza który rozpocznie rozgrywkę i po
		nawiązaniu połączenia informuje o tym instancje gry obydwu graczy.
		\param port Port na którym ustanawiamy serwer.
		\param ip Dla serwera parametr ten jest bez znaczenia.
		\return bool Zwraca prawdę jeśli ustanowienie połączenia powiodło się.
	*/
	bool start(unsigned int port, sf::IpAddress ip="127.0.0.1");
	//! Metoda odpowiadająca za komunikację.
	/*!
		Wewnątrz tej metody znajduje się wywołanie metody loop z klasy bazowej TcpClient.
		Komunikacja dla serwra jest identyczna jak dla klienta.
		\return void
	*/
	void loop();
	//! Metoda zamykająca połączenie TCP.
	/*!
		Wywołuje metodę closeConnection() z klasy bazowej TcpClient i ewentualnie zamyka obiekt nasłuchiwania jeśli nie ustanowiono
		połączenia.
		\return void
	*/
	void closeConnection();
	//! Destruktor
	/*!
		Kończy oczekiwanie na połączenie.
	*/
	~TcpServer();
};

