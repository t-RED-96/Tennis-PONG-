#ifdef ENGINE
#pragma once
#include "Model.h"
class AnimatedModel :
    public Model
{
public:
    AnimatedModel() {}
private:
    void* getComponent() override { return this; }
    ComponentType typ() override { return ANIMATED_MODEL; }
};

#endif