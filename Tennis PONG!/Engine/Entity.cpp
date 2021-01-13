#include "Entity.h"

Entity::Entity(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, Scene* _scene)
	:sceneItIsPartOf(_scene),_Position(position), _Rotation(rotation), _Scale(scale)
{
	updateTransformationMatrix();
}

const glm::mat4& Entity::Matrix() const
{
	return transformationMatrix;
}

const glm::vec3& Entity::Position() const {
	return _Position;
}
const glm::vec3& Entity::Position(const glm::vec3& newPosn) {
	_Position = newPosn;
	updateTransformationMatrix();
	return _Position;
}
const glm::vec3& Entity::Rotation() const {
	return _Rotation;
}
const glm::vec3& Entity::Rotation(const glm::vec3& newRotation) {
	_Rotation = newRotation;
	updateTransformationMatrix();
	return _Rotation;
}
const glm::vec3& Entity::Scale() const {
	return _Scale;
}
const glm::vec3& Entity::Scale(const glm::vec3& newScale) {
	_Scale = newScale;
	updateTransformationMatrix();
	return _Scale;
}

void* Entity::GetComponent(Component::ComponentType typ)
{
	unsigned char i = 0;
	while (allComponentsAttached[i]->typ() != typ)
		if (i < allComponentsAttached.size())
			i++;
		else
			return nullptr;
	return allComponentsAttached[i]->getComponent();
}

void Entity::updateTransformationMatrix()
{
	transformationMatrix = glm::mat4(1.0f);
	transformationMatrix = glm::translate(transformationMatrix, _Position);
	transformationMatrix = glm::rotate(transformationMatrix, glm::radians(_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transformationMatrix = glm::rotate(transformationMatrix, glm::radians(_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transformationMatrix = glm::rotate(transformationMatrix, glm::radians(_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	transformationMatrix = glm::scale(transformationMatrix, _Scale);
}

const Collider& Entity::AddCollider(Collider::ColliderTyp typ, float radius)
{
	auto& comp = sceneItIsPartOf->AddComponent(Collider(*this, typ, radius));
	allComponentsAttached.push_back((Component*)(&comp));
	return comp;
}

const Collider& Entity::AddCollider(Collider::ColliderTyp typ, float radius, float height)
{
	auto& comp = sceneItIsPartOf->AddComponent(Collider(*this, typ, radius,height));
	allComponentsAttached.push_back((Component*)(&comp));
	return comp;
}

const Collider& Entity::AddCollider(Collider::ColliderTyp typ, float length, float breadth, float height)
{
	auto& comp = sceneItIsPartOf->AddComponent(Collider(*this, typ, length,breadth,height));
	allComponentsAttached.push_back((Component*)(&comp));
	return comp;
}

const RigidBody& Entity::AddRigidBody(glm::vec3 Velocity, glm::vec3 Acceleration, float Mass)
{
	auto& comp = sceneItIsPartOf->AddComponent(RigidBody(*this,Velocity,Acceleration,Mass));
	allComponentsAttached.push_back((Component*)(&comp));
	return comp;
}
