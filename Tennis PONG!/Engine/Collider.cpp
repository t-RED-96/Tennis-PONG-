#include "Collider.h"

Collider::Collider(Entity& thisObj,ColliderTyp typ, float radius)
	:Component(thisObj)
{
	if (typ == ColliderTyp::CIRCLE) {
		this->radius = radius;
	}
}

Collider::Collider(Entity& thisObj,ColliderTyp typ, float radius, float height)
	:Component(thisObj)
{
	if (typ == ColliderTyp::CYLINDER) {
		this->radius = radius;
		this->height = height;
	}
}

Collider::Collider(Entity& thisObj, ColliderTyp typ, float length, float breadth, float height)
	:Component(thisObj)
{
	if (typ == ColliderTyp::BOX) {
		this->length = length;
		this->breadth = breadth;
		this->height = height;
	}
}
