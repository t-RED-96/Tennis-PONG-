//#ifdef ENGINE
#pragma once

class Component;
#include "Component.h"
class Entity;

class Scripts :
    public Component
{
private:
    void(*_reset)(Entity& thisObj);
    void(*_update)(Entity& thisObj);
    void* getComponent() override { return this; }
    Component::Type typ() override { return Component::Type::SCRIPT; }
public:
    static const Component::Type Typ = Component::Type::SCRIPT;
    Scripts() = delete;
    Scripts(Entity& thisObj,void(*_reset)(Entity& thisObj), void(*_update)(Entity& thisObj));
    void Reset() const;
    void Update() const;
};          

//#endif