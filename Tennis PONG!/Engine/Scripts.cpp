#include "Scripts.h"

Scripts::Scripts(Entity& thisObj,void(*reset)(Entity& thisObj), void(*update)(Entity& thisObj))
	:Component(thisObj),_reset(reset),_update(update)
{}

void Scripts::Reset() const
{
	_reset(thisObj);
}

void Scripts::Update() const
{
	_update(thisObj);
}
