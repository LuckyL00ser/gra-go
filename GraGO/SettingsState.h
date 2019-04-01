#pragma once
#include "BaseState.h"
#include "GUIGroup.h"
#include "GUIButton.h"
#include "GUITextField.h"
#include "GUIImage.h"
#include "GUILabel.h"
#include "GUITickbox.h"
#include "StateManager.h"
#include "MenuState.h"
//! Klasa reprezentująca stan gry typu ustawienia.
	/*!
		Klasa umożliwia graficzne przedstawienie ustawień gry oraz ich łatwą modyfikację użytkownikowi gry.
	
	*/
class SettingsState :
	public BaseState, public  GUI::GUIGroup
{
private:
	void createGUI();
	void createLabels();
	void createTickboxes();
	void createResolutionButtons();
	void createBoardSizeButtons();
	void setFullscreen();
	void setKomi();
	void setIP();
	void setResolution(WindowResoultion newSize);
	void setBoardSize(BoardSize newSize);
	void exitToMenu();

	GUI::GUITextField* tf; //przetrzymuje ip
	
public:
	//!Konstruktor
	/*!
		Inicjuje podstawowe pola klasy oraz klas bazowych. Wywołuje metodę createGUI() tworzącą interfejs graficzny 
		ustawień.

	*/
	SettingsState(StateManager* state, const Utilities& utilities);
	//! Destruktor
	/*!
		Niszycz obiekt.
	*/
	virtual ~SettingsState();

	//! Metoda odpowiadająca za odświeżanie stanu gry oraz graficznych elementów potomnych.
	/*!
		Implementacja czysto wirtualnej metody z klasy BaseState. Odświeżaniem zajume się metoda
		update dziedziczona z klasy GUIGroup.
		\param e Referencja do zdarzenia jakie wystapiło.
		\param window Referencja do okna aplikacji w którym należy wyrysować obiekt.
		\return void
	*/
	void update(sf::Event& e, sf::RenderWindow& window);
	//! Metoda odpowiadająca za renderowanie stanu gry.
	/*!
		Implementacja czysto wirtualnej metody z klasy BaseState. Renderuje obiekty graficzne ustawień agregowane przez
		klasę bazową GUIGroup.
		\return void
	*/
	void draw() const;
};

