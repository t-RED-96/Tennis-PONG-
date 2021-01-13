#ifdef ENGINE
#pragma once
#include "Component.h"
class Collider :
    public Component
{
public:
    enum ColliderTyp: unsigned char{
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
    ColliderTyp _typ;
public:
    Collider() = delete;
#ifdef OnlyEngineHasAccess
    Collider(Entity& thisObj,ColliderTyp typ, float radius);
    Collider(Entity& thisObj,ColliderTyp typ, float radius, float height);
    Collider(Entity& thisObj,ColliderTyp typ, float length, float breadth, float height);
#endif // OnlyEngineHasAccess
private:
    void* getComponent() override { return this; }
    ComponentType typ() override { return COLLIDER; }
};


#endif