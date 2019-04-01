#pragma once
#include "FieldColor.h"
//! Klasa pola planszy
	/*!
		Operuje polem planszy i jego parametrami. Zwraca pozycję i kolor. Umożliwia zmianę koloru.
	*/
class Field
{

private:
	unsigned x, y; /**< Zmienne reprezentujące koordynaty pola planszy*/
	FieldColor color; /**<kolor planszy pola*/
	
public:
	//! Konstruktor
	/*!
		Ustawia pola klasy odpowiadające pozycji na planszy.
		\param positionX Kolumna planszy na ktorej znajduje się pole.
		\param positionY Wiersz planszy na ktorym znajduje się pole.

	*/
	Field(unsigned positionX, unsigned positionY) : x(positionX), y(positionY),color(FieldColor::EMPTY) {}
	//! Wirtualny destruktor.
	
	virtual ~Field();
	//! Zwraca pozycję x pola na planszy (kolumnę).
	/*!
		\return unsigned Pozycja x.
	*/
	unsigned getPositionX()const;
	//! Zwraca pozycję y pola na planszy (wiersz).
	/*!
		\return unsigned Pozycja y.
	*/
	unsigned getPositionY()const;
	//! Zwraca kolor pola na planszy(w tym pole puste).
	/*!
		\return FieldColor Kolor pola.
	*/
	FieldColor getColor()const; 
	//! Zmienia kolor pola na planszy.
	/*!
		\param color Nowy kolor pola planszy.
		\return void
	*/
	void setColor(FieldColor color);
};

