//#ifdef ENGINE
class Component;
#include "Component.h"
class Entity;

#pragma once
class Camera :
    public Component
{
public:
    Camera(Entity& thisObj) :Component(thisObj) {}
private:
    void* getComponent() override { return this; }
    Component::Type typ() override { return Component::Type::CAMERA; }
};

//#endif