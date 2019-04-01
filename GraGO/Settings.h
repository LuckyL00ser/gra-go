#pragma once
#include <fstream>
#include <string>
#include "Callback.h"

enum WindowResoultion { /**<Enum reprezentujący rozmiar okna gry*/
	RES_800x600=0,
	RES_1024x756=1,
	RES_1280x720=2,
	RES_1600x900=3,
	RES_1920x1080=4
};
enum  BoardSize { /**<Enum reprezentujący rozmiar planszy gry*/
	SIZE_5x5 = 5,
	SIZE_9x9 = 9,
	SIZE_11x11 = 11,
	SIZE_13x13 = 13,
	SIZE_19x19=19

};
//! Klasa reprezntująca ustawienia gry.
	/*!
		Odczytuje i zapisuje do pliku ustawienia gry. W trakcie działania aplikacji wystawia te parametry do odczytu
		i modyfikacji zewnętrznym klasom.
	*/
class Settings : public Callback
{
private:
	const char* settingsFilePath = "ustawienia.cfg";

	unsigned windowSizeX, windowSizeY;
	bool fullscreen;
	bool komi; //reguła "kompensujaca" fakt ze gre zawsze rozpoczyna czarny, +7,5 punktow dla bialego

	WindowResoultion resolution;
	BoardSize boardSize;
	std::string ip;
	

public:
	//!Konstruktor
	/*!
		Inicjuje domyślne parametry gry. Następnie odczytuje ustawienia z pliku.
	*/
	Settings();
	//!Destruktor
	/*!
		Niszczy obiekt. Zapisuje ustawienia gry do pliku.
	*/
	~Settings();
	//!Metoda umożlwia zmianę rozdzielczości okna gry.
	/*!
		\param resolution Nowa rozdzielczość okna gry.
		\return void
	*/
	void setResolution(WindowResoultion resolution);
	//!Metoda zwraca rozdzielczość okna gry.
	/*!
		
		\return WindowResolution Rozdzielczość okna gry.
	*/
	WindowResoultion getResolution() const;
	//!Metoda zwraca szerokość okna gry.
	/*!

		\return unsigned Szerokość okna gry.
	*/
	unsigned getWindowSizeX() const;
	//!Metoda zwraca wysokość okna gry.
	/*!

		\return unsigned wysokość okna gry.
	*/
	unsigned getWindowSizeY() const;
	//!Metoda zwraca informację o tym czy gra uruchomiona jest w trybie pełnoekranowym
	/*!

		\return bool Prawda jeśli włączony jest tryb pełnoekranowy.
	*/
	bool getFullscreen() const;
	//!Metoda włącza/wyłącza tryb pełnoekranowy gry.
	/*!
		\param useFullscreen Zmienna określa czy gra ma być w trybie pełnoekranowy.
		\return void
	*/
	void setFullscreen(bool useFullscreen);
	//!Metoda zwraca rozmiar planszy rozgrywki.
	/*!

		\return BoardSize Rozmiar planszy gry.
	*/
	BoardSize getBoardSize()const;
	//!Metoda zmienia rozmiar planszy gry.
	/*!
		\param bSize Nowy rozmiar planszy gry.
		\return void
	*/
	void setBoardSize(BoardSize bSize);
	//!Metoda zwraca informację o tym czy gra korzysta z reguły komi
	/*!
		Reguła komi dodaje białemu graczowi +7,5 punkta - kompensuje to stratę związaną z faktem iż to czarny gracz
		zawsze rozpoczyna rozgrywkę. Połówka punkta zapobiega remisom.
		
		\return bool Jeśli prawda, gra korzysta z reguły komi.
	*/
	bool getKomi()const;
	//! Metoda ustawia czy gra będzie korzystać z reguły komi.
	/*!
		Reguła komi dodaje białemu graczowi +7,5 punkta - kompensuje to stratę związaną z faktem iż to czarny gracz
		zawsze rozpoczyna rozgrywkę. Połówka punkta zapobiega remisom.
		\param k Aktywność reguły komi.
		\return void
	*/
	void setKomi(bool k);
	//! Metoda zmienia IP serwera z którym łączy się gracz
	/*!
		Jako argument podajemy w formie tekstowej adres oponenta który uruchamia u siebie grę w trybie serwera.
		\param newIp Nowy adres IP.
		\return void
	*/
	void setIP(std::string newIp);
	//! Metoda zwraca IP serwera z którym łączy się gracz.
	/*!
		\return std::string Adres IP.
	*/
	const std::string& getIp()const;
	
	//! Metoda odczytuje ustawienia gry z pliku.
	/*!
		Ustawienia gry zapisane są w pliku "ustawienia.cfg". W pliku opisano znaczenie poszczególnych wartości.
		
		\return void
	*/
	void loadSettingsFromFile();
	//! Metoda zapisuje ustawienia gry do pliku.
	/*!
		Ustawienia gry zapisywane są do pliku "ustawienia.cfg". W pliku opisano znaczenie poszczególnych wartości.

		\return void
	*/
	void saveSettingsToFile();
	
	const float komiValue = 7.5; /**<Wartość współczynnika reguły komi*/
	
};

