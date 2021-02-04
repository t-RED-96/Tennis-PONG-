//#ifdef ENGINE
#include <vector>
#pragma once
class Entity;
class Model;
class AnimatedModel;
class Audio;
class Camera;
class Collider;
class RigidBody;
class Scripts;
class Sun;
#include "All_Components.h"
class Scene
{
public:
	struct ComponentCatalogue {
		const std::vector<Entity>* allEntity;
		const std::vector<Model>* allModel;
		//const std::vector<AnimatedModel>* allAnimatedModel;
		//const std::vector<Audio>* allAudio;
		const std::vector<Camera>* allCamera;
		const Camera* currCamera;
		//const std::vector<Collider>* allCollider;
		//const std::vector<RigidBody>* allRigidBodyData;
		const std::vector<Scripts>* allScripts;
		//union {
		//	const Sun* sun;
		//	const Sun* mainLight;
		//};
	};
private:
	std::vector<Entity> allEntity;
	std::vector<Model> allModel;
	std::vector<AnimatedModel> allAnimatedModel;
	std::vector<Audio> allAudio;
	std::vector<Camera> allCamera;
	Camera* currCamera;
	std::vector<Collider> allCollider;
	std::vector<RigidBody> allRigidBodyData;
	std::vector<Scripts> allScripts;

	union {
		Sun* sun;
		Sun* mainLight;
	};
	void(*_init)(Scene& _this);
	void(*_update)(Scene& _this);
	void(*_render)(Scene& _this);
public:
	Scene(void(*_init)(Scene& _this),void(*_update)(Scene& _this),void(*_render)(Scene& _this)) 
		: currCamera(NULL), sun(NULL) , _init(_init), _update(_update), _render(_render)
	{};
	Entity& AddEntity(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
	ComponentCatalogue AllSceneComponentCatalogue() {
		return { &allEntity, &allModel, /*&allAnimatedModel, &allAudio,*/ &allCamera, currCamera, /*&allCollider, &allRigidBodyData,*/ &allScripts/*, sun*/ };
	};
	void Init() {
		_init(*this);
	}
	void Update() {
		_update(*this);
	}
	void Render() {
		_render(*this);
	}
//#ifdef OnlyEngineHasAccess

	Model& AddComponent(const Model& comp);
	AnimatedModel& AddComponent(const AnimatedModel& comp);
	Audio& AddComponent(const Audio& comp);
	Camera& AddComponent(const Camera& comp);
	Collider& AddComponent(const Collider& comp);
	RigidBody& AddComponent(const RigidBody& comp);
	Scripts& AddComponent(const Scripts& comp);
	Sun& AddComponent(const Sun& comp);

//#endif // OnlyEngineHasAccess
private:
	Scene() = delete;
	Entity& AddEntity(const Entity& entity);
};
//#endif