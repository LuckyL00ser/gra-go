#pragma once
#include "BaseState.h"
#include "Utilities.h"
#include "GUIGroup.h"
#include "GUILabel.h"
#include "GUIButton.h"
#include "StateManager.h"
#include "GameState.h"
//! Stan gry informujący o zakończonej rozgrywce.
	/*!
		Klasa stanu gry informującego o zakończeniu rozgrywki i jej rezultacie.
		
	*/
class GameOverState : public BaseState, public GUI::GUIGroup
{
private:
	GUI::GUIButton* newGame;
	GUI::GUIButton* backToMenu;
	GUI::GUILabel* label;
	GUI::GUILabel* points;
	void createGUI();
public:
	//! Konstruktor
	/*!
		Konstruktor inicjalizuje niezbędne pola, wywołuje jawnie konstruktor klasy bazowej BaseState, inicjalizuje i ustawia
		elementy graficzne GUI.

	*/
	GameOverState(StateManager* stateManager,const Utilities& utilities,Player* winner,bool newGame);
	//! Destruktor
	
	~GameOverState();
	//! Odświeża stan obiektu
	/*!
		Odświezą stan gry i elementy potomne np. GUI.
		\param e Zdarzenie
		\param window Okno głowne aplikacji
		\return void
	*/
	void update(sf::Event& e, sf::RenderWindow& window);
	//! Renderuje stan gry.
	/*!
		Renderuje stan gry, planszę i towarzyszące mu obiekty np. GUI.
		\return void
	*/
	void draw() const;

	//! Metoda wywoływana po kliknięciu przycisku nowej gry.
	/*!
		Zdejmuje ze stostu menadżera stanów dwa wierzchnie stany tj. sam siebie oraz niezamkniętą grę pod spodem tym samym niszcząc te obiekty.
		Odkłada na szczyt stosu stan nowej gry.
		\return void
	*/
	void createNewGame();
	//! Metoda wywoływana po kliknięciu przycisku powrotu do menu.
	/*!
		Zdejmuje ze stostu menadżera stanów dwa wierzchnie stany tj. sam siebie oraz niezamkniętą grę pod spodem tym samym niszcząc te obiekty.
		Poniżej na stosie znajduje się menu do któro tym samym znajduje się po wywołaniu na szcycie stosu i jest aktualnym stanem gry.
		\return void
	*/
	void goBackToMenu();
};

