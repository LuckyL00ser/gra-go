#include "Field.h"


Field::~Field()
{
}



unsigned Field::getPositionX() const
{
	return x;
}

unsigned Field::getPositionY() const
{
	return y;
}
FieldColor Field::getColor() const
{
	return color;
}

void Field::setColor(FieldColor color)
{
	this->color = color;
}
