#ifdef ENGINE
#pragma once
#include <GLM/glm.hpp>
#include "Component.h"
class RigidBody :
    public Component
{
private:
    glm::vec3 _Velocity;
    glm::vec3 _Acceleration;
    float mass;
public:
    RigidBody() = delete;
    RigidBody(Entity& thisObj,glm::vec3 Velocity, glm::vec3 Acceleration, float Mass)
        :Component(thisObj),_Velocity(Velocity),_Acceleration(Acceleration),mass(Mass){}
private:
    void* getComponent() override { return this; }
    ComponentType typ() override { return RIGIDBODY; }
};

#endif