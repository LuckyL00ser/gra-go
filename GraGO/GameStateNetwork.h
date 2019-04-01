#pragma once

#include "GameState.h"
#include <thread>
#include "AlertState.h"
#include "NetworkThread.h"
#include "GUIImage.h"

enum GameActions {
	GiveColor = 0,
	GameSize = 1,
	Move = 2,
	Pass = 3,
	EndGame = 4,
	SetKomi = 5
};
enum ConnectionState {
	Disconnected = 0,
	Connecting = 1,
	Connected = 2,
	Running = 3

};
//! Klasa reprezentująca stan aplikacji typu gra sieciowa.
	/*!
		Dziedziczy z klasy GameState rozszerzając jej funkcjonalność o możliwość gry przez sieć z innym graczem.
		Odpowiada za ustanawianie i zakończanie połączeń.
	
	*/
class GameStateNetwork :
	public GameState
{
private:

	std::mutex refreshMutex;
	NetworkThread& networkConnection;
	GUI::GUIButton* abortButton;
	std::thread* network;
	ConnectionState currentState;
	FieldColor myColor;
	void endGame();

public:
	//! Konstruktor
	/*!
		Inicjalizuje niezbędne pola na podstawie przekazanych argumentów. Wywołuje jawnie konstruktor klasy bazowej
		GameState. Łączy zdarzenia sieciowe (ustanowienie połącznia, przekroczony czas łączenia itp.) z odpowiednimi metodami (mechanizm callback).
		Tworzy pola z przyciskami dla planszy.
		\param state Menedżer stanów.
		\param utilities Struktura przydatnych obiektów/zmiennych
		\param nt Wskaźnik na obiekt klasy Network Thread
		\param runningThread Wskaźnik na istniejący wątek opodowiadający na obsługę blokujących gniad.
		\param color Kolor gracza lokalnego.
	

	*/
	GameStateNetwork(StateManager* state, const Utilities& utilities,NetworkThread* nt, std::thread* runningThread,FieldColor color);
	//! Destruktor
	/*!
		Wymuszone wywołanie np. gracz rezygnujący z połączenia, zamyka dodatkowo utworzony wątek łączenia i niszczy obiekt.

	*/
	~GameStateNetwork();
	//! Odświeża stan obiektu, reaguje na zdarzenia.
	/*!
		Odświezą ten stan gry i elementy potomne. Wykrywa rozłączenie połączenia. Wykrywa spasowanie gracza i wysyła informajcę o tym
		do przeciwnika.
		\param e Zdarzenie
		\param window Okno głowne aplikacji
		\return void
	*/
	void update(sf::Event& e, sf::RenderWindow& window);
	//! Renderuje stan gry.
	/*!
		Renderuje stan gry
		\return void
	*/
	void draw() const;
	//! Metoda przetwarza odebrane z sieci dane.
	/*!
		Metoda interpretuje odebrany pakiet danych z sieci, wyznacz zaistniałą akcję:
		-nadanie koloru gracza,
		-wykonanie ruchu gracza (postawienie pionu na planszy),
		-pass przeciwnika
		\param s pakiet danych
		\return void
	*/
	void processData(std::string s);
	//! Metoda reaguje na odbiór danych.
	/*!
		Metoda callback przekazywana do obiektu odpowiadającego za przetwarzanie zdarzeń sieciowych. Wywoływana przez ten
		obiekt w reakcji na odbiór danych z sieci. Przekazuje odebrany pakiet jako argument metody processData(std::string)
		
		\return void
	*/
	void dataReceived();
	//! Zmienia stan połączenia na rozłączone.
	/*!
		Metoda mechanizmu callback.

		\return void
	*/
	void disconnected();
	//! Metoda reaguje na niespodziewane rozłączenie.
	/*!
		Metoda callback przekazywana do obiektu odpowiadającego za przetwarzanie zdarzeń sieciowych. Wywoływana przez ten
		obiekt w reakcji na rozłączenie się drugiego gracza. Wstawia na stos menadżera stanów, stan informujący o nieprzewidzianym
		zakończeniu rozgrywki na skutek utraty połączenia.

		\return void
	*/
	void disconnect();
	//! Metoda stawiania pionu na planszy.
	/*!
		Metoda odpowiada za postawienie pionu na planszy podczas ruchu gracza "lokalnego". Jesli ruch jest poprawny informacja
		o ruchu przesyłana jest do przeciwnika, a przyciski planszy zostają zablokowane.
		\param x Kolumna planszy na której znaduje się pion.
		\param y Wiersz planszy na której znaduje się pion.
		\return void
	*/
	void putStone(unsigned int x, unsigned int y);
};


