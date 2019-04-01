#pragma once
#include <SFML\Network.hpp>


#include "Callback.h"
class NetworkThread;
//! Klasa reprezentuje klienta dla połączenia sieciowego typu TCP.
	/*!
		Obiekt tej klasy zarządza gniazdem TcpSocket odpowiadającym za komunikację
		po protokole TCP.
	*/
class TcpClient: public Callback
{
private:
	
	
	bool connect(unsigned int port, sf::IpAddress ip = "127.0.0.1");
	friend class NetworkThread;
protected:
	sf::TcpSocket socket; /**<Obiekt reprezentujący gniazo TCP*/
	std::string message; /**< Ostatni odebrany ciąg znaków z sieci*/
	
public:
	//! Konstruktor
	TcpClient();
	//! Destruktor 
	/*!
		Zamyka połączenie gniazda TCP.
	*/
	virtual ~TcpClient();
	//! Metoda inicjuje połączenie TCP do serwra.
	/*!
		Metoda podejmuje próbę połączenia się z serwerem TCP gry o adresie IP zdefiniowanym w ustawieniach gry.
		Łączenie się poprzez gniazdo TCP jest operacją blokującą dlatego zaleca się wywołanie tej metody
		w osobnym wątku. Funcka zwraca prawde w przypadku ustanowienia połączenia. Fałsz gdy nie można się połączyć, bądź
		przekroczono systemowy czas połączenia.
		\param port Port do którego łączymy się.
		\param ip IP serwera do którego łączymy się.
		\return bool Zwraca prawdę w przypadku pozytywnego rezultatu połączenia.
	*/
	virtual bool start(unsigned int port, sf::IpAddress ip = "127.0.0.1");
	//! Metoda oczekuje na odbiór danych.
	/*!
		Wywołuje metodę receiveData() [SPRAWDŹ]. Jedyna różnica polega na wirtualizacji tejże metody loop()
		dzięki czemu może być ona rozszerzona o dodatkowe funkcjonalności np. w klasie TcpServer.
		\return void
	*/
	virtual void loop();

	//! Metoda zwraca ostatni odebrany pakiet danych
	/*!
		\return std::string Ciąg znaków reprezentujący ostatni odebrany pakiet danych.
	*/
	std::string getLastMessage()const { return message; }

	//! Metoda wysyła pakiet danych do drugiego gracza.
	/*!
		\param packet Pakiet danych do wysłania.
		\return sf::Socket::Status Zwraca status połączenia/operacji.
	*/
	sf::Socket::Status sendData(sf::Packet& packet);
	//! Metoda oczekuje na odbiór danych.
	/*!
		Metoda oczekuje aż pakiety danych dotrą do gniazda TCP, następnie je odczytuje. Jest metodą która
		wykonuje operacje blokujące zatem zaleca się jej wywołanie w osobnym wątku aplikacji.
		\return void
	*/
	void receiveData();
	
	//! Metoda zamyka połączenie TCP
	/*!
		Zamyka aktywne połączenie gniazda TCP.
		\return void
	*/
	virtual void closeConnection();
	bool close; /**<Pole informuje o tym czy połączenie zostało zerwane/zamknięte*/
};

