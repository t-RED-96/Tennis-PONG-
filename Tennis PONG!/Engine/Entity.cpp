#include "Entity.h"

const glm::mat4& Entity::Matrix() const {
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

void Entity::ChangeAllParams(const glm::vec3& newPosn, const glm::vec3& newRotation, const glm::vec3& newScale)
{
	_Position = newPosn;
	_Rotation = newRotation;
	_Scale = newScale;
	updateTransformationMatrix();
}

void* Entity::GetComponent(Component::Type typ)
{
	unsigned char i = 0;
	while (allComponentsAttached[i]->typ() != typ)
		if (i < allComponentsAttached.size())
			i++;
		else
			return nullptr;
	return allComponentsAttached[i]->getComponent();
}

Model& Entity::AddModel(const std::string& filePath)
{
	auto _temp = this;
	auto temp = Model(*_temp);
	Model& comp = sceneItIsPartOf->AddComponent(temp);
	comp.LoadModel(filePath);
	allComponentsAttached.push_back((Component*)(&comp));
	return comp;
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

Collider& Entity::AddCollider(Collider::TYP typ, float radius)
{
	auto _temp = this;
	auto temp = Collider(*_temp, typ, radius);
	auto& comp = sceneItIsPartOf->AddComponent(temp);
	allComponentsAttached.push_back((Component*)(&comp));
	return comp;
}

Collider& Entity::AddCollider(Collider::TYP typ, float radius, float height)
{
	auto _temp = this;
	auto temp = Collider(*_temp, typ, radius, height);
	auto& comp = sceneItIsPartOf->AddComponent(temp);
	allComponentsAttached.push_back((Component*)(&comp));
	return comp;
}

Collider& Entity::AddCollider(Collider::TYP typ, float length, float breadth, float height)
{
	auto _temp = this;
	auto temp = Collider(*_temp, typ, length, breadth, height);
	auto& comp = sceneItIsPartOf->AddComponent(temp);
	allComponentsAttached.push_back((Component*)(&comp));
	return comp;
}

RigidBody& Entity::AddRigidBody(const glm::vec3& Velocity,const glm::vec3& Acceleration, float Mass)
{
	auto _temp = this;
	auto temp = RigidBody(*_temp, Velocity, Acceleration, Mass);
	auto& comp = sceneItIsPartOf->AddComponent(temp);
	allComponentsAttached.push_back((Component*)(&comp));
	return comp;
}

Scripts& Entity::AddScripts(void(*_reset)(Entity& thisObj), void(*_update)(Entity& thisObj))
{
	auto _temp = this;
	auto temp = Scripts(*_temp, _reset, _update);
	auto& comp = sceneItIsPartOf->AddComponent(temp);
	allComponentsAttached.push_back((Component*)(&comp));
	return comp;
}
