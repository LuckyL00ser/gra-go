#pragma once
#include "GUIElement.h"
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Texture.hpp>
namespace GUI {
	//! Klasa zarządza wyświetlaniem tekstur dla interfejsu graficznego GUI.

	class GUIImage :
		public GUIElement
	{
	protected:
		//! Metoda reagująca na zmianę rozmiaru.
		/*!
			Metoda ta dziedziczona jest z klasy GUI::GUIElement i wywoływana jest przez metodę setSize tejże klasy.
			Implementuje zachowanie się obiektu GUI::GUIImage po zmianie rozmiaru.
			\return  void
		*/
		void setSizeDerivered();
		sf::RectangleShape graphics; /**<Obiekt reprezentujący wyświetlaną grafikę - obrazek*/

	public:
		//! Konstruktor
		GUIImage();
		//! Destruktor
	/*!
		Przypisuje do tworzonego obiektu podaną w argumencie teksturę. Zmienia rozmiar obiektu na rozmiar zgodny z wielkością
		przekazanej tekstury.
		\param tex Tekstura obrazka.

	*/
		GUIImage(const sf::Texture& tex);
		//! Destruktor.
		virtual ~GUIImage();
		//! Zmienia kolor tekstury.
	/*!
		
		\param color Nowy kolor tekstury.
		\return void
	*/
		void setColor(sf::Color color) { graphics.setFillColor(color); }
		//! Renderuje teksture.
		/*!
			\param target Obiekt na rzecz którego element jest renderowany.
			\param states Parametry renderowania.
			\return void
		*/
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		//! Odświeża stan obiektu.
		/*!
			Dla obrazka nie ma zastosowania. Wymaga jednak implementacji dziedzicząc z GUIElement.
			\param e Zdarzenie
			\param window Okno główne aplikacji
			\return void
		*/
		 void update(sf::Event& e, sf::RenderWindow& window) {};
	
	};
}
