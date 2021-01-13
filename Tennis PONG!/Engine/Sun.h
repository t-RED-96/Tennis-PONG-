#ifdef ENGINE
#pragma once
#include "BaseLight.h"
#include "Component.h"
class Sun :
    public Component, public BaseLight
{
public:
    Sun(Entity& thisObj):Component(thisObj){}
    void operator=(const Sun& oth) {
        thisObj = oth.thisObj;
    }
private:
    void* getComponent() override { return this; }
    ComponentType typ() override { return SUN; }
};

#endif