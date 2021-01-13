#ifdef ENGINE
#pragma once
class Entity;
class Component
{
public:
	enum ComponentType :unsigned char {
		ANIMATED_MODEL,
		AUDIO,
		CAMERA,
		COLLIDER,
		MODEL,
		RIGIDBODY,
		SCRIPT,
		SUN
	};
	virtual void* getComponent() = 0;
	virtual ComponentType typ() = 0;
protected:
	Component() = delete;
	Component(Entity& thisObj) :thisObj(thisObj) {};
	Entity& thisObj;
};

#endif