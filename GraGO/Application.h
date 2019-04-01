#pragma once
#include "Settings.h"
#include "Game.h"
#include "StateManager.h"
#include "ResourceManager.h"
#include "GameState.h"
#include "MenuState.h"
//!  Klasa główna aplikacji 
/*!
  Klasa inicjalizująca wszystkie podstawowe składowe aplikacji niezbędne do jej dziłania i uruchamiania
  kolejnych funkcjonalności. 
*/
class Application
{
private:
	Settings appSettings; /**< Pole przechowujące obiekt ustawień gry.*/
	StateManager stateManager; /**< Menadżer stanów gry.*/
	sf::RenderWindow window;	/**< Okno główne programu.*/
	Utilities* utilities;	/**<Wskaźnik do struktury przechowującej zmienne i klasy pomocne innym obiektom aplikacji.*/
	ResourceManager<ResourceIDs::TextureID, sf::Texture> textureManager; /**< Menadżer zasobów dla tekstur.*/
	ResourceManager<ResourceIDs::FontID, sf::Font> fontManager;	/**<Menadżer zasobów dla czcionek.*/
	//! Metoda ustawiająca i tworząca najlpilniej potrzebne elementy aplikacji.
	/*!
	Tworzy okno gry, strukturę narzędziową Utilities, dodaje ścieżki do menadzerów zasobów, wstawia początkowy stan (menu) do 
	menadżera stanów.
	  \return void
	*/
	void initialize();	
	//! Dodaje ścieżki zasobów do menadżera zasobów.
	/*!
		Metoda ustawia w poszczególnych menadżerach zasobów ściezki do plików i skojarzone z nimi identyfikatory zasobów.
		\return void
	*/
	void addResourcesPaths();
	//! Metoda (callback) reagująca na wciśnięcie przycisku wyjścia z aplikacji.
	/*!
		W konstruktorze metoda ta przekazywana jest jako argument dla konstruktora menadżera stanów, który w sytuacji gdy użytkownik 
		chce wyjść z gry, wywołuje przypisany callback (czyli tę metode) informując klasę aplikacji o zamiarach użytkownika.
		\return void
	*/
	void exitApplication();
	//! Metoda (callback) reagująca na zmianę rozmiaru ekranu w obiekcie ustawień.
	/*!
		Callback wywoływany przez klasę Settings w przypadku gdy dojdzie do zmiany rozmiaru okna gry. Wymusza na klasie Application
		utworzenie okna o nowych rozmiarach i zaaplikowanie tej zmiany w odpowiednich miejscach, tak aby wszystkie elementy graficzne 
		aplikacji mogły korzystać z nowego RenderTargetu jakim jest okno.
		\return void
	*/
	void setFullscreenMode();
	
public:
	//! Konstruktor
	/*!
		Wywołuje metodę initialize(), ustawia odpowiedni callback dla menadżera stanów.
	*/
	Application();
	//!Destruktor
	/*!
		Zwalnia zasoby.
	*/
	~Application();
	
	//!Funkcja przetwarzająca zdarzenia.
	/*!
		Przetwarza zdarzenia wywoływane na rzecz aplikacji przez użytkownika, kliknięcia, ruchy myszy itd. przekazując je dalej 
		aby każdy element mógł odpowiednio na nie zareagowac. Obsługuje pętlę główną gry.
		\return void
	*/
	void processEvents();
	//! Metoda zarządzająca wyświetlaniem.
	/*!
		Odświeża ekran gry, wymusza wyrenderowanie się na nowo obecnego stanu gry przechowywanego w menadżerze stanów.
		\return void
	*/
	void render();
};

