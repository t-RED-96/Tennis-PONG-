#ifdef ENGINE
#pragma once
#include "Component.h"
class Audio :
    public Component
{
public:
    Audio(Entity& thisObj):Component(thisObj) {};
private:
    void* getComponent() override { return this; }
    ComponentType typ() override { return AUDIO; }
};

#endif
