#include "AlertState.h"





void AlertState::createGUI()
{
	back = new GUI::GUIButton(sf::Vector2f(0, 0), sf::Vector2f(0, 0), utilities.fontManager.getResource(ResourceIDs::FontID::mainFont), "OK", this);
	
	info = new GUI::GUILabel(sf::Vector2f(0, 0), sf::Vector2f(0, 0), utilities.fontManager.getResource(ResourceIDs::FontID::mainFont));
	info->setText(message);
	
	
	
	back->setCallback(std::bind(&AlertState::goBack, this));

	attachChildren(*info, 0.1, 0.2, 0.8, 0.5);
	attachChildren(*back, 0.2, 0.75, 0.6, 0.1);
	
}

void AlertState::goBack()
{
	getStateManager()->addTopToDelete();
	getStateManager()->addTopToDelete();
}

AlertState::AlertState(StateManager * state, const Utilities & utilities,std::string msg):BaseState(state,utilities),
GUIGroup(sf::Vector2f(0,0 ), //pozycja
	sf::Vector2f(utilities.renderWindow.getSize().x , utilities.renderWindow.getSize().y ), nullptr),message(msg) //rozmiar - polowa okna w kazdym wymiarze
{
	createGUI();
}

AlertState::~AlertState()
{
}
void AlertState::update(sf::Event & e, sf::RenderWindow & window)
{
	GUIGroup::update(e, window);

}

void AlertState::draw() const
{
	GUIGroup::draw(utilities.renderWindow, utilities.states);

}