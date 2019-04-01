#pragma once
#include "GUIElement.h"
#include <vector>

#include "Utilities.h"
using namespace std;
namespace GUI {
	//! Klasa umożlwia grupowanie obiektów przestrzeni nazw GUI.
	/*!
		Klasa stworzona dla wygodnej manipulacji. Może być rodzicem wielu elementów graficznych dziedziczących z GUI::GUIElement.
		Zarządza renderowaniem i odświeżaniem stanu swoich "dzieci". Umożliwia wygodną maniupulację jedynie swoim rozmiarem,
		odpowiednio dostosowując agregowane obiekty.
		
	*/
	class GUIGroup : public GUIElement
	{
	private:
		vector<GUIElement*> children;
	protected:
		//! Metoda reagująca na zmianę rozmiaru grupy obiektów GUI::GUIGroup.
		/*!
			Metoda ta dziedziczona jest z klasy GUI::GUIElement i wywoływana jest przez metodę setSize tejże klasy.
			Implementuje zachowanie się grupy elementów GUI po zmianie rozmiarów rodzica (obiektu opisywanej klasy).
			\return  void
		*/
		void setSizeDerivered();
	public:
		//! Konstruktor
	/*!
		Inicjuje podstawowe parametry klasy.

	*/
		GUIGroup(sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f size = sf::Vector2f(100, 100),
			GUIElement* parent=nullptr);
		//! Destruktor
	/*!
		Niszczy przypisane obiekty dzieci.

	*/
		virtual ~GUIGroup();
		//! Metoda przypisuje obiekt jak rodzica tej klasy.
		/*!
			Przekazany obiekt klasy GUIElement staje się "dzieckiem" tej klasy. Zarządza ona jego wyświetlaniem, odświeżaniem
			oraz zwalnianiem pamięci tego obiektu. Pozostałe argumenty w % pozwalają określić i dostosować rozmiar nowego dziecka
			do obiektu rodzica.
			\param newChild Referencja do obiektu-dziecka.
			\param xInPercent Wyrażony w % lewy margnies obiektu-dziecka od lewej krawędzi obiektu rodzica.
			\param yInPercent Wyrażony w % górny margnies obiektu-dziecka od górnej krawędzi obiektu rodzica.
			\param widthInPercent Wyrażona w % szerokość obiektu-dziecka względem szerokości obiektu rodzica.
			\param heightInPercent Wyrażona w % wysokość obiektu-dziecka względem wysokości obiektu rodzica.
			\return void

		*/
		void attachChildren(GUIElement& newChild,float xInPercent, float yInPercent, float widthInPercent, float heightInPercent);
		//! Metoda przypisuje obiekt jak rodzica tej klasy.
		/*!
			Przekazany obiekt klasy GUIElement staje się "dzieckiem" tej klasy. Zarządza ona jego wyświetlaniem, odświeżaniem
			oraz zwalnianiem pamięci tego obiektu. Pozostałe argumenty w % pozwalają określić i dostosować rozmiar nowego dziecka
			do obiektu rodzica.
			\param newChild Referencja do obiektu-dziecka.
			\return void

		*/
		void attachChildren(GUIElement& newChild);
		//! Metoda zwalnia istniejący obiekt dziecko z grupy GUI.
		/*!
			Jeśli przekazany obiekt GUIElement jest dzieckiem obiektu tej klasy to następuje jego zwolnienie - odłączenie
			z GUIGroup któro przestaje zarządzać obiektem-dziecko.
			\param child Referencja do zwalnianego obiektu-dziecka.
		
			\return void

		*/
		void detachChildren(GUIElement& child);
		//! Metoda przesuwa obiekt-dziecko na szczyt hierarchi odświeżania/renderowania.
		/*!
			Obiekty podrzędne odświeżane są w kolejności odwrotnej do kolejności dodawania tj. ostani dołączony obiekt
			jest renderowany/odświeżany jako ostatni. Metoda ta przesuwa wybrany obiekt-dziecko na szczyt tej hierarchi.
			\param child Referencja do przesuwanego obiektu-dziecka.

			\return void

		*/
		void moveChildrenOnTop(GUIElement& child);
		//! Renderuje grupę obiektów.
			/*!
				
				\param target Obiekt na rzecz którego element jest renderowany.
				\param states Parametry renderowania.
				\return void
			*/
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		//! Odświeża stan grupy obiektów.
		/*!
			\param e Zdarzenie
			\param window Okno główne aplikacji
			\return void
		*/
		virtual void update(sf::Event& e, sf::RenderWindow& window);
		
		

	};
}
