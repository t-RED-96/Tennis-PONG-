#ifdef ENGINE
#pragma once
#include "Component.h"
class Model :
    public Component
{
public:
    Model(Entity& thisObj):Component(thisObj) {};
private:
    virtual void* getComponent() override { return this; }
    virtual ComponentType typ() override{ return MODEL; }
};

#endif