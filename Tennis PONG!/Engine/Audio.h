//#ifdef ENGINE
class Component;
#include "Component.h"
class Entity;

#pragma once
class Audio :
    public Component
{
public:
    Audio(Entity& thisObj): Component(thisObj) {};
private:
    void* getComponent() override { return this; }
    Component::Type typ() override { return Component::Type::AUDIO; }
public: 
    static Component::Type Typ(){ return Component::Type::AUDIO; }
};

//#endif
