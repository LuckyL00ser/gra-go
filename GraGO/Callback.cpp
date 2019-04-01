#include "Callback.h"



Callback::Callback()
{
}


void Callback::setCallback(EventCallback newCb)
{
	callback = newCb;

}

Callback::~Callback()
{
}
