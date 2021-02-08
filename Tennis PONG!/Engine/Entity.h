//#ifdef ENGINE
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#pragma once
class Scene;
#include "Scene.h"
class Component;
#include "Component.h"
class Model;
#include "Model.h"
class AnimatedModel;
#include "AnimatedModel.h"
class Audio;
#include "Audio.h"
class Camera;
#include "Camera.h"
class Collider;
#include "Collider.h"
class Camera;
#include "Camera.h"
class RigidBody;
#include "RigidBody.h"
class Scripts;
#include "Scripts.h"
class Sun;
#include "Sun.h"

class Entity
{
private:
	glm::vec3 _Position;
	glm::vec3 _Rotation;
	glm::vec3 _Scale;
	Scene* sceneItIsPartOf;
	glm::mat4 transformationMatrix;
	std::vector<Component*> allComponentsAttached;
public:
	Entity() = delete;

	Entity(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, Scene* _scene)
		:_Position(position), _Rotation(rotation), _Scale(scale)
	{
		sceneItIsPartOf = _scene;
		updateTransformationMatrix();
	}
//#ifdef OnlyEngineHasAccess

//#endif // OnlyEngineHasAccess
public:
	const glm::mat4& Matrix() const;
	const glm::mat3 ConstructRotationMatrix() const;
	const glm::vec3& Position() const;
	const glm::vec3& Position(const glm::vec3& newPosn);
	const glm::vec3& Rotation() const;
	const glm::vec3& Rotation(const glm::vec3& newRotation);
	const glm::vec3& Scale() const;
	const glm::vec3& Scale(const glm::vec3& newScale);
	const glm::vec3 Front() const;
	const glm::vec3 Right() const;
	const glm::vec3 Up() const;
	void ChangeAllParams(const glm::vec3& newPosn, const glm::vec3& newRotation, const glm::vec3& newScale);

	//template<class Tp>
	//const Tp* GetComponent(Tp*) const;

	void* GetComponent(Component::Type typ) const;

	void LookAt(const glm::vec3& _position_in_space);
	void LookAndRollBy(const glm::vec3& _position_in_space,float _roll_amount_in_degrees);
	//MODEL params
	Model& AddModel(const std::string& filePath);//model params
	//ANIMATED_MODEL params
	//const AnimatedModel& AddAnimatedModel(const AnimatedModel& comp);
	//AUDIO params
	//const Audio& AddAudio(const Audio& comp);
	//CAMERA params
	Camera& AddCamera(float fov_y, float aspectRatio, float nearClipDist, float farClipDist);
	//COLLIDER params
	Collider& AddCollider(Collider::TYP typ, float radius);
	Collider& AddCollider(Collider::TYP typ, float radius, float height);
	Collider& AddCollider(Collider::TYP typ, float length, float breadth, float height);
	//RIGIDBODY,
	RigidBody& AddRigidBody(const glm::vec3& Velocity,const glm::vec3& Acceleration, float Mass);
	//SCRIPT,
	Scripts& AddScripts(void(*_reset)(Entity& thisObj), void(*_update)(Entity& thisObj));
	Scripts& AddScripts(void(*_update)(Entity& thisObj));
	//SUN,
	//const Sun& AddSun(const Sun& comp);
	void Updated(bool status) const { matrixUpdated = status; }//this is dangerous but it works
	bool Updated() const { return matrixUpdated; }
public: //Utility Functions
	static glm::mat3 MakeRotationX(float radians);
	static glm::mat3 MakeRotationY(float radians);
	static glm::mat3 MakeRotationZ(float radians);

	static glm::vec2 pitchYawFromDirn(glm::vec3& dirn);
private:
	void updateTransformationMatrix();
	mutable bool matrixUpdated;
};
//#endif