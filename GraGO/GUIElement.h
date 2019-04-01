#pragma once
#include "SFML\Graphics\Drawable.hpp"
#include "SFML\Graphics\Transformable.hpp"

#include "SFML\Graphics\RenderStates.hpp"
#include "SFML\Graphics\RenderTarget.hpp"
#include "SFML\Window\Event.hpp"
#include "SFML\Graphics\RenderWindow.hpp"

namespace GUI {
	//! Abstrakcyjna klasa bazowa wszystkich graficznych elementów GUI
		/*!
			Dostarcza wszystkim klasom pochodnym podstawowej możliwości manipulacji obiektami graficznymi.
			Posiada czysto wirtualne funkcje draw i update, by każdy element interfejsu mógł samodzielnie
			odświeżać i renderować siebie wedle indywidualnych potrzeb. Umożliwia wizualne "ukrycie" obiektu
			oraz maniuplację jego położeniem/punktem transformacji (dziedziczone z sf::Transformable).
			Wymusza w klasach potomnych implementację metody setSizeDerivered() odpowiadającej za reakcję
			indywidualną reakcję klasy na zewnętrzną, wymuszoną zmianę rozmiaru elementu graficznego.
			
		*/
	class GUIElement : public sf::Drawable, public sf::Transformable
	{
	private:
		bool visible;
		sf::Vector2f size;
		GUIElement *parent;
		
	protected:
		//! Funkcja reagująca na zmianę rozmiaru obiektu.
		/*!
			Czysto wirtualna funkcja do implementacji w klasach bazowych. Wywoływana jest przez publiczną metodę setSize().
			Każdy potomek może indywidualnie reagować na potrzebę zmiany rozmiaru.

		*/
		virtual void setSizeDerivered() = 0; //wymusza implementacje reakcji na zmiane rozmiaru w klasie pochodnej
	public:
		//! Konstruktor
		/*!
			Posiada parametry domyślne pozwalające na modyfikację podstawowych parametrów obiektu interfejsu graficznego.
			\param position Pozycja elementu względem rodzica.
			\param parent Wskaźnik na rodzica (element nadrzędny hierarchi GUI).
			\param visi Określa czy element ma być widoczny (renderowany).


		*/
		GUIElement(sf::Vector2f position=sf::Vector2f(0,0), GUIElement* parent=nullptr, bool visi=true) :
			visible(visi) {
			setPosition(position); 
			setParent(parent);
			
		}
		//! Writualny destruktor
	
		virtual ~GUIElement() {}
		//! Metoda zwraca informację o tym czy obiekt jest widoczny.
		/*!
			\return bool Prawda jeśli obiekt jest widoczny.
		*/
		bool isVisible()const;
		//! Metoda zmienia stan obiektu na widoczny.
		/*!
			\return void
		*/
		void show();
		//! Metoda zmienia stan obiektu na ukryty.
		/*!
			\return void
		*/
		void hide();
		//! Metoda zwraca wskaźnik do rodzica w hierarchi GUI.
		/*!
			\return GUIElement* Wskaźnik na rodzica.
		*/
		GUIElement* getParent() { return parent; }
		//! Metoda pozwala zmienić rodzica w hierarchi GUI.
		/*!
			\param newParent Nowy rodzic.
			\return void
		*/
		void setParent(GUIElement* newParent) { parent = newParent; }
		//! Metoda pozwala zmienić rozmiar obiektu.
		/*!
			\param s Nowy rozmiar.
			\return void
		*/
		void setSize(sf::Vector2f s) {size = s; setSizeDerivered();	}
		//! Metoda pozwala zmienić rozmiar obiektu.
		/*!
			\param width Nowa szerokość obiektu.
			\param height Nowa wysokość obiektu.
			\return void
		*/
		void setSize(float width, float height) { size.x = width; size.y = height; setSizeDerivered();	}
		//! Metoda pozwala zmienić rozmiar obiektu.
		/*!
			\param s Nowy rozmiar obiektu.
			\return void
		*/
		void setSize(sf::Vector2u s) { size.x = s.x; size.y = s.y; setSizeDerivered(); }

		//! Czysto wirtualna metoda odpowiadająca za renderowanie obiektu.
		/*!
			Do implementacji w klasach pochodnych.
			\param target Obiekt na rzecz którego renderowany jest element (np. okno gry).
			\param states Parametry renderowania.
			\return void
		*/
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0; //przeslanianie metody z sf::Drawable
		//! Czysto wirtualna metoda odpowiadająca za odświeżanie obiektu.
		/*!
			Do implementacji w klasach pochodnych.
			\param e Zdarzenie.
			\param window Okno głowne gry.
			\return void
		*/
		virtual void update(sf::Event& e, sf::RenderWindow& window) = 0;
		//! Zwraca rozmiar elementu GUI.
		/*!
			Metoda wirtualna.
			\return sf::Vector2f Rozmiar elementu.
		*/
		virtual sf::Vector2f getSize()const { return size; }
		//! Zwraca bezwzględne położenie obiektu.
		/*!
			Zwraca położenie obiektu względem okna gry a nie rodzica.
			\return sf::Vector2f Położenie obiektu.
		*/
		sf::Vector2f getPositionRealitve();
		

	};
}

