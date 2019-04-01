#include "GUILine.h"



void GUI::GUILine::setSizeDerivered()
{
	//TODO: resize lines
}

GUI::GUILine::GUILine(sf::Vector2f position):GUIElement(position)
{
	sf::Vertex *start = new sf::Vertex(sf::Vector2f(0, 0)), *end = new sf::Vertex(sf::Vector2f(0, 0));
	start->color = sf::Color::Black;
	end->color = sf::Color::Black;
	line.append(*start);
	
	line.append(*end);
}


GUI::GUILine::~GUILine()
{
	line.clear();
}

void GUI::GUILine::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(line, states);

}
