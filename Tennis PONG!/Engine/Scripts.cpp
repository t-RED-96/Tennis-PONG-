#include "Scripts.h"

Scripts::Scripts(Entity& thisObj,void(*reset)(Entity& thisObj), void(*update)(Entity& thisObj))
	:Component(thisObj),_reset(reset),_update(update)
{}

void Scripts::Reset() const
{
	if(_reset)
		_reset(thisObj);
}

void Scripts::Update() const
{
	if(_update)
		_update(thisObj);
}
