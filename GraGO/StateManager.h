#pragma once

#include <stack>
#include <memory>
#include "BaseState.h"
#include "Callback.h"
using namespace std;
//! Klasa reprezentująca menadżer stanów gry.
/*!
	Klasa ta zarządza wszystkimi stanami gry. Implementuje stos unikalnych wskaźników na
	poszczególne stany gry które są na niego odkładane. Aktualny stan gry znajduje się na szcycie stosu
	i tylko on jest odświeżany oraz renderowany. Pozostałe "poniższe" stany są zamrożone i czekają na swoją kolej.
	Menedżer stanów umożliwia dodawanie oraz usuwanie stanów gry ze stostu. Każdy stan gry musi dziedziczyć
	z abstrakcyjnej klasy BaseState i to na jej metodach operuje menedżer stanów. Jeśli stos okaże się pusty, metoda
	wywołuje callback informujący głowną klasę aplikacji o zakończeniu wykonywania się programu i konieczności jego 
	zamknięcia.
*/
class StateManager : public Callback
{

public:
	//! Konstruktor
	/*!
		Ustawia callback informujący obiekt klasy Application o konieczności zakończenia programu.
	*/
	StateManager(EventCallback exitApplicationCallback) { setCallback(exitApplicationCallback); }
	//! Destruktor
	/*!
		Jeśli przy wywołaniu destruktora stos jest niepusty, to zdejmuje on z niego i niszczy wszystkie 
		zalegające stany gry.
	*/
	~StateManager();
		
	//! Metoda odkłada nowy stan gry na szczyt stosu.
	/*!
		\return void
	*/
	void pushState(unique_ptr<BaseState> state);
	//! Metoda zdejmuje aktualny stan gry ze szczytu stosu.
	/*!
		Aktualny stan gry zostaje zdjęty ze stosu, zniszczony i zostaje zwolniona pamięć po nim.
		\return void
	*/
	void popState();
	//! Metoda podmienia aktualny stan gry.
	/*!
		Aktualny stan gry zostaje zdjęty ze stosu i zastąpiony nowym przekazanym w agrumencie.
		\return void
	*/
	void changeState(unique_ptr<BaseState> state);
	//! Metoda wywołuje callback wyjścia z aplikacji.
	/*!
		Metoda wywoływana jest przy konieczności zakończenia aplikacji, np. gdy na stosie nie ma już więcej stanów gry
		(stos pusty). Wywołuje ona funkcję callback() która ustawiona na odpowiednią metodę klasy Application
		informuję tamtą klasę o konieczności zamknięcia aplikacji.
		\return void
	*/
	void exitApplication() { callback(); }
	//! Metoda odpowiadająca za odświeżanie aktualnego stanu gry.
	/*!
		Odświeża aktualny stan gry (ze szczytu stostu). Stany gry przeznaczone do usunięcia (znajdujące się na osobnym stosie) zwalnia
		i usuwa.
		\param e Referencja do zdarzenia jakie wystapiło.
		\param window Referencja do okna aplikacji w którym należy wyrysować obiekt.
		\return void
	*/
	void update(sf::Event& e, sf::RenderWindow& window);
	//! Renderuja aktualny stan gry
	/*!
		\return void
	*/
	void draw();
	//! Metoda dodaje aktualny stan gry do usunięcia.
	/*!
		Stan gry ze szczytu stosu odkładany jest na osobny stos który przy następnej aktualizacji zwalnia ten stan gry. Umożlwia to
		aktualnemu stanowi dokończenie odświeżania i zapobiega generowaniu błędów związanych z odświeżaniem elementów po których zwolniono
		już pamięć. Np. wciskając przycisk, reakcją na to zdarzenie byłoby natychmiastowe usunięcie stanu gry, podczas gdy funckja odświeżania
		tego stanu nie byłaby zakończona i chciałaby dokończyć operację aktualizacji dla elementów wobec których zwolniono już pamięć.
		\return void
	*/
	void addTopToDelete();
	//! Metoda zwraca wskaźnik do aktualnego stanu gry.
	/*!
		Metoda zwraca wskaźnik do aktualnego stanu gry (stanu ze szczytu stosu stanów gry).
		\return BaseState*
	*/
	BaseState* getCurrentState() const { return states.top().get(); }

private:
	stack<unique_ptr<BaseState>> states;
	stack<unique_ptr<BaseState>> toLateDelete;

};

