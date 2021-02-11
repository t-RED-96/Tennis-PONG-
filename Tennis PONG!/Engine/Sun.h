//#ifdef ENGINE
#pragma once
#include <GLM/glm.hpp>
#include <GL/glew.h>
class Component;
#include "Component.h"
class Entity;

class Sun :
    public Component
{
public:
    Sun() = delete;
    Sun(Entity& thisObj,glm::vec3 color_RGB,float ambientIntensity,float diffuseIntensity)
        : color(color_RGB),ambientIntensity(ambientIntensity),diffuseIntensity(diffuseIntensity), Component(thisObj)
    {}
    void ApplyLight(GLuint colorLocationInShaderProg, GLuint ambienceLocationInShaderProg, GLuint diffuseLocationInShaderProg, GLuint directionLocationInShaderProg) const;
private:
    void* getComponent() override { return this; }
    Component::Type typ() override { return Component::Type::SUN; }
public:
    static const Component::Type Typ = Component::Type::SUN;
private:
    glm::vec3 color;
    GLfloat ambientIntensity;
    GLfloat diffuseIntensity;
};

//#endif