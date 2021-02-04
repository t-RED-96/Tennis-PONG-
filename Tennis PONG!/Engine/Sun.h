//#ifdef ENGINE
#pragma once

#include "BaseLight.h"
class Component;
#include "Component.h"
class Entity;

class Sun :
    public Component, public BaseLight
{
public:
    Sun() = delete;
    Sun(Entity& thisObj):Component(thisObj){}
private:
    void* getComponent() override { return this; }
    Component::Type typ() override { return Component::Type::SUN; }
};

//#endif