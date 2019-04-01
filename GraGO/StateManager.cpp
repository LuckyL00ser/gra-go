#include "StateManager.h"

StateManager::~StateManager()
{
	while (!states.empty()) {
		popState(); //unique_ptr jest tracony -> obiekt BaseState na ktory wskazuje zostaje zniszczony
	}
	while (!toLateDelete.empty())
		toLateDelete.pop();
}

void StateManager::pushState(unique_ptr<BaseState> state)
{
	states.push(move(state));
	
}

void StateManager::popState()
{
	states.pop();
}

void StateManager::changeState(unique_ptr<BaseState> state)
{
	if (!states.empty()) {
		popState();
	}
	pushState(std::move(state));
}



void StateManager::update(sf::Event& e, sf::RenderWindow& window)
{
	if (!states.empty())
		states.top()->update(e,window);

	while (!toLateDelete.empty()) 
		toLateDelete.pop();
	
}

void StateManager::draw()
{
	if(!states.empty())
		states.top()->draw();
	
}

void StateManager::addTopToDelete()
{
	toLateDelete.push(std::move(states.top()));
	states.pop();
}


