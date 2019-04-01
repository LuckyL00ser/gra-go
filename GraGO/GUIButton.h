#pragma once
#include "GUIElement.h"
#include <SFML\System\String.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include "Callback.h"
namespace GUI {
	enum class ButtonState {
		NORMAL,
		HOVER,
		CLICKED
	};
	//! Klasa reprezentująca przycisk.
	/*!
		Klasa odpowiadająca za graficzną i logiczną część przycisku. Wyświetla go pozwajaląc na szeroki wachlarz wizualnych zmian:
		czcionka, kolor, obrazek tła, obramowanie. Wykrywa kliknięcie oraz najechanie. Jest głównym beneficjentem mechanizmu callback,
		wywołuje ustawioną funkcję gdy przycisk zostaje wciśnięty. Może znajdować się w 3 stanach: normalny, najechany, wciśnięty.
	*/
	class GUIButton :public GUIElement,public Callback
	{
	private:
		bool active;
	protected:
		//! Metoda reaguje na zmianę rozmiaru obiektu graficznego.
		/*!
			Implementacja metody z klasy bazowej GUIElement, określa zachowanie obiektu w reakcji na zmianę
			jego rozmiaru przez inne obiekty.		
			\return void
		*/
		void setSizeDerivered();
		sf::RectangleShape borders; /**<Reprezentuje obiekt obramowania i wypełnienia przycisku*/
		sf::Color backgroundNormalColor; /**<Reprezentuje normalny kolor przycisku*/
		sf::Color textNormalColor; /**<Reprezentuje normalny kolor tekstu przycisku*/
		sf::Color textHoverColor;  /**<Reprezentuje kolor tekstu przycisku po najechaniu*/
		sf::Color textClickedColor; /**<Reprezentuje kolor tekstu przycisku po kliknięciu*/
		sf::Color backgroundHoverColor; /**<Reprezentuje kolor tła przycisku po najechaniu*/
		sf::Color backgroundClickedColor; /**<Reprezentuje kolor tła przycisku po kliknięciu*/
		//! Metoda dodatkowej reakcji na wciśnięcie przycisku.
		/*!
			Metoda jest pusta dla klasy GUIButton natomiast umożliwia klasom które ją dziedziczom własnę implementację
			w reakcji na kliknięcie w dany obiekt GUI.
			\return void
		*/
		virtual void derivedClassReaction();
	private:
		bool pressed;
		ButtonState state;
		sf::Text text;
		void centerText();
		void setCustomButtonProperties();

	public:
		//! Konstruktor
		/*!
			Inicjuje niezbędne pola na podstawie przekazanych argumentów. Ustawia domyślny styl przycisku.
			\param position Pozycja względem rodzica.
			\param buttonSize Rozmiar przycisku.
			\param font Wskaźnik do czcionki.
			\param text Tekst przycisku.
			\param parent Wskaźnik na rodzica obiektu w hierarchi GUI.
			\param cb Funkcja zewnętrznego obiektu wywoływana w momencie kliknięcia na przycisk.
		*/
		GUIButton(sf::Vector2f position = sf::Vector2f(0,0), sf::Vector2f buttonSize = sf::Vector2f(50, 20),
							sf::Font* font=nullptr, std::string text=" ",GUIElement* parent=nullptr,EventCallback cb=nullptr);
		//! Destruktor
		virtual ~GUIButton();
		//! Zwraca aktualny stan przycisku.
		/*!
			\return ButtonState Stan przycisku.
		*/
		ButtonState getState();
		/*! Metoda zmienia tekst przycisku.
			\param text Nowy tekst przycisku.
			\return void
		*/
		void setText(const std::string& text);

		/*! Metoda zmienia kolor tekstu przycisku w stanie normalnym. 
			\param color Nowy kolor
			\return void
		*/
		void setColorTextNormal(sf::Color color) { textNormalColor = color; }
		/*! Metoda zmienia kolor tła przycisku po najechaniu na niego.
			\param color Nowy kolor
			\return void
		*/
		void setColorTextHover(sf::Color color) { textHoverColor = color; }
		/*! Metoda zmienia kolor tekstu przycisku po kliknięciu.
			\param color  Nowy kolor
			\return void
		*/
		void setColorTextClicked(sf::Color color) { textClickedColor = color; }
		
		/*! Metoda zmienia kolor tła przycisku w stanie normalnym.
			\param color Nowy kolor
			\return void
		*/
		void setColorBackgroundNormal(sf::Color color) { backgroundNormalColor = color; }
		/*! Metoda zmienia kolor tekstu przycisku po najechaniu.
			\param color Nowy kolor
			\return void
		*/
		void setColorBackgroundHover(sf::Color color) { backgroundHoverColor = color; }
		/*! Metoda zmienia kolor tekstu przycisku po kliknięciu.
			\param color Nowy kolor
			\return void
		*/
		void setColorBackgroundClicked(sf::Color color) { backgroundClickedColor = color; }

		/*! Metoda zmienia kolor obramowania przycisku.
			\param color Nowy kolor
			\return void
		*/
		void setBorderColor(sf::Color color) {  borders.setOutlineColor(color); }
		/*! Metoda zmienia obrazek tła przycisku.
			\param background Nowa tekstura.
			\return void
		*/
		void setBackgroundImage(const sf::Texture& background);
		/*! Metoda zmienia rozmiar napisu przycisku.
			\param size Rozmiar czcionki.
			\return void
		*/
		void setTextSize(unsigned size);
		/*! Metoda zmienia grubość obramowania przycisku.
			\param thickness Grubość obramowania.
			\return void
		*/
		void setBorderThickness(float thickness) { borders.setOutlineThickness(thickness); }
		/*! Metoda zmienia czcionkę przycisku.
			\param newFont  Nowa czcionka
			\return void
		*/
		void setFont(const sf::Font& newFont);
		/*! Metoda zwraca informację o tym czy przycisk jest aktywny.
			Jeśli przycisk jest niekatywny metoda zwraca fałsz, inaczej zwraca prawdę. 
			\return bool Prawda jeśli przycisk jest aktywny.
		*/
		bool isActive() { return active; }
		/*! Metoda zmienia stan przycisku.
			Zmienia stan przycisku na aktywny/nieaktywny. Przycisk nieaktywny nie reaguje na kliknięcia i najechania myszką.
			\param newActive Nowy stan przycisku.
			\return void
		*/
		void setActive(bool newActive) { active = newActive;}
		//! Renderuje obiekt
		/*!
			Renderuje obiekt jeśli jest ustawiony jako widoczny.
			\param target Obiekt na rzecz którego element jest renderowany.
			\param states Parametry renderowania.
			\return void
		*/
		void draw(sf::RenderTarget& target, sf::RenderStates states)const;
		//! Odświeża stan obiektu.
		/*!
			Sprawdza stan w jakim znajduje się przycisk: normalny, najechany, wciśnięty i podejmuje
			adekwatne akcje do tego stanu.
			\param e Zdarzenie
			\param window Okno główne aplikacji
			\return void
		*/
		void update(sf::Event& e, sf::RenderWindow& window);
		
	};
}

