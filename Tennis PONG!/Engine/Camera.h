#ifdef ENGINE
#pragma once
#include "Component.h"
class Camera :
    public Component
{
public:
    Camera(Entity& thisObj) :Component(thisObj) {}
private:
    void* getComponent() override { return this; }
    ComponentType typ() override { return CAMERA; }
};

#endif