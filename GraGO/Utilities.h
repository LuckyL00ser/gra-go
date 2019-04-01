#pragma once
#include <SFML\Graphics\RenderStates.hpp>
#include  <SFML\Graphics\RenderWindow.hpp>
#include "ResourceManager.h"
#include "ResoruceIDs.h"
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Font.hpp>
#include "Settings.h"
//! Struktura przechowująca przydatne innym klasom obiekty, zmienne, charakterystyczne w całej grze.
	/*!
		Obiekt tej struktury przekazywany jest w aplikacji w głąb hierarchi obiektów agregujących się.
		Wykorzystywana jest głownie przez klasy reprezentujące graficzną stronę gry ale także przez
		samą logiczną warstwę aplikacji np. do uzsykania informacji o ustawieniach rozgrywki.
	*/
struct Utilities { 
	sf::RenderWindow& renderWindow; /**<Refenrecja do okna głównego gry*/
	sf::RenderStates states;	/**<Obiekt reprezentujący parametry renderowania obiektów graficznych*/
	ResourceManager<ResourceIDs::TextureID, sf::Texture>& textureManager; /**<Obiekt reprezentujący parametry menedżer zasobów typu tekstua*/
	ResourceManager<ResourceIDs::FontID, sf::Font>& fontManager; /**<Obiekt reprezentujący parametry menedżer zasobów typu czcionka*/
	Settings& applicationSettings; /**<Referencja do obiektu ustawień gry*/

};