#ifdef ENGINE
#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "All_Components.h"
#include "Scene.h"
class Entity
{
private:
	Scene* sceneItIsPartOf;
	glm::vec3 _Position;
	glm::vec3 _Rotation;
	glm::vec3 _Scale;
	glm::mat4 transformationMatrix;
	std::vector<Component*> allComponentsAttached;
public:
	Entity() = delete;
#ifdef OnlyEngineHasAccess
	Entity(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, Scene* _scene);
#endif // OnlyEngineHasAccess
	const glm::mat4& Matrix() const;
	const glm::vec3& Position() const;
	const glm::vec3& Position(const glm::vec3& newPosn);
	const glm::vec3& Rotation() const;
	const glm::vec3& Rotation(const glm::vec3& newRotation);
	const glm::vec3& Scale() const;
	const glm::vec3& Scale(const glm::vec3& newScale);
	void* GetComponent(Component::ComponentType typ);
	//MODEL params
	const Model& AddModel(const Model& comp);//model params
	//ANIMATED_MODEL params
	const AnimatedModel& AddAnimatedModel(const AnimatedModel& comp);
	//AUDIO params
	const Audio& AddAudio(const Audio& comp);
	//CAMERA params
	const Camera& AddCamera(const Camera& comp);
	//COLLIDER params
	const Collider& AddCollider(Collider::ColliderTyp typ, float radius);
	const Collider& AddCollider(Collider::ColliderTyp typ, float radius, float height);
	const Collider& AddCollider(Collider::ColliderTyp typ, float length, float breadth, float height);
	//RIGIDBODY,
	const RigidBody& AddRigidBody(glm::vec3 Velocity, glm::vec3 Acceleration, float Mass);
	//SCRIPT,
	const Scripts& AddScripts(const Scripts& comp);
	//SUN,
	const Sun& AddSun(const Sun& comp);
private:
	void updateTransformationMatrix();
};

#endif