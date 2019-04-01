#pragma once
#include "GUIElement.h"
#include <SFML\Graphics\VertexArray.hpp>
namespace GUI {
	//! Klasa reprezentująca element GUI typu linia.
	/*!
		Klasa wykorzystywana jest przy tworzeniu planszy gry.
	*/
	class GUILine :
		public GUIElement
	{
	private:
		sf::VertexArray line{ sf::LinesStrip,2 };
	protected:
		//! Metoda reagująca na zmianę rozmiaru linii.
		/*!
			Metoda ta dziedziczona jest z klasy GUI::GUIElement i wywoływana jest przez metodę setSize tejże klasy.
			Implementuje zachowanie się obiektu klasy GUI::GUILine po zmianie rozmiaru.
			\return  void
		*/
		void setSizeDerivered();
	public:
		//! Konstruktor
	/*!
		Może ustawić linię na konkretnej pozycji. Domyślny kolor lini to czarny.
	*/
		GUILine(sf::Vector2f position = sf::Vector2f(0, 0));
		//!Destruktor
	/*!
		Zwalnia pamięć po obiekcie.
	*/
		~GUILine();
		//! Metoda ustawia pozycję początku linii.
	/*!
	\param position Pozycja początku linii.
		\return void
	*/
		void setStartVertexPosition(sf::Vector2f position) { line[0].position = position; }
		//! Metoda ustawia pozycję końca linii.
	/*!
	\param position Pozycja końca linii.
		\return void
	*/
		void setEndVertexPosition(sf::Vector2f position) { line[1].position = position; }
		//! Metoda ustawia kolor początku lini
	/*!
	\param color Kolor początku linii.
		\return void
	*/
		void setStartVertexColor(sf::Color color) { line[0].color = color; }
		//! Metoda ustawia kolor końca lini
	/*!
	\param color Kolor końca linii.
		\return void
	*/
		void setEndVertexColor(sf::Color color) { line[1].color = color; }
		//! Renderuje linię.
		/*!
			\param target Obiekt na rzecz którego element jest renderowany.
			\param states Parametry renderowania.
			\return void
		*/
		void draw(sf::RenderTarget& target, sf::RenderStates states)const;
		//! Odświeża stan obiektu.
		/*!
			Dla lini nie ma zastosowania. Wymaga jednak implementacji dziedzicząc z GUIElement.
			\param e Zdarzenie
			\param window Okno główne aplikacji
			\return void
		*/
		void update(sf::Event& e, sf::RenderWindow& window) {};
	};
}

