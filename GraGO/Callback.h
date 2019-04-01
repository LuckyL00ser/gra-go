#pragma once
#include <functional>
typedef std::function<void()> EventCallback; 
//! Abstrakcyjna klasa implementująca mechanizm callback.
	/*!
		Pozwala klasom potomnym ustawić poprzez metodę setCallback() funkcje typu void() wywoływaną w reakcji na jakieś wydarzenie
		w klasie potomnej. Dzięki temu ograniczamy wiedzę klas agregowanych o klasach agregujących, jednocześnie umożliwiając im
		komunikację. Klasa dziedziczona jest głównie przez elementy graficzne np. GUIButton reagujący na kliknięcie.
	*/
class Callback
{
	
protected:
	//! Konstruktor
	/*!
		Konstruktor z modyfikatorem dostępu "protected" czyni klasę abstrakcyjną - nie może ona istnieć samodzielnie.
	*/
	Callback();
	
	EventCallback callback; /**< Pole przechowujące wskazanie na callback (funkcję)*/
public:
	//!	Metoda ustawia przekazaną funkcję jako callback obiektu
	/*!
		\return void
	*/
	void setCallback(EventCallback newCb);
	//! Wirtualny destruktor
	virtual ~Callback();
	
};

