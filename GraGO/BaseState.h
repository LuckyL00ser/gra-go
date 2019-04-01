#pragma once
#include "Utilities.h"
#include <SFML\Window\Event.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
class StateManager;
//! Abstrakcyjna klasa bazowa dla wszystkich klas stanów gry.
	/*!
		Z tej klasy dziedziczą wszystkie klasy umieszczane na stosie menadżera stanów gry. Jest abstrakcyjna.
		\return void
	*/
class BaseState
{
private:
	StateManager* stateManager; /**<Wskaźnik do menadżera stanów.*/
protected:
	const Utilities& utilities; /**<Referencja do struktury zawierającej przydatne obiekty i zmienne.*/
public:
	//! Konstruktor
	/*!
		Klasa BaseState nie może istnieć bez zainicjowania swoich dwóch pól wskaźnikowych.
		Ich istnienie wymuszają parametry przekazywane przez referencję.
		\param myStateManager Wskaźnik na menedżer stanów gry.
		\param context Referencja do struktruty zawierającej użyteczne pola i obiekty.
	*/
	BaseState(StateManager* myStateManager,const Utilities& context) :stateManager(myStateManager),utilities(context) {}
	//! Destruktor.
	
	virtual ~BaseState() {}
	//! Czysto wirtualna metoda odpowiadająca za odświeżanie stanu obiektów.
	/*!
		Niesprecyzowana metoda do implementacji w klasach potomnych. Każdy stan gry zależnie od funkcjonalności
		może posiadać indywidualny sposób reagowania
		na zdarzenia i odświeżanie swojego stanu.
		\param e Referencja do zdarzenia jakie wystapiło.
		\param window Referencja do okna aplikacji w którym należy wyrysować obiekt.
		\return void
	*/
	virtual void update(sf::Event& e, sf::RenderWindow& window) = 0;
	//! Czysto wirtualna metoda odpowiadająca za renderowanie stanu gry.
	/*!
		Niesprecyzowana metoda do implementacji w klasach potomnych. Każdy stan gry zaleznie od funkcjonalności
		może posiadać indywidualny sposób prezentowania swojej zawartości.
		\return void
	*/
	virtual void draw() const= 0;
	//! Metoda zwracająca wskaźnik do menadżera stanów.
	/*!
		
		\return StateManager*
	*/
	StateManager* getStateManager()const;
	
};

