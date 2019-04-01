#include "GUIGroup.h"



void GUI::GUIGroup::setSizeDerivered()
{
	//TODO: obliczenie zmiany skali w stosunku do poprzedniego widoku
	//setScale(getSize().x / getSize().x, getSize().y / getSize().y);
}

GUI::GUIGroup::GUIGroup(sf::Vector2f position , sf::Vector2f size ,GUIElement* parent):GUIElement(position,parent)
{
	setSize(size);
	
}

GUI::GUIGroup::~GUIGroup()
{

	for (GUIElement* child : children) {
		delete child;
	}
	children.clear();
}

void GUI::GUIGroup::draw(sf::RenderTarget & target, sf::RenderStates states)const 
{ //rysowanie dzieci
	states.transform *= getTransform();
	if (!isVisible())
		return;
	
		for (auto& child : children) {
			child->draw(target, states);
		}
		
	
}

void GUI::GUIGroup::attachChildren(GUIElement& newChild, float xInPercent, float yInPercent, float widthInPercent, float heightInPercent)
{
	attachChildren(newChild);
	newChild.setPosition(xInPercent*getSize().x, yInPercent*getSize().y ); //+getPosition() nie potrzebne, uwzgledniane przy renderowaniu
	newChild.setSize(widthInPercent*getSize().x , heightInPercent*getSize().y );
}




void GUI::GUIGroup::attachChildren(GUIElement& newChild)
{
	
	children.push_back(&newChild);
}

void GUI::GUIGroup::detachChildren(GUIElement & child)
{
	vector<GUIElement*>::iterator it = children.begin();
	for (auto& cd : children) {
		if (&child == cd)
			break;
		it++;
	}
	children.erase(it);

}

void GUI::GUIGroup::moveChildrenOnTop(GUIElement & child)
{
	detachChildren(child);
	attachChildren(child);
	
}



void GUI::GUIGroup::update(sf::Event & e, sf::RenderWindow & window)
{
		
		for(auto& child : children){
			child->update(e, window);
			
		}
	
	
}

