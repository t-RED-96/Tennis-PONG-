#include "Scene.h"

Entity& Scene::AddEntity(const glm::vec3& position,const glm::vec3& rotation,const glm::vec3& scale)
{
    Entity tempEntity(position, rotation, scale, this);
    return AddEntity(tempEntity);
}

Entity& Scene::AddEntity(const Entity& entity)
{
    auto& list = allEntity;
    list.push_back(entity);
    return list[list.size() - 1];
}

Model& Scene::AddComponent(const Model& comp)
{
    auto& list = allModel;
    list.push_back(comp);
    return list[list.size() - 1];
}

AnimatedModel& Scene::AddComponent(const AnimatedModel& comp)
{
    auto& list = allAnimatedModel;
    list.push_back(comp);
    return list[list.size() - 1];
}

Audio& Scene::AddComponent(const Audio& comp)
{
    auto& list = allAudio;
    list.push_back(comp);
    return list[list.size() - 1];
}

Camera& Scene::AddComponent(const Camera& comp)
{
    auto& list = allCamera;
    list.push_back(comp);
    currCamera = &list[list.size() - 1];
    return *currCamera;
}

Collider& Scene::AddComponent(const Collider& comp)
{
    auto& list = allCollider;
    list.push_back(comp);
    return list[list.size() - 1];
}

RigidBody& Scene::AddComponent(const RigidBody& comp)
{
    auto& list = allRigidBodyData;
    list.push_back(comp);
    return list[list.size() - 1];
}

Scripts& Scene::AddComponent(const Scripts& comp)
{
    auto& list = allScripts;
    list.push_back(comp);
    return list[list.size() - 1];
}

Sun& Scene::AddComponent(const Sun& comp)
{
    sun = new Sun(comp);
    return *sun;
}
