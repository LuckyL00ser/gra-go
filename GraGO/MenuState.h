#pragma once
#include "BaseState.h"
#include "GUIGroup.h"
#include"Utilities.h"
#include "GUILabel.h"
#include "GUIButton.h"
#include "GUIImage.h"
#include "StateManager.h"
#include "GameState.h"
#include "SettingsState.h"

#include "ConnectingState.h"
//! Klasa reprezntująca menu gry.
	/*!
		Klasa będąca menu gry jest jednocześnie jednym ze stanów gry (dziedziczy z BaseState). Jest pierwszym stanem jaki wrzucany jest
		do menadżera stanów po uruchomieniu aplikacji i jednoczesnie ostatnim zdejmowanym ze stostu stanem. Dziedziczy również z GUIGroup
		by umożliwić sprawną manipulację elementami graficznymi menu. 
	*/
class MenuState : public BaseState , public GUI::GUIGroup
{
	
private:
	
	void onStartGameClick();
	void onExitClick();
	void onSettingsClick();
	void createGUI();
	void onConnectClick();
	void onHostClick();
public:
	//! Konstrutor
	/*!
		Inicjuje niezbędne pola wymagane przez klasę bazową BaseState przekazując argumenty do konstruktora klasy bazowej.
		Wywołuje metodę createGUI() tworząca interfejs graficzny menu.
	*/
	MenuState(StateManager* state, const Utilities& utilities);
	//! Destruktor
	/*!
		Zwalnia pamięć.
	*/
	~MenuState();

	//! Metoda odpowiadająca za odświeżanie stanu gry oraz agregowanych obiektów graficznych.
	/*!
		Za odświeżanie "dzieci" menu odpowiedzialna jest funkcja update klasy potomnej GUIGroup.
		\param e Referencja do zdarzenia jakie wystapiło.
		\param window Referencja do okna aplikacji w którym należy wyrysować obiekt.
		\return void
	*/
	void update(sf::Event& e, sf::RenderWindow& window);
	//! Metoda odpowiadająca za renderowanie stanu gry.
	/*!
		
		\return void
	*/
	void draw() const;
};

