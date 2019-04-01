#include "GUIElement.h"




bool GUI::GUIElement::isVisible() const
{
	return visible;
}

void GUI::GUIElement::show()
{
	visible = true;
}

void GUI::GUIElement::hide()
{
	visible = false;
}

sf::Vector2f GUI::GUIElement::getPositionRealitve()
{
	if (parent == nullptr)
		return getPosition();
	return getPosition() + parent->getPositionRealitve();
}
