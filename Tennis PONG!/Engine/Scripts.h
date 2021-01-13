#ifdef ENGINE
#pragma once
#include "Entity.h"
#include "Component.h"
class Scripts :
    public Component
{
private:
    void(*_reset)(Entity& thisObj);
    void(*_update)(Entity& thisObj);
    void* getComponent() override { return this; }
    ComponentType typ() override { return SCRIPT; }
public:
    Scripts() = delete;
    Scripts(Entity& thisObj,void(*_reset)(Entity& thisObj), void(*_update)(Entity& thisObj));
    void Reset();
    void Update();
};          

#endif