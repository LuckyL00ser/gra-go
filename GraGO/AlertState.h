#pragma once
#include "BaseState.h"
#include "GUIButton.h"
#include "GUILabel.h"
#include "GUIGroup.h"
#include "StateManager.h"
using namespace GUI;
//!  Klasa stanu gry wyświetlającego komunikat 
/*!
	Stan gry wyświetlający komunikat na ekranie oraz przycisk powrotu do poprzedniego stanu
	na stosie stanów menadżera. Używana np. przy próbie nawiązania połączenia przez sieć
	by poinformować o niepowodzeniu operacji, rozłączeniu się drugiego gracza itp.
*/
class AlertState :	public BaseState, public GUIGroup
{
private:

	GUIButton* back; /**< Wskaznik do klasy GUIButton, czyli przycisku powrotu do poprzedniego stanu gry */
	GUILabel* info; /**< Wskaznik do klasy GUILabel, czyli wizualnej klasy przetrzymujacej komunikat*/
	//! Metoda tworzaca interfejs graficzny.
	/*!
	  Metoda wywoływana jest w konstruktorze, inicjuje pola back oraz info.
	*/
	void createGUI();	
	//! Metoda reagujaca na wcisniecie przycisku "back".
	/*!
		Metoda podawana jest jako argument do obiektu back, jej celem jest reakcja na wcisniecie przycisku.
		Powraca do poprzedniego stanu gry.
	*/
	void goBack();
	std::string message; /**< zmienna przechowujaca wyswietlany komunikat*/
public:
	//! Konstruktor.
	/*!
	  \param state Wskaźnik do menedżera stanów.
	  \param utilities Referencja na stałą strukturę zawierającą przydatne obiekty.
	  \param msg Zmienna zawierająca komunikat od wyświetlania.
	*/
	AlertState(StateManager* state, const Utilities& utilities,std::string msg);
	//! Destruktor
	~AlertState();

	//! Funkcja odświeżająca stan obiektu.
	/*!
		\param e Referencja do zdarzenia jakie mogło nastąpić.
		\param window Referencja do aktualnego okna renderującego widok gry.
		\return void
	*/
	void update(sf::Event& e, sf::RenderWindow& window);
	//! A constructor.
	/*! Funkcja wyrysowująca obiekt.
	\return void
	*/
	void draw() const;
};

