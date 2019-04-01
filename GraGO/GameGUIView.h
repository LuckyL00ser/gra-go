#pragma once
#include "GUIGroup.h"
#include "Game.h"
#include "GUIButton.h"
#include "GUILabel.h"
#include "GUILine.h"
#include "Utilities.h"
#include "GUIImage.h"
class GameStateNetwork;
//! Klasa reprezentująca widok gry.
	/*!
		Zarządza wizualną stroną samej rozgrywki. Renderuje planszę, piony, opisy graczy, ilości zdobytych punktów, przycisk powrotu.
		Komunikuje się z klasą Game wydając jej polecenia takie jak np. spasowanie gracza, ustawienie pionu na danej pozycji zależnie od 
		wciśniętego przycisku GUIButton. Dziedziczy z GUIGroup by łatwiej zarządzać renderowanymi elementami.
		
	*/
class GameGUIView :
	public GUI::GUIGroup
{
protected:
	//! Metoda reagująca na zmianę rozmiaru wizualnego obiektu.
	/*!
		Implementacja czysto wirtualnej metody z klasy GUIGroup. Realizuje zachowanie się obiektu i potomnych elementów graficznych
		po zmianie jego wymiarów.
		\return  void
	*/
	void setSizeDerivered();
private:
	Game* game;
	const Utilities& utilities;
	
	GUI::GUIButton ***interactiveElements; //wskaznik do dwuwymiarowej tablicy elementow widocznych na planszy: przycisk lub obraz kamienia GO
	//elementy graficzne GUI i zasoby:
	sf::Texture* blackStoneTexture;
	sf::Texture* whiteStoneTexture;

	GUI::GUILabel *whitePoints;
	GUI::GUILabel *blackPoints;
	GUI::GUILabel *gameStateInfo;
	GUI::GUIButton* lastPutStone;
	GUI::GUIImage* whosTurn;

	GUI::GUIButton* exit;

	void createBoardGUI();

	void takeOutStone(unsigned x, unsigned y);
	
public:
	//! Konstruktor
	/*!
		Ustawia odpowiednie wartości pól przekazane jako parametry konstruktora. Obiekty klas Utilities oraz Game są niezbędne dla tej klasy, pozostałe
		parametry mogą być domyślne. Konstruktor tworzy graficzną interpretację planszy - każde pole to przycisk GUIButton, mapuje je z odpowiednimi
		koordynatami planszy w pamięci. Tworzy całe wizualne GUI wywołując metodę createBoardGUI().
		
	*/
	GameGUIView(const Utilities& context, const Game& game, sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f size = sf::Vector2f(100, 100),
				 GUIElement* parent = nullptr);
	//! Destruktor
	/*!
		Nie musi niczego zwalniać, elementy wizualne niszczone są przez destruktor klasy bazowej GUIGroup.
	*/
	~GameGUIView();
	
	//! Ustawia teksturę dla białych pionów.
	/*!
		\param tex Wskaźnik do nowej tekstury.
		\return  void
	*/
	void setWhiteStoneTexture(sf::Texture* tex);
	//! Ustawia teksturę dla czarnych pionów.
	/*!
		\param tex Wskaźnik do nowej tekstury.
		\return void
	*/
	void setBlackStoneTexture(sf::Texture* tex);
	//! Metoda próbuje postawić pion na planszy, wykonać ruch.
	/*!
		Metoda opiera się o wywołanie funkcji putStone() z klasy Game. Tym samym weryfikuje poprawność ruchu. Jesli jest on zgodny
		z regułami gry pion zostaje ustawiony czym zajmuje się wyżej wspomniana klasa, zaś metoda tej klasy dokonuje graficznej akualizacji
		widoku analzując zmiany na planszy. Następnie aktualizuje elementy wyświetlające kolejnośc ruchu, punkty itp. zwraca prawdę.
		Fałsz natomiast zwraca gdy ruch jest niepoprawny.
		\param x Kolumna na której stawiany jest pion.
		\param y Wiersz na którym stawiany jest pion.
		\return  bool Zwracaj prawdę jeśli wykonanie ruchu powiodło się. Fałsz w innym wypadku.
	*/
	bool putStone(unsigned x, unsigned y); 
	//! Metoda odpowiadajaca za spasowanie któregoś z graczy.
	/*!
	Wywołanie tej metody informuję obiekt klasy Game, że obecnie wykonujący ruch gracz spasował i nastepuje zmiana kolejki.
		\param who Pasujący gracz.
		\return  void
	*/
	void pass(Moves who);
	//! Blokuje wszystkie przyciski pól planszy.
	/*!
		Blokuje przyciski na czas gdy ruch wykonuje przeciwny gracz. Metoda wykorzystywana jest jedynie w rozgrywce sieciowej.
		\return  void
	*/
	void lockAllButtons();
	//! Odblokowuje wszystkie przyciski pól planszy.
	/*!
		Odblokowuje przyciski na czas gdy następuje kolejka "naszego" gracza. Metoda wykorzystywana jest tylko w rozgrywce sieciowej.
		\return  void
	*/
	void unlockAllButtons();
	//! Odświeża opisy, ilości punktów, wskaźnik ruchu gracza.
	/*!
		
		\return  void
	*/
	void refreshLabelsInfo();
	//! Zmienia tekst wyświetlany na głownej belce.
	/*!
		Zmienia wyświetlaną informację.
		\param content Tekst do wyświetlenia.
		\return  void
	*/
	void setMainLabelContent(sf::String content);
	//! Renderuje stan gry.
	/*!
		Renderuje stan gry, planszę i towarzyszące mu obiekty np. GUI.
		\param target Obiekt na rzecz którego element jest renderowany.
		\param states Parametry renderowania.
		\return void
	*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//! Odświeża stan obiektu
	/*!
		Odświezą stan gry i elementy potomne np. GUI.
		\param e Zdarzenie
		\param window Okno głowne aplikacji
		\return void
	*/
	void update(sf::Event& e, sf::RenderWindow& window);
	friend class GameState; /**<Deklaracja przyjaźni z klasą GameState (która agreguje GameGUIView)*/
	friend class GameStateNetwork;  /**<Deklaracja przyjaźni z klasą GameStateNetwork (która agreguje GameGUIView)*/
};

