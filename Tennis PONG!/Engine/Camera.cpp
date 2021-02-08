#include "Camera.h"
#include "Entity.h"

Camera::Camera(Entity& thisObj, float fov_y, float aspectRatio, float nearClipDist, float farClipDist)
    : projectionMatrix(glm::perspective(glm::radians(fov_y), aspectRatio, nearClipDist, farClipDist)),
    target(NULL), Component(thisObj)
{
    updateViewMatrix();
}

const glm::mat4& Camera::ProjectionViewMatrix() const
{
    return projViewMatrix;
}
void Camera::Update() const
{
    if (thisObj.Updated())
    {
        updateViewMatrix();
    };
    if (target) {
        LookAt(target->Position());
    }
}
void Camera::UpdateMatrix()
{
    updateViewMatrix();
}
void Camera::LookAt(const glm::vec3& positionInSpace) const
{
    glm::vec3 dirn(glm::normalize(positionInSpace - thisObj.Position()));
    glm::vec2 angl = Entity::pitchYawFromDirn(dirn*=-1.0f);//Inverting The Model Matrix Flipped the dirn of forward, so flipping the dirn to the trouble of flipping pitch yaw
    glm::vec3 eular(angl.x, angl.y, 0);
    thisObj.Rotation(eular);

    updateViewMatrix();
}

void Camera::LookAndRollBy(const glm::vec3& positionInSpace, float _roll_amount_in_degrees) const
{
    glm::vec3 dirn(glm::normalize(positionInSpace - thisObj.Position()));
    glm::vec2 angl = Entity::pitchYawFromDirn(dirn *= -1.0f);
    glm::vec3 eular(angl.x, angl.y, 0);
    thisObj.Rotation(eular);

    updateViewMatrix();
}

void Camera::Follow(Entity* target) const
{
    this->target = target;
    Update();
    LookAt(target->Position());
}

inline void Camera::updateViewMatrix() const
{
    viewMatrix = glm::inverse(thisObj.Matrix());
    projViewMatrix = projectionMatrix * viewMatrix;
    glm::mat3 matrix(thisObj.ConstructRotationMatrix());
    cameraRight = matrix * glm::vec3(1, 0, 0);
    cameraUp = matrix * glm::vec3(0, 1, 0);
    cameraFront = matrix * glm::vec3(0, 0, -1);
}