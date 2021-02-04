//#ifdef ENGINE
#pragma once
class Component;
#include "Component.h"
class Entity;

class Collider :
    public Component
{
public:
    enum class TYP: unsigned char{
        CIRCLE,
        CYLINDER,
        BOX,
    };
private:
    union {
        float length;
        float radius;
    };
    float breadth;
    float height;
    TYP _typ;
public:
    Collider() = delete;
//#ifdef OnlyEngineHasAccess
    Collider(Entity& thisObj,TYP typ, float radius);
    Collider(Entity& thisObj,TYP typ, float radius, float height);
    Collider(Entity& thisObj,TYP typ, float length, float breadth, float height);
//#endif // OnlyEngineHasAccess
private:
    void* getComponent() override { return this; }
    Component::Type typ() override { return Component::Type::COLLIDER; }
};


//#endif