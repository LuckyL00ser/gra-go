#pragma once
#include <map>
#include "ResoruceIDs.h"
#include <string>

template<typename IDType,typename T>
//! Klasa szablonowa reprezentująca menedżer zasobów.
		/*!
			Klasa może być utworzona dla zasobów dowolnego rodzaju określonych w bibliotece SFML (korzysta z funkcji loadFromFile z klas
			zasobów SFML). Umożliwia zarządzanie, dodawanie, usuwanie określonych zasobów przypisując im odpowiednie id co znacznie
			ułatwia ich rozróżnienie dalej w kodzie.
		*/
class ResourceManager
{

public:
	//! Konstruktor
	
	ResourceManager() {};
	//!Destruktor
		/*!
			Zwalnia wszystkie wczytane zasoby określonego typu.
		*/
	virtual ~ResourceManager() {
		
		releaseAllResources();
	
	};
	//! Metoda zwraca zasób danego typu.
		/*!
			Zwraca wskaźnik do rządanego zasobu. Jeśli jest to jego pierwsze użycie w aplikacji, zasób ten zostaj wczytany. Inaczej, nie będąc
			potrzebnym nie jest ładowany, nawet jeśli zmapowano jego ID ze ścieżką. Zwraca pusty wskaźnik jesli jest to nieznany zasób.
			\param requestedResource ID rządanego zasobu.
			\return T* Wskaźnik do rządanego zasobu.
		*/
	T* getResource(IDType requestedResource) ;
	//! Zwalnia określony zasób.
		/*!
			Zwalnia wczytany zasób.
			\param resourceToRelease ID skojarzone z zasobem do zwolnienia.
			\return void
		*/
	void releaseResource(IDType resourceToRelease);
	//! Dodaje ścieżkę do zasobu.
		/*!
			Przekazana ścieżka do pliku zostaje skorelowana z odpowiadającym jej ID zasobu, po którym później dany plik jest 
			rozpoznawany.
			\param path Ścieżka do pliku.
			\param resource Id zasobu do skojarzenia ze ścieżką
			\return void
		*/
	void addPath(const std::string& path, IDType resource);
	//! Zwraca ścieżkę do zasobu.
		/*!
			
			\param resource ID zasobu.
			\return std::string Ścieżka do pliku zasobu.
		*/
	std::string getPath(IDType resource) const;
	

protected:
	std::map<IDType, std::string> paths; /**<Obiekt łączący w pary ścieżki do plików wraz z odpowiadającymi im identyfikatorami zasobów.*/
	std::map<IDType, T*> resources; /**<Obiekt łączący w pary identyfikatory zasobów wraz z odpowiadającymi im zasobami załadowanymi do pamięci operacyjnej*/
	//! Metoda reagująca zwalnia z pamięci wszystkie zasoby.
		/*!
			Metoda zwalnia z pamięci wszelkie zasoby danego typu podlegające danej instancji menadżera zasobów, jakie 
			zostały wczytane w trakcie działania aplikacji.
			\return  void
		*/
	void releaseAllResources();
	//! Metoda znajdująca zasób na podstawie odpowiadającego mu identyfikatora.
		/*!
			Jeśli żądanego zasobu nie ma jeszcze w pamięci (w mapie resources) zostanie on wczytany i zwrócony wskaźnik do niego.
			Jeśli plik zasobu nie istnieje bądź zmapowano jego identyfikator z błędną ścieżką do pliku zwrócony zostanie pusty
			wskaźnik.
			\param id Identyfikator zasobu.
			\return  T* Wskaźnik do zasobu w pamięci. Pusty jeśli zasób nie istnieje.
		*/
	T* Find(IDType id);
	//! Metoda wczytująca zasób do pamięci.
		/*!
			Metoda ta dziedziczona jest z klasy GUI::GUIElement i wywoływana jest przez metodę setSize tejże klasy.
			Implementuje zachowanie się obiektu klasy GUI::GUILine po zmianie rozmiaru.
			\return  void
		*/
	T* load(IDType resource);
};


template<typename IDType, typename T>
void ResourceManager<IDType, T>::releaseAllResources()
{
	for (auto const& x : resources) // C++ 11
	{
		delete x.second;
	}
	resources.clear();
}
template<typename IDType, typename T>
T* ResourceManager<IDType, T>::Find(IDType id) {
	auto result = resources.find(id);
	return result != resources.end() ? result->second : nullptr;
}


template<typename IDType, typename T>
T* ResourceManager<IDType, T>::load(IDType resource)
{
	T* newResource = new T();

	if (!newResource->loadFromFile(getPath(resource))) {
		throw std::runtime_error("Bledna sciezka do pliku");
		return nullptr;
	}
	//dodawanie zasobu:
	auto emplaced = resources.emplace(resource, newResource);
	return emplaced.first->second;
}



template<typename IDType, typename T>
T* ResourceManager<IDType, T>::getResource(IDType requestedResource)
{
	T* result = Find(requestedResource);
	
	return (result == nullptr) ? load(requestedResource) : result; //jesli nie znaleziono zasobu sprobuj go zaladowac
}

template<typename IDType, typename T>
void ResourceManager<IDType, T>::releaseResource(IDType resourceToRelease)
{
	auto result = resources.find(resourceToRelease);
	if (result == resources.end()) //gdy nie znaleziono zasobu nie ma czego zwalniac
		return;

	delete result->second;

}

template<typename IDType, typename T>
void ResourceManager<IDType, T>::addPath(const std::string& pathToFile, IDType resource)
{
	auto result = resources.find(resource);
	if (result != resources.end()) //zasob a tym samym sciezka do niego istnieje
		return;

	auto path = paths.find(resource);
	if (path != paths.end()) //sciezka juz jest w pamieci
		return;

	paths.emplace(resource, pathToFile);

}

template<typename IDType, typename T>
std::string ResourceManager<IDType, T>::getPath(IDType resource) const
{
	auto path = paths.find(resource);
	return path == paths.end() ? nullptr : (path->second);
}




