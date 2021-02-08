//#ifdef ENGINE
#pragma once
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
class Component;
#include "Component.h"
class Entity;

class Camera :
    public Component
{
public:
    static const Component::Type Typ = Component::Type::CAMERA;

    Camera(Entity& thisObj, float fov_y, float aspectRatio, float nearClipDist, float farClipDist);
    const glm::mat4& ProjectionViewMatrix() const;
    void Update() const;
    void UpdateMatrix();
    const glm::vec3& Front() const { return cameraFront; }
    const glm::vec3& Right() const { return cameraRight; }
    const glm::vec3& Up() const { return cameraUp; }
    void LookAt(const glm::vec3& positionInSpace) const;
    void LookAndRollBy(const glm::vec3& positionInSpace, float _roll_amount_in_degrees) const;
    void Follow(Entity* target) const;
private:
    glm::mat4 projectionMatrix;
    mutable glm::mat4 viewMatrix;
    mutable glm::mat4 projViewMatrix;

    mutable glm::vec3 cameraFront;
    mutable glm::vec3 cameraRight;
    mutable glm::vec3 cameraUp;

    mutable Entity* target;

    void updateViewMatrix() const;
    void* getComponent() override { return this; }
    Component::Type typ() override { return Component::Type::CAMERA; }
};

//#endif