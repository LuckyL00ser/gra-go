#pragma once

#include "Moves.h"
#include "Board.h"
#include "Player.h"
#include "Callback.h"
//! Klasa reprezentująca obiekt gry.
	/*!
		Obiekt tej klasy jest podstawowym elementem tworzenia i zarządzania rozgrywką - pośredniczy w komunikacji
		pomiędzy graczem a grą.
	*/
class Game : public Callback
{
private:
	
	Moves whoMoves;
	Board board;
	bool passedOnce;	
	Player blackPlayer, whitePlayer;
	Player* winner;
	float komiValue;
	void changeGameState();
	void endGame();
	
public:
	//! Konstruktor
	/*!
		Inicjalizuje początkowe/domyśle wartości gry takie jako, kto pierwszy wykonuje ruch, rozmiar planszy czy zastosowanie reguły komi.
	*/
	Game(BoardSize size, float komiValue);
	//! Destruktor
	~Game();
	//! Zwraca rozmiar planszy.
	/*!
		\return BoardSize Rozmiar planszy.
	*/
	BoardSize getBoardSize() const;
	//! Zwraca kolor gracza aktualnie wykonującego ruch.
	/*!
		\return Moves Kolor gracza wykonującego ruch.
	*/
	Moves getWhoMoves() const;
	//! Gracz spasował.
	/*!
		Funkcja wywoływana jest przez zewnętrzny obiekt. Mówi grze że aktualnie wykonujący ruch gracz spasował i kolejka przechodzi
		na jego oponenta. Jeśli dwóch graczy spasuje naraz pod rząd gra kończy się.
		\return void
	*/
	void pass();
	//! Metoda odpowiadająca za ustawienie pionu na planszy.
	/*!
		Metoda stawiając pion na planszy sprawdza czy ruch zgodny jest z regułami gry (funkcja tryPutStone() z klasy Board), jeśli tak,
		pion zostaje ustawiony, zaaplikowane zostają opowiednie reguły i w razie potrzeby dochodzi do przejęcie pionów przeciwnika,	kolejka zmienia się na przeciwnego gracza, funkcja zwraca prawdę.
		Jeśli ruch nie jest poprawny funkcja zwraca fałsz.
		\param x Kolumna na planszy na której znajduje się pole na które gracz stawia pion.
		\param y Wiersz na planszy na którym znajduje się pole na które gracz stawia pion.
		\return bool Prawda jeśli wykonanie ruchu powiodło się.
	*/
	bool putStone(unsigned x, unsigned y);
	//! Metoda zwraca prawdę jeśli jeden z graczy spasował w swojej ostatniej turze.
	/*!
		\return bool Prawda jeśli w poprzedniej kolejce następił pas.
	*/
	bool passed()const;
	//! Zwraca pole planszy na pozycji x,y
	/*!
		\param x Kolumna na planszy na której znajduje się pole.
		\param y Wiersz na planszy na którym znajduje się pole.
		\return  const Field& Referencja do pola planszy.
	*/
	const Field& getAt(unsigned int x, unsigned int y);
	//! Zwraca pola z których w ostatnim ruchu usunięto ustawione uprzednio piony.
	/*!
		Zwraca wskaźnik do wektora par liczb typu unsigned oznaczających koordynaty pól.
		\return  const vector<std::pair<unsigned, unsigned>>* Wskaźnik na wektor par koordynatów.
	*/
	const vector<std::pair<unsigned, unsigned>>* getLastDeletedPositions()const;
	//! Zwraca obiekt gracza o zadanym kolorze.
	/*!
		\param color Kolor gracza.
		\return  Player* Wskaźnik na gracza,
	*/
	Player* getPlayer(FieldColor color);
	//! Zwraca zwycięzcę.
	/*!
		Metoda zwraca wskaźnik na obiekt reprezentujący zwycięskiego gracza. Jeśli gra nadal trwa zwróci nullptr.
		\return  Player* Wskaźnik na gracza
	*/
	Player* getWinner();

	
	
};

