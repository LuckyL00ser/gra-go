#pragma once
#include "GameState.h"
#include <thread>
#include "AlertState.h"
#include "NetworkThread.h"
#include "GUIImage.h"

#include "GameStateNetwork.h"
//! Klasa stanu gry odpowiadająca za utworzenie połączenia sieciowego
	/*!
		Klasa umożliwia podjęcie próby stworzenia serwera gry lub podłączenia się do już
		istniejącej w sieci gry. Impelementuje mechanizm wątków do obsługi blokujących gniazd sieciowych.
	*/
class ConnectingState :
	public BaseState
{
private:
	GUI::GUIImage * img; /**<Wskaźnik do obrazka oczekiwania.*/
	GUI::GUIButton * abortButton;  /**<Wskaźnik do przycisku przerwania operacji łączenia/nasłuchiwania.*/
	GUI::GUILabel * label; /**<Wskaźnik do etykiety wyświetlającej komunikat.*/
	ConnectionState currentState; /**< Zmienna opisująca obecny stan połączenia.*/

	NetworkThread* networkConnection; /**< Wskaźnik do klasy realizującej połączenia sieciowe.*/
	//! Podejmuje próbę połączenia się/utworzenia serwera.
	/*!
	Dowiązuje callback reakcji na odbiór danych. Inicjalizuje połączenie. Gdy operacja się niepowiedzie zmienia stan połączenia
	na rozłączony.
		\return void
	*/
	void tryConnect(void); 
	std::thread* network; /**<Wskaźnik do obiektu reprezentującego nowy wątek - wątek dla blokujących operacji sieciowych.*/
	FieldColor myColor; /**<Kolor pionow gracza lokalnego*/

	bool colorSet; /**<Zmienna określa czy kolor graczy został określony..*/
	bool gameSizeSet; /**<Zmienna określa czy rozmiar planszy został określony.*/
	bool komiSet; /**<Zmienna określa czy reguła komi została określona.*/

public:
	//! Konstruktor
	/*!
		Implementuje niezbędne elementy klasy bazowej BaseState.
		Ostatni argument określa czy utworzony zsotanie serwer czy tez zostanie podjęta próba połączenia się z już istniejącym.
		Tworzy interfejs graficzny stanu gry. Podejmuje próbę połączenia.
	*/
	ConnectingState(StateManager* state, const Utilities& utilities, bool server);
	//! Destruktor
	/*!
		Zwalnia zasoby. Jeśli użytkownik przerwie proces łączenia samodzielnie
		, metoda przerywa wątek sieciowy i niszczy obiekt.
	*/
	~ConnectingState();
	//! Odświeża stan obiektu
	/*!
		Implementacja czysto wirtualnej metody z klasy bazowej BaseState. Odświezą stan gry i elementy potomne np. GUI. Zarządza przełączaniem
		się między poszczególnymi stanami połączenia.
		\param e Zdarzenie
		\param window Okno głowne aplikacji
		\return void
	*/
	void update(sf::Event& e, sf::RenderWindow& window);
	//! Renderuje stan gry.
	/*!
		Implementacja czysto wirtualnej metodyz klasy bazowej BaseState. Renderuje stan gry i towarzyszące mu obiektu np. GUI.
		\return void
	*/
	void draw() const;
	//! Rozłącza połączenie.
	/*!
		\return void
	*/
	void disconnected();
	//! Metoda reagująca na odebranie danych (callback).
	/*!
		Odbiera dane niezbędne do inicjalizacji gry internetowej tzn. ustawień takich jak rozmiar planszy, kolor graczy, obecność reguly komi.
		Niezbędna jest synchronizacja tych parametrów pomiędzy graczami w sieci. 
		\return void
	*/
	void dataReceived();

};

