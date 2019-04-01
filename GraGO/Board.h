#pragma once
#include "Settings.h"
#include <vector>
#include <stack>
#include "Field.h"
using namespace std;
//! Klasa reprezentujaca planszę gry.
	/*!
		Klasa reprezentuje planszę gry o dowolnych, przewidzianych w ustawieniach rozmiarach. Metody tej klasy
		pozwalają na umieszczanie pionów na planszy z jednoczesnym sprawdzeniem poprawności ruchu. Umożliwia
		finalne podliczenie zdobytych przez każdego z graczy punktów "terytoriów" planszy.
	*/
class Board
{
private:
	BoardSize boardSize; /**< Rozmiar planszy*/
	Field*** board;	/**< Dwuwymiarowa tablica wskaźników do pól planszy*/
	
	vector<std::pair<unsigned, unsigned>> lastDeletedPositions; /**< Wektor par zawierających koordynaty pól z których usunięto pionki w ostatnim ruchu.*/
	//! Sprawdza czy ruch na danej pozycji jest poprawny - zgodny z regułami gry.
	/*!
		Zwraca prawdę jeśli ruch jest poprawny, fałsz w innym wypadku. Wyrzuca błąd "out of range" w przypadku koordynatów
		przekraczających rozmiary planszy.
		\param column Kolumna planszy.
		\param row Wiersz planszy.
		\param color Kolor stawianego pionka.
		\return bool Prawda jeśli ruch jest poprawny.
	*/
	bool isMoveCorrect(unsigned column, unsigned row, FieldColor color) const;
	//! Metoda sprawdza czy podane koorydanty należą do planszy gry
	/*!
		Zwraca prawdę jeśli pozycja (column,row) znajduje się na planszy, fałsz w innym wypadku.
		\param column Kolumna planszy.
		\param row Wiersz planszy.
		\return bool Prawda jeśli koordynat jest poprawny.
	*/
	bool areRowAndColumnCorrect(unsigned column, unsigned row) const;
	//! Metoda zwracająca łańcuch pól tego samego rodzaju oraz wszystkich ich sąsiadów.
	/*!
		Metoda implementuje algorytm typu flood-fill do znajdywania sąsiadów oraz łańcuchów pól danego koloru (nie tylko pionów ale 
		również pustych pól, co wykorzystywane jest np. podczas końcowego punktowania planszy). Dla danego koordynatu pola wyznaczany jest
		łańcuch (chain) wszystkich pól tego samego rodzaju (czarny, bialy, pusty) które sąsiadują z sobą i są z soba połączone na planszy.
		Metoda wyznacza także osiągniętych sąsiadów (reach) dla uprzednio wyznaczonego łańcucha pól danego koloru, przy czym sąsiedzi moga
		być polami dowolnego rodzaju. Wartości te zwracane są jako wskaźnik do pary zawierającej wskaźniki do wektorów pól - pierwszy wektor łańcuch, 
		drugi wektor sąsiedzi. Metoda może być wywołana także dla pojedynczego pola - ono tez tworzy łańcuch o długości 1.
		\param column Kolumna planszy na której znajduje się sprawdzane pole.
		\param row Wiersz planszy na którym znajduję się sprawdzane pole.
		\return pair<vector<Field*>*,vector<Field*>*> Wskaźnik na parę zawierającą wskaźniki do wektorów z polami 1-łańcucha, 2- osiągniętych przez łańcuch sąsiadów.
	*/
	pair<vector<Field*>*, vector<Field*>*> getReachedAndChain(unsigned column, unsigned row)const;
	//! Metoda zwracająca sąsiadów danego pola.
	/*!
		
		\param column Kolumna planszy na której znajduje sie sprawdzane pole.
		\param row Wiersz planszy na którym znajduje się sprawdzane pole.
		\return vector<Field>* Wskaźnik na wektor sąsiadów (pól sąsiadujących).
	*/
	vector<Field*>* getNeighbors(unsigned column, unsigned row)const;
	//! Metoda zwracająca sąsiadów danego pola.
	/*!
		\param field Pole dla którego szukamy sąsiadów.
		\return vector<Field>*
	*/
	vector<Field*>* getNeighbors(Field* field)const;
	//! Metoda "zbierająca" z planszy zbite piony.
	/*!
		Metoda sprawdza czy ostatnio ustawiony pion doprowadził na planszy do sytuacji gdy sąsiadująca grupa pionów (łańcuch) nie posiada już
		więcej wolnych połączeń (oddechów) w takim przypadku zwraca prawdę i dodaje piony wymagające usunięcia do zmiennej lastDeletedPositions,
		zwraca prawdę. Jeśli grupa kamieni posiada choćby jedno wolne połączenie zwraca fałsz.
		\param stone Stawiany pion.
		\return bool Prawda jeśli operacja powiodła się.
	*/
	bool tryCaptureStones(Field* stone);
	//! Zdejmuje kamień (pion) z planszy.
	/*!
		Zmienia stan pola na puste (FieldColor::Empty)
		\param column Kolumna planszy na której znajduje się  pole.
		\param row Wiersz planszy na którym znajduje się  pole.
		\return void
	*/
	void takeOutStone(unsigned x, unsigned y);

public:
	//! Konstruktor
	/*!
		Tworzy planszę o przekazanym w argumencie rozmiarze.
	*/
	Board(BoardSize size);
	//! destruktor
	/*!
		Zwalnia pamięć po utworzonych w konstruktorze polach planszy.
	*/
	~Board();
	//! Metoda zwraca kamień (pion) na zadanej pozycji.
	/*!
		Moze generować wyjątek "out of range" jeśli podane koordynaty wyjdą poza zakres planszy.
		\param column Kolumna planszy na której znajduje się rządany pion.
		\param row Wiersz planszy na którym znajduje się rządany pion.
		\return Field* Pole na planszy.
	*/
	Field* getStoneAtPosition(unsigned column, unsigned row) const;
	//! Metoda zwraca pole planszy na zadanej pozycji.
	/*!
		Moze generować wyjątek "out of range" jeśli podane koordynaty wyjdą poza zakres planszy.
		\param column Kolumna planszy na której znajduje się rządany pion.
		\param row Wiersz planszy na którym znajduje się rządany pion.
		\return Field* Pole na planszy.
	*/
	Field* getFieldAtPosition(unsigned column, unsigned row) const;
	//! Zwraca rozmiar planszy.
	/*!
		
		\return BoardSize Rozmiar planszy.
	*/
	BoardSize getBoardSize()const; 
	//! Podlicza zajęte przez graczy terytoria na planszy.
	/*!
		Przyjęto metodę podliczania terytorium tzw. chińską. Punkty terytorium danego gracza równe są ilości kamieni jego koloru
		jakie obecnie znajdują sie na planszy oraz ilości pustych pól jakie on otoczył łańcuchem tylko i wyłącznie swoich pionow ( bądź krawędzią
		planszy).Jeśli puste terytorium sąsiaduje z pionami różnych kolorow to jest to "ziemia niczyja" i punkty za nią nie są nikomu przydzielane.
		Metoda zwraca różnicę zdobytych punktów terytoriów pomiędzy graczem czarnym i białym. Dla rezultatu gry znaczenie ma tylko to kto
		zdobył więcej punktów a nie o ile więcej.
		\return unsigned Różnica punktów terytorium czarnego i białego gracza.
	*/
	unsigned scoreBoard();
	//! Próbuje postawić pion na zadanej pozycji.
	/*!
		Metoda "probuje" postawić pion danego koloru na planszy ponieważ akcja taka mozę się nie powieść w przypadku gdy ruch niezgodny jest
		z regułami gry, wtedy zwraca fałsz. Jeśli ruch jest poprawny stawia pion, aplikuje rezultaty ruchu na planszy i zwraca prawdę.
		\param column Kolumna planszy na ktorej stawiamy pion.
		\param row Wiersz planszy na ktorym stawiamy pion.
		\param color Kolor stawianego pionu.
		\return bool Zwraca prawdę jeśli ruch jest poprawny.
	*/
	bool putStone(unsigned column, unsigned row,FieldColor color);
	//! Zwraca piony usunięte w ostatnim ruchu.
	/*!
		Jeśli ostatni ruch spowodował "zniknięcie" jakichś pionów z planszy to ta metoda pozwala na zwrócenie ich koordynatów.
		Stosowana jest przez klasy renderujące plansze do stwierdzenia które piony nalezy usunąć by zachować zgodność planszy  w pamięci
		i tej wyświetlanej na ekranie.
		\return const  vector<std::pair<unsigned, unsigned>>* Zbiór koordynatów usuniętych pionów.
	*/
	const vector<std::pair<unsigned, unsigned>>* getLastDeletedPositions()const;
	//! Zwraca rozmiar (ilość) pionów usuniętych po ostatnim ruchu.
	/*!
		\return unsigned Ilość ostatnio usuniętych pionów.
	*/
	unsigned getLastDeletedPositionsSize()const;
	
};

