#pragma once
#include "BaseState.h"
#include "GUIGroup.h"
#include "Game.h"
#include "Utilities.h"
#include "GUIButton.h"
#include "GUILabel.h"
#include "GUIImage.h"
#include "GUILine.h"
#include "GameGUIView.h"
#include "StateManager.h"
#include "GameOverState.h"
//! Klasa reprezentująca stan aplikacji typu gra.
	/*!
		Dziedziczy z klasy BaseState. Łączy logikę gry z warstwą prezentacji (wyłącznie dla stanu rozgrywki), agregując obiekty
		klas Game oraz GameGUIView.
		\return void
	*/
class GameState : public BaseState
{

protected:
	Game game; /**<Obiekt gry, reprezentujący jej logikę*/
	GameGUIView gameView; /**< Obiekt gry reprezentujący jej graficzną prezentację*/
	
	//! Metoda wywoływana gdy gra zostaje zakończona.
	/*!
		Metoda wstawia na stos menadżera stanów gry, nowy stan wyświetlający informację
		o zakończeniu rozgrywki i dający graczowi możliwość podjęcia decyzji czy chce
		zagrać jeszcze raz czy też powrócić do menu.
		\return  void
	*/
	virtual void endGame();
public:
	//! Konstruktor
	/*!
		Wywołuje jawnie konstruktor klasy bazowej BaseState. Inicjluje ustawienia gry pobieranie z ustawień.
		Ustawia reakcję na zakończenie rozgrywki wywoływane przez agregowany obiekt klasy GameGUIView.
	*/
	GameState(StateManager* state,const Utilities& utilities);
	//! Destruktor
	/*!
		Wirtualny destruktor. Przystosowuje klasę do dziedziczenia.
	*/
	virtual ~GameState();
	//! Odświeża stan obiektu, reaguje na zdarzenia.
	/*!
		Odświezą ten stan gry i elementy potomne. Wykrywa wciśnięcie klawisza odpowiadającego za pass ("P").
		\param e Zdarzenie
		\param window Okno głowne aplikacji
		\return void
	*/
	virtual void update(sf::Event& e, sf::RenderWindow& window);
	//! Renderuje stan gry.
	/*!
		Renderuje agregowany obiekt gameView.
		\return void
	*/
	virtual void draw() const;

	
};

