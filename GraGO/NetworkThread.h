#pragma once

#include "TcpClient.h"
#include "TcpServer.h"
#include "Callback.h"
#include <mutex>
#include "Settings.h"

//! Klasa obsługująca połączenia sieciowe.
/*!
	Klasa odpowiedzialna jest za nawiązywanie i zarządzanie połączeniem sieciowym.
	Uruchamiana jest w osobnym wątku ze względu na wykorzystanie z blokujących gniazd sieciowych.
*/
class NetworkThread :public Callback
{

private:
	bool server;
	TcpClient * tcpConnection;
	BoardSize bs;
	bool k;
public:
	std::mutex mutex; /**<Obiekt mutex umożliwia wyłącznościowy dostęp do zasobu jakim jest pakiet przesłanych danych*/
	//! Konstruktor
	/*!
		Ustawia rodzaj (klient/serwer) i parametry połączenia.
	*/
	NetworkThread(bool isServer,BoardSize s=(BoardSize)1,bool komi=false);
	//! Destruktor
	/*!
		Zamyka połączenie.
	*/
	~NetworkThread();
	//! Metoda zwraca informację czy aplikacja uruchomiona jest w trybie serwera.
	/*!
		\return bool Prawda jeśli aplikacja jest serwerem rozgrywki.
	*/
	bool isServer()const { return server; }
	//! Metoda zwraca ostatnio odebrany pakiet danych z sieci.
	/*!
		\return std::string Pakiet danych.
	*/
	std::string getData();
	
	//! Metoda wysyła dane do przeciwnego gracza.
	/*!
		\param packet Paczka danych.
		\return void
	*/
	void sendData(sf::Packet& packet);
	//! Metoda zmienia funkcję callback.
	/*!
		Przekazana w argumencie funkcja wywoływana jest później jako reakcja na odebranie porcji danych.
		\param cb Wskaźnik do funkcji.
		\return void
	*/
	void setReceivedCallback(EventCallback cb);
	//! Metoda inicjuje połączenie.
	/*!
		Metoda inicjuje połączenie. Ponadto jeśli aplikacja pełni role serwera, wysyła do przeciwnika (narzuca) swoje reguły gry tzn.
		kolor graczy, obecnośc reguły komi, rozmiar planszy. Domyślnie łączy się z komputerem lokalnym.
		\param port Port komunikacji sieciowej.
		\param ip Adres IP urządzenia do którego łączy się klient. Domyślnie maszyna lokalna.
		\return bool Prawda jeśli udało się połączyć, fałsz w przeciwnym wypadku.
	*/
	bool start(unsigned int port, std::string ip="127.0.0.1");
	//! Metoda przerywa połączenie.
	/*!
		\return void
	*/
	void stop();
	//! Metoda obsługująca komunikację.
	/*!
		Zawiera nieskończoną pętle która przerywana jest dopiero w momencie zerwania/zakończenia połączenia.
		\return void
	*/
	void loop();
	


};




