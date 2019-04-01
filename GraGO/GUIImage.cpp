#include "GUIImage.h"



void GUI::GUIImage::setSizeDerivered()
{
	graphics.setSize(getSize());
}

GUI::GUIImage::GUIImage()
{
}

GUI::GUIImage::GUIImage(const sf::Texture & tex)
{
	graphics.setTexture(&tex);
	
	setSize(tex.getSize().x,tex.getSize().y);
}


GUI::GUIImage::~GUIImage()
{
}

void GUI::GUIImage::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (!isVisible())
		return;
	
	target.draw(graphics, states);
}

