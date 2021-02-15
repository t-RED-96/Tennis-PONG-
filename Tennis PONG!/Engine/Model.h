//#ifdef ENGINE
#pragma once
#include <vector>
#include <string>
#include <glm\gtc\type_ptr.hpp>
#include "Mesh.h"
#include "Material.h"
#include "obj_loader.h"
class Component;
#include "Component.h"
class Entity;

class Model :
    public Component
{
public:
	static const Component::Type Typ = Component::Type::MODEL;
    Model() = delete;
    Model(Entity& thisObj): opaque(true), Component(thisObj) {};
	void LoadModel(const std::string& fileName);
	const glm::mat4& Matrix() const;
	void RenderModel() const;
	void ClearModel();
	Model& Transparent(bool state);
	Model& ChangeMaterial(float shininess, float specularIntensity);

	~Model();
private:
    virtual void* getComponent() override { return this; }
	virtual Component::Type typ() override { return Component::Type::MODEL; }
	void LoadMeshesAndMaterials(const objLoad::Loader& loader);
	void LoadMesh(const objLoad::Mesh& mesh);
	void LoadMaterials(const objLoad::Material& material);
	bool opaque;
	std::vector<Mesh*> mesh_list;
	std::vector<Material> material_list;
};
//#endif