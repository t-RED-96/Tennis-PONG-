//#ifdef ENGINE
#include <GLM/glm.hpp>
class Component;
#include "Component.h"
class Entity;

#pragma once

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
        : _Velocity(Velocity), _Acceleration(Acceleration), mass(Mass), Component(thisObj) {}
private:
    void* getComponent() override { return this; }
    Component::Type typ() override { return Component::Type::RIGIDBODY; }
};

//#endif