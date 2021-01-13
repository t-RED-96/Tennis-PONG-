#include "Scripts.h"

Scripts::Scripts(Entity& thisObj,void(*reset)(Entity& thisObj), void(*update)(Entity& thisObj))
	:Component(thisObj),_reset(reset),_update(update)
{}

void Scripts::Reset()
{
	_reset(thisObj);
}

void Scripts::Update()
{
	_update(thisObj);
}
