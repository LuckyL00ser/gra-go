#include "GUIButton.h"



void GUI::GUIButton::setSizeDerivered()
{
	borders.setSize(getSize());
	centerText();
}

void GUI::GUIButton::derivedClassReaction()
{
}

void GUI::GUIButton::centerText()
{
	text.setOrigin(text.getLocalBounds().width / 2.0, text.getLocalBounds().height / 2.0);
	
	text.setPosition(getSize().x/2,getSize().y/2);
	
}
void GUI::GUIButton::setCustomButtonProperties()
{
	setTextSize(30);
	setBorderThickness(3);

	setBorderColor(sf::Color(226, 124, 81));
	textNormalColor = sf::Color::Black;
	textHoverColor = sf::Color::White;
	textClickedColor = sf::Color::Yellow;

	backgroundNormalColor = sf::Color::White;
	backgroundHoverColor = sf::Color(200, 200, 200, 128);
	backgroundClickedColor = sf::Color(128, 128, 128, 255);
}






GUI::GUIButton::GUIButton(sf::Vector2f position, sf::Vector2f buttonSize, sf::Font * font, std::string text, GUIElement * parent, EventCallback cb) :
	GUIElement(position, parent),active(true)
{
	//domyslny styl przycisku

	setCallback(cb);
	setFont(*font);
	this->text.setString(text);
	setSize(buttonSize);
	setCustomButtonProperties();

	this->text.setFillColor(textNormalColor);
	borders.setFillColor(backgroundNormalColor);
}


GUI::GUIButton::~GUIButton()
{
}





GUI::ButtonState GUI::GUIButton::getState()
{
	return state;
}

void GUI::GUIButton::setText(const std::string& newText)
{
	text.setString(newText);
	centerText();
}

void GUI::GUIButton::setBackgroundImage(const sf::Texture & background)
{
	borders.setTexture(&background,false);
	borders.setFillColor(backgroundNormalColor);
	
}



void GUI::GUIButton::setTextSize(unsigned size)
{
	text.setCharacterSize(size);
	centerText();
}

void GUI::GUIButton::setFont(const sf::Font & newFont)
{
	
		text.setFont(newFont);
		centerText();
	
}

void GUI::GUIButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	
	
	if (!isVisible())
		return;
		
	states.transform *= getTransform();
	target.draw(borders, states);
	target.draw(text, states);
	
}

void GUI::GUIButton::update(sf::Event& e, sf::RenderWindow& window)
{
	
	if (!isActive())
		return;
	
	sf::Vector2i m_mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2i parentOffset;
	if (getParent() != nullptr)
		parentOffset = sf::Vector2i(getParent()->getPosition().x, getParent()->getPosition().y);
	bool mouseInButton = m_mousePosition.x >= getPosition().x - getOrigin().x + parentOffset.x
		&& m_mousePosition.x <= getPosition().x + getSize().x - getOrigin().x + parentOffset.x
		&& m_mousePosition.y >= getPosition().y - getOrigin().y + parentOffset.y
		&& m_mousePosition.y <= getPosition().y + getSize().y - getOrigin().y + parentOffset.y;

	switch (e.type) {
	case sf::Event::MouseMoved:
		if (mouseInButton)
		{
			if (!pressed)
				state = ButtonState::HOVER;
			else
				state = ButtonState::CLICKED;
		}

		else
		{
			state = ButtonState::NORMAL;
			pressed = false;
		}
		break;
	case sf::Event::MouseButtonPressed:
		
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			if (mouseInButton)
			{
				state = ButtonState::CLICKED;
				pressed = true;
			}

			else
			{
				state = ButtonState::NORMAL;
				pressed = false;
			}
		}
		
		
		break;
	case sf::Event::MouseButtonReleased:
		
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			if (mouseInButton)
			{
				
				if (pressed) {
					if (callback != nullptr)
						derivedClassReaction();
						callback();
					
					
					
				}
					
			}

			state = ButtonState::NORMAL;
			pressed = false;
		}
		
		break;
	}
	

	
	switch (state) {
	case ButtonState::CLICKED:

		text.setFillColor(textClickedColor);
		
		borders.setFillColor(backgroundClickedColor);
		
		break;
	case ButtonState::HOVER:

		text.setFillColor(textHoverColor);
		borders.setFillColor(backgroundHoverColor);
		break;
	case ButtonState::NORMAL:
		text.setFillColor(textNormalColor);
		borders.setFillColor(backgroundNormalColor);
		break;
	}

}
