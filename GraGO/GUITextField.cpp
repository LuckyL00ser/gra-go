#include "GUITextField.h"



GUI::GUITextField::GUITextField(sf::Vector2f position, sf::Vector2f size, sf::Font * font, std::string text, GUIElement * parent) :
	GUIElement(position, parent), focus(false){

	setFont(*font);
	this->text.setString(text);
	setSize(size);
	borders.setOutlineColor(sf::Color(226, 124, 81, 128));
	this->text.setFillColor(sf::Color::Black);

}


void GUI::GUITextField::setSizeDerivered()
{
	borders.setSize(getSize());
	formatText();
}

void GUI::GUITextField::formatText()
{
	text.setOrigin(0, text.getLocalBounds().height / 2.0);
	text.setPosition(0, getSize().y / 2);
}



GUI::GUITextField::~GUITextField()
{
}

void GUI::GUITextField::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(borders, states);
	target.draw(text, states);
}

void GUI::GUITextField::update(sf::Event & e, sf::RenderWindow & window)
{
	sf::Vector2i m_mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2i parentOffset;
	if (getParent() != nullptr)
		parentOffset = sf::Vector2i(getParent()->getPosition().x, getParent()->getPosition().y);
	bool mouseInField = m_mousePosition.x >= getPosition().x - getOrigin().x + parentOffset.x
		&& m_mousePosition.x <= getPosition().x + getSize().x - getOrigin().x + parentOffset.x
		&& m_mousePosition.y >= getPosition().y - getOrigin().y + parentOffset.y
		&& m_mousePosition.y <= getPosition().y + getSize().y - getOrigin().y + parentOffset.y;
	if (e.type == sf::Event::MouseButtonReleased) {
		if (mouseInField) {
			focus = true;
			borders.setFillColor(hasFocus);
		}
		else {
			focus = false;
			borders.setFillColor(noFocus);
		}
	}
	else if (e.type == sf::Event::TextEntered && focus) {
		
		if (text.getGlobalBounds().width < getSize().x) {
			setText(text.getString() + e.text.unicode);
		}
	}
	else if (focus && e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Backspace) {
		if (text.getString().getSize()>0) {
			setText(text.getString().substring(0,text.getString().getSize()-2));
		}
	}

}

void GUI::GUITextField::setText(const std::string & text)
{
	this->text.setString(text);
	formatText();
}

void GUI::GUITextField::setTextSize(unsigned size)
{
	text.setCharacterSize(size);
	formatText();
}

void GUI::GUITextField::setFont(const sf::Font & newFont)
{
	text.setFont(newFont);
	formatText();
}

std::string GUI::GUITextField::getText() const
{
	return text.getString();
}
