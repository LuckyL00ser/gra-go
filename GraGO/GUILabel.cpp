#include "GUILabel.h"



void GUI::GUILabel::setSizeDerivered()
{
	label.setSize(getSize());
	centerText();
}

void GUI::GUILabel::centerText()
{
	text.setOrigin(text.getLocalBounds().width / 2.0, text.getLocalBounds().height / 2.0);
	text.setPosition(getSize().x / 2, getSize().y / 2);
}

void GUI::GUILabel::setCustomLabelProperties()
{
	setTextSize(30);
	setBorderThickness(3);

	setBorderColor(sf::Color(255, 255, 255, 170));
	setTextColor(sf::Color::Black);
	setBackgroundColor(sf::Color(228, 180, 93, 255));
}





GUI::GUILabel::GUILabel(sf::Vector2f position, sf::Vector2f size, sf::Font * font, std::string text)
{
	
	setPosition(position);
	setFont(*font);
	this->text.setString(text);
	setSize(size);
	setCustomLabelProperties();;
}


GUI::GUILabel::~GUILabel()
{
}

void GUI::GUILabel::setText(const std::string & text)
{
	this->text.setString(text);
	centerText();
}

void GUI::GUILabel::setTextSize(unsigned size)
{
	text.setCharacterSize(size);
	centerText();
}

void GUI::GUILabel::setFont(const sf::Font & newFont)
{
	text.setFont(newFont);
	centerText();
}

void GUI::GUILabel::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (!isVisible())
		return;

	target.draw(label, states);
	target.draw(text, states);
}


