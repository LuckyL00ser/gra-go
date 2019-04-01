#pragma once
#include "GUIElement.h"
#include "SFML\Graphics\Text.hpp"
#include "SFML\Graphics\RectangleShape.hpp"
namespace GUI {
	//! Klasa reprezentuje elementy GUI typu pole tekstowe.
	/*!
		Umożliwia wpisywanie danych z klawiatury oraz odczyt tekstu przez zewnętrzne obiekty.

	*/
	class GUITextField :
		public GUIElement
	{
	private:
		sf::Text text;
		sf::RectangleShape borders;
		const sf::Color hasFocus = sf::Color(200, 50, 50,100);
		const sf::Color noFocus = sf::Color::White;
	protected:
		//! Metoda reagująca na zmianę rozmiaru pola tekstowego.
		/*!
			Metoda ta dziedziczona jest z klasy GUI::GUIElement i wywoływana jest przez metodę setSize tejże klasy.
			Implementuje zachowanie się pola tekstowego po zmianie rozmiaru.
			\return  void
		*/
		virtual void setSizeDerivered();
		//! Metoda pozycjonuje tekst w polu tekstowym.
		/*!
			W przypadku zmiany rozmiaru pola tekstowego bądź wpisaniu do niego tekstu, pojawia się konieczność
			wyliczenia nowych koordynatów dla obiektu graficznego reprezentującego tekst. Metoda ta
			pozycjonuje tekst w taki sposób aby zawsze justował się do lewej krawędzi pola tekstowego
			oraz pozostawał na środku jego wysokości.
			\return  void
		*/
		void formatText();
		bool focus; /**<Pole przechowuje informację o tym czy pole tekstowe posiada fokus - czy możliwe jest wpisywanie danych*/

	public:
		//! Konstruktor
	/*!
		Inicjuje niezbędne pola na podstawie przekazanych argumentów. 
			\param position Pozycja względem rodzica.
			\param buttonSize Rozmiar pola tekstowego.
			\param font Wskaźnik do czcionki.
			\param text Tekst pola tekstowego.
			\param parent Wskaźnik na rodzica obiektu w hierarchi GUI.
		
	*/
		GUITextField(sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f buttonSize = sf::Vector2f(50, 20),
			sf::Font* font = nullptr, std::string text = " ", GUIElement* parent = nullptr);
		//! Destruktor
		virtual ~GUITextField();

		//! Renderuje pole tekstowe.
		/*!
			\param target Obiekt na rzecz którego element jest renderowany.
			\param states Parametry renderowania.
			\return void
		*/
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
		//! Odświeża stan obiektu.
		/*!
			Sprawdza czy obiekt posiada fokus tzn. czy użytkownik kliknął na niego w celu wpisania tekstu. Jeśli tak
			zbiera informację o wciśniętych klawiszach i wpisuje je w pole tekstowe.
			\param e Zdarzenie
			\param window Okno główne aplikacji
			\return void
		*/
		virtual void update(sf::Event& e, sf::RenderWindow& window);

		//! Metoda zmienia tekst wyświetlany w polu tekstowym.
		/*!
			
			\param text Tekst do wyświetlania.
			\return void
		*/
		void setText(const std::string& text);
		//! Metoda zmienia rozmiar tekstu etykiety.
		/*!

			\param size Nowy rozmiar tekstu.
			\return void
		*/
		void setTextSize(unsigned size);
		//! Metoda zmienia czcionkę etykiety.
		/*!

			\param newFont Nowa czcionka tekstu.
			\return void
		*/
		void setFont(const sf::Font& newFont);
		
		//! Metoda zwraca tekst wpisany w polu tekstowym.
		/*!
		\return std::string Wpisany tekst.
		*/
		std::string getText() const;
	};


}
