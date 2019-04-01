#include "GUITickbox.h"




void GUI::GUITickbox::derivedClassReaction()
{
	setChecked(!checked);
}

GUI::GUITickbox::GUITickbox(sf::Vector2f position, sf::Vector2f buttonSize ,sf::Font* font, GUIElement* parent, EventCallback cb) :
	GUIButton(position, buttonSize, font, "", parent, cb), checked(false) {

}

GUI::GUITickbox::~GUITickbox()
{
	
}

void GUI::GUITickbox::setChecked(bool c)
{
	checked = c;
	
	if (checked)
		setColorBackgroundNormal(checkedFillColor);
	else
		setColorBackgroundNormal(sf::Color::Transparent);
		//borders.setFillColor(backgroundNormalColor);
}

void GUI::GUITickbox::setCheckedFillColor(sf::Color color)
{
	checkedFillColor = color;
	setChecked(checked);
}


void GUI::GUITickbox::update(sf::Event & e, sf::RenderWindow & window)
{
	GUI::GUIButton::update(e, window);
	

	//if (checked) borders.setFillColor(checkedFillColor);
	//borders.setFillColor(checkedFillColor);
	
}
