#include "Collider.h"

Collider::Collider(Entity& thisObj,TYP typ, float radius)
	: Component(thisObj)
{
	if (typ == TYP::CIRCLE) {
		_typ = typ;
		this->radius = radius;
	}
}

Collider::Collider(Entity& thisObj,TYP typ, float radius, float height)
	:Component(thisObj)
{
	if (typ == TYP::CYLINDER) {
		_typ = typ;
		this->radius = radius;
		this->height = height;
	}
}

Collider::Collider(Entity& thisObj, TYP typ, float length, float breadth, float height)
	:Component(thisObj)
{
	if (typ == TYP::BOX) {
		_typ = typ;
		this->length = length;
		this->breadth = breadth;
		this->height = height;
	}
}
