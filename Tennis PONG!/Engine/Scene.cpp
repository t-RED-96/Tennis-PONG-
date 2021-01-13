#include "Scene.h"

const Entity& Scene::AddEntity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    return AddEntity(Entity(position, rotation, scale,this));
}

const Entity& Scene::AddEntity(const Entity& entity)
{
    auto& list = allEntity;
    list.push_back(entity);
    return list[list.size() - 1];
}

const Model& Scene::AddComponent(const Model& comp)
{
    auto& list = allModel;
    list.push_back(comp);
    return list[list.size() - 1];
}

const AnimatedModel& Scene::AddComponent(const AnimatedModel& comp)
{
    auto& list = allAnimatedModel;
    list.push_back(comp);
    return list[list.size() - 1];
}

const Audio& Scene::AddComponent(const Audio& comp)
{
    auto& list = allAudio;
    list.push_back(comp);
    return list[list.size() - 1];
}

const Camera& Scene::AddComponent(const Camera& comp)
{
    auto& list = allCamera;
    list.push_back(comp);
    return list[list.size() - 1];
}

const Collider& Scene::AddComponent(const Collider& comp)
{
    auto& list = allCollider;
    list.push_back(comp);
    return list[list.size() - 1];
}

const RigidBody& Scene::AddComponent(const RigidBody& comp)
{
    auto& list = allRigidBodyData;
    list.push_back(comp);
    return list[list.size() - 1];
}

const Scripts& Scene::AddComponent(const Scripts& comp)
{
    auto& list = allScripts;
    list.push_back(comp);
    return list[list.size() - 1];
}

const Sun& Scene::AddComponent(const Sun& comp)
{
    sun = comp;
    return sun;
}
