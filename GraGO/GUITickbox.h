#pragma once
#include "GUIButton.h"
namespace GUI {
	//! Klasa GUI typu tickbox (pole znacznikowe)
/*!
	Umożliwia wybranie czy zadana opcja ma byc aktywna czy też nie.

*/
	class GUITickbox :
		public GUI::GUIButton
	{
	private:
		bool checked;
		sf::Color checkedFillColor;
	protected:
		//! Metoda reagująca na kliknięcie w pole znacznikowe.
		/*!
			Metoda ta dziedziczona jest z klasy GUI::GUIButton i wywoływana jest podczas odświeżania obiektu tej
			klasy jeśli dojdzie do kliknięcia na nim. Implementuje reakcję tej klasy na kliknięcie tj. zmiana stanu
			pola znacznikowego, zmiana zaznaczenia.
			\return  void
		*/
		virtual void derivedClassReaction();
	public:
		//! Konstruktor
		/*!
			Inicjuje niezbędne pola na podstawie przekazanych argumentów.
				\param position Pozycja względem rodzica.
				\param buttonSize Rozmiar pola znacznikowego.
				\param font Wskaźnik do czcionki.
				
				\param parent Wskaźnik na rodzica obiektu w hierarchi GUI.
				\param cb  Funkcja zewnętrznego obiektu wywoływana w momencie kliknięcia na pole tekstowe.

		*/
		GUITickbox(sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f buttonSize = sf::Vector2f(50, 20),
			sf::Font* font = nullptr, GUIElement* parent = nullptr, EventCallback cb = nullptr);
		//! Destruktor
		virtual ~GUITickbox();
		//! Metoda zwraca informację o tym czy pole jest zaznaczone.
		/*!
			\return bool Zwraca prawdę jeśli stan elementu jest ustawiony na "prawda".

		*/
		bool getChecked() { return checked; }
		//! Metoda zmienia stan wyboru.
		/*!
			\param c Stan zaznaczenia, prawda - opcja wybrana, fałsz - opcja nieaktywna.
			\return void
		*/
		void setChecked(bool c);
		//! Metoda zmienia kolor elementu graficznego po wybraniu.
		/*!
			\param color Kolor elementu po zmianie jego stanu na "prawda".
			\return void
		*/
		void setCheckedFillColor(sf::Color color);
	
		//! Odświeża stan obiektu.
		/*!
			\param e Zdarzenie
			\param window Okno główne aplikacji
			\return void
		*/
		void update(sf::Event& e, sf::RenderWindow& window);
	};

}