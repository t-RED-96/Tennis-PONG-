#ifdef ENGINE
#pragma once
#include "All_Components.h"
#include <vector>
class Scene
{
public:
	struct ComponentCatalogue {
		const std::vector<Entity>& allEntity;
		const std::vector<Model>& allModel;
		const std::vector<AnimatedModel>& allAnimatedModel;
		const std::vector<Audio>& allAudio;
		const std::vector<Camera>& allCamera;
		const Camera* currCamera;
		const std::vector<Collider>& allCollider;
		const std::vector<RigidBody>& allRigidBodyData;
		const std::vector<Scripts>& allScripts;
		union {
			const Sun& sun;
			const Sun& mainLight;
		};
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
		Sun sun;
		Sun mainLight;
	};
public:
	Scene() {};
	const Entity& AddEntity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	ComponentCatalogue AllSceneComponentCatalogue(){
		return { allEntity, allModel, allAnimatedModel, allAudio, allCamera, currCamera, allCollider, allRigidBodyData, allScripts };
	}
#ifdef OnlyEngineHasAccess
	const Model& AddComponent(const Model& comp);
	const AnimatedModel& AddComponent(const AnimatedModel& comp);
	const Audio& AddComponent(const Audio& comp);
	const Camera& AddComponent(const Camera& comp);
	const Collider& AddComponent(const Collider& comp);
	const RigidBody& AddComponent(const RigidBody& comp);
	const Scripts& AddComponent(const Scripts& comp);
	const Sun& AddComponent(const Sun& comp);
#endif // OnlyEngineHasAccess
private:
	const Entity& AddEntity(const Entity& entity);
};
#endif