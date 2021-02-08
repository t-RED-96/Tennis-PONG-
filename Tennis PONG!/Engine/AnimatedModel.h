//#ifdef ENGINE
#pragma once

class Component;
#include "Component.h"
class Entity;
class Model;
#include "Model.h"

class AnimatedModel :
    public Model
{
public:
    AnimatedModel() = delete;
    AnimatedModel(Entity& thisObj): Model(thisObj) {};
private:
    void* getComponent() override { return this; }
    Component::Type typ() override { return Component::Type::ANIMATED_MODEL; }
public: 
    static const Component::Type Typ = Component::Type::ANIMATED_MODEL;
};

//#endif