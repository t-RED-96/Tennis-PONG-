//#ifdef ENGINE
class Entity;

#pragma once
class Component
{
public:
	enum class Type :unsigned char {
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
	virtual Type typ() = 0;
protected:
	Entity& thisObj;
	Component() = delete;
	Component(Entity& thisObj) :thisObj(thisObj) {};
};

//#endif