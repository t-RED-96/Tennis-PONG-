#include "Entity.h"

const glm::mat4& Entity::Matrix() const {
	return transformationMatrix;
}

const glm::mat3 Entity::ConstructRotationMatrix() const
{
	return glm::transpose(MakeRotationZ(glm::radians(_Rotation.z)) * MakeRotationX(glm::radians(_Rotation.x)) * MakeRotationY(glm::radians(_Rotation.y)));
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

const glm::vec3 Entity::Right() const
{//X axis
	glm::mat3 mat = ConstructRotationMatrix();
	return mat * glm::vec3(-1, 0, 0);
}
const glm::vec3 Entity::Up() const
{//Y axis
	glm::mat3 mat = ConstructRotationMatrix();
	return mat * glm::vec3(0, 1, 0);
}
const glm::vec3 Entity::Front() const
{//Z axis
	//return glm::vec3(transformationMatrix[0][2], transformationMatrix[1][2], transformationMatrix[2][2]);
	glm::mat3 mat = ConstructRotationMatrix();
	return mat * glm::vec3(0, 0, 1);
}

void Entity::ChangeAllParams(const glm::vec3& newPosn, const glm::vec3& newRotation, const glm::vec3& newScale)
{
	_Position = newPosn;
	_Rotation = newRotation;
	_Scale = newScale;
	updateTransformationMatrix();
}

//template<class Tp>
//const Tp* Entity::GetComponent(Tp* _pass_NULL) const
//{
//	return static_cast<const Tp*>(GetComponent(Tp::Typ()));
//}
void* Entity::GetComponent(Component::Type typ) const
{
	unsigned char i = 0;
	while (allComponentsAttached[i]->typ() != typ)
		if (i < allComponentsAttached.size())
			i++;
		else
			return nullptr;
	return allComponentsAttached[i]->getComponent();
}

void Entity::LookAt(const glm::vec3& _position_in_space)
{
	glm::vec3 dirn(glm::normalize(_position_in_space - Position()));
	glm::vec2 angl = Entity::pitchYawFromDirn(dirn);
	glm::vec3 eular(angl.x, angl.y, 0);
	Rotation(eular);
}
void Entity::LookAndRollBy(const glm::vec3& _position_in_space, float _roll_amount_in_degrees)
{
	glm::vec3 dirn(glm::normalize(_position_in_space - Position()));
	glm::vec2 angl = Entity::pitchYawFromDirn(dirn);
	glm::vec3 eular(angl.x, angl.y, _roll_amount_in_degrees);
	Rotation(eular);
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
	transformationMatrix = glm::rotate(transformationMatrix, glm::radians(_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transformationMatrix = glm::rotate(transformationMatrix, glm::radians(_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transformationMatrix = glm::rotate(transformationMatrix, glm::radians(_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	transformationMatrix = glm::scale(transformationMatrix, _Scale);

	matrixUpdated = true;
}

glm::vec2 Entity::pitchYawFromDirn(glm::vec3& dirn)
{
	/*       Y axis
			  |
			  |     SCREEN
			  |
			  |____________X axis
			 /
	  Z axis/
	*/
	dirn = glm::normalize(dirn);
	float x = dirn.x;
	float y = dirn.y;
	float z = dirn.z;
	float xz = sqrt(x * x + z * z);//length of projection in xz plane
	float xyz = 1.0f;//i.e sqrt(y*y + xz*xz);//length of dirn

	float yaw = glm::degrees(asin(x / xz));
	float pitch = glm::degrees(asin(y / xyz));
	//front is  0, 0, 1;
	if (dirn.z < 0)
		yaw = 180 - yaw;

	//negating pitch --\/ as pitch is clockwise rotation while eular rotation is counter-Clockwise
	return glm::vec2(-pitch, yaw);
}

Camera& Entity::AddCamera(float fov_y_in_degrees, float aspectRatio, float nearClipDist, float farClipDist)
{
	auto _temp = this;
	auto temp = Camera(*_temp, fov_y_in_degrees,aspectRatio,nearClipDist,farClipDist);
	auto& comp = sceneItIsPartOf->AddComponent(temp);
	allComponentsAttached.push_back((Component*)(&comp));
	return comp;
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

Scripts& Entity::AddScripts(void(*_update)(Entity& thisObj))
{
	auto _temp = this;
	auto temp = Scripts(*_temp, NULL, _update);
	auto& comp = sceneItIsPartOf->AddComponent(temp);
	allComponentsAttached.push_back((Component*)(&comp));
	return comp;
}

Sun& Entity::AddSun(glm::vec3 color_RGB, float ambientIntensity, float diffuseIntensity)
{
	auto _temp = this;
	auto temp = Sun(*_temp, color_RGB, ambientIntensity, diffuseIntensity);
	auto& comp = sceneItIsPartOf->AddComponent(temp);
	allComponentsAttached.push_back((Component*)(&comp));
	return comp;
}

glm::mat3 Entity::MakeRotationX(float radians) {
	float c = cos(radians);
	float s = sin(radians);
	return (glm::mat3(1.0f, 0.0f, 0.0f,
		0.0f, c, -s,
		0.0f, s, c));
}
glm::mat3 Entity::MakeRotationY(float radians) {
	float c = cos(radians);
	float s = sin(radians);
	return (glm::mat3(c, 0.0f, s,
		0.0f, 1.0f, 0.0f,
		-s, 0.0f, c));
}
glm::mat3 Entity::MakeRotationZ(float radians) {
	float c = cos(radians);
	float s = sin(radians);
	return (glm::mat3(c, -s, 0.0f,
		s, c, 0.0f,
		0.0f, 0.0f, 1.0f));
}