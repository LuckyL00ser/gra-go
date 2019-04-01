#pragma once
#include "GUIElement.h"
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <string>
namespace GUI {
	//! Klasa reprezentująca napis z tłem i obramowaniem.
	/*!
		Klasa odpowiadająca za graficzną reprezentację etykiet tekstowych. Umożlwia wiele sposobó ich dostosowywania. Zmiana koloru tekstu,
		czcionki, koloru tła itp.
	*/
	class GUILabel :
		public GUIElement
	{
	protected:
		//! Metoda reagująca na zmianę rozmiaru elementu graficznego.
		/*!
			Metoda ta dziedziczona jest z klasy GUI::GUIElement i wywoływana jest przez metodę setSize tejże klasy.
			Implementuje zachowanie się obiektu klasy GUI::GUILabel po zmianie rozmiaru.
			\return  void
		*/
		void setSizeDerivered();
	private:
		sf::Text text;
		sf::RectangleShape label;
		
		void centerText();
		void setCustomLabelProperties();
	public:
		//! Konstruktor
		/*!
			Inicjuje niezbędne pola na podstawie przekazanych argumentów. Ustawia domyślne parametry etykiety.
			\param position Pozycja względem rodzica.
			\param size Rozmiar etykiety.
			\param font Wskaźnik do czcionki.
			\param text Tekst etykiety.

			
		*/
		GUILabel(sf::Vector2f position=sf::Vector2f(0,0),sf::Vector2f size=sf::Vector2f(100,100),sf::Font* font=nullptr,std::string text="");
		//! Destruktor
		virtual ~GUILabel();
		
		//! Metoda zmienia tekst etykiety.
		/*!
			
			\param text Tekst etykiety.
			\return void

		*/
		void setText(const std::string& text);
		//! Metoda zmienia kolor tekstu.
		/*!
			
			\param color Nowy kolor.
			\return void
		*/
		void setTextColor(sf::Color color) { text.setFillColor(color); }
		//! Metoda zmienia rozmiar tekstu.
		/*!

			\param size Nowy rozmiar.
			\return void

		*/
		void setTextSize(unsigned size);
		//! Metoda zmienia czcionkę dla tekstu.
		/*!

			\param newFont Referencja do nowej czcionki dla etykiety.
			\return void

		*/
		void setFont(const sf::Font& newFont);
		//! Metoda zmienia kolor tła etykiety.
		/*!

			\param color Nowy kolor tła
			\return void

		*/
		void setBackgroundColor(sf::Color color) { label.setFillColor(color); }
		//! Metoda zmienia kolor obramowania etykiety.
		/*!

			\param color Nowy kolor obramowania
			\return void

		*/
		void setBorderColor(sf::Color color) { label.setOutlineColor(color); }
		//! Metoda zmienia obrazek tła etykiety.
		/*!

			\param background Nowa tekstura tła.
			\return void

		*/
		void setBackgroundImage(const sf::Texture& background) { label.setTexture(&background); }
		//! Metoda zmienia rozmiar obramowania etykiety.
		/*!

			\param thickness Nowa grubość obramowania.
			\return void

		*/
		void setBorderThickness(float thickness) { label.setOutlineThickness(thickness); }
		
		//! Renderuje napis.
		/*!
			\param target Obiekt na rzecz którego element jest renderowany.
			\param states Parametry renderowania.
			\return void
		*/
		void draw(sf::RenderTarget& target, sf::RenderStates states)const;
		//! Odświeża stan obiektu.
		/*!
			Dla napisu nie ma zastosowania. Wymaga jednak implementacji dziedzicząc z GUIElement.
			\param e Zdarzenie
			\param window Okno główne aplikacji
			\return void
		*/
		 void update(sf::Event& e, sf::RenderWindow& window) {};
		
	};
}

