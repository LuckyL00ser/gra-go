#pragma once

#include "FieldColor.h"

//! Klasa reprezentująca gracza,

class Player
{
	FieldColor myType;
	unsigned points;
	
	
public:
	//! Konstruktor
	/*!
		Przypisuje graczowi kolor oraz zeruje pole z ilością zdobytych punktów.
	*/
	Player(FieldColor type) :myType(type), points(0) {}
	//! Metoda zwraca kolor/typ gracza.
	/*!
		\return FieldColor Kolor gracza.
	*/
	FieldColor getPlayerType();
	//! Metoda dodaje punkt graczowi.
	/*!
		\return void
	*/
	void addPoint() { points++; }
	//! Metoda dodaje punkty graczowi.
	/*!
		\param points Ilość punktów do dodania.
		\return void
	*/
	void addPoints(unsigned points) { this->points += points; }
	//! Metoda zwraca aktualną ilość punktów gracza.
	/*!
		\return unsigned Ilość punktów.
	*/
	unsigned getPoints() const;
	

};

