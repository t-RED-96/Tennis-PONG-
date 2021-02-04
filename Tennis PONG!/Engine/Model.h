//#ifdef ENGINE
#include <vector>
#include <string>
#include <glm\gtc\type_ptr.hpp>
#include "Mesh.h"
#include "Texture.h"
#include "obj_loader.h"
class Component;
#include "Component.h"
class Entity;
#pragma once

class Model :
    public Component
{
public:
    Model() = delete;
    Model(Entity& thisObj): opaque(true), Component(thisObj) {};
	void LoadModel(const std::string& fileName);
	const glm::mat4& Matrix() const;
	void RenderModel() const;
	void ClearModel();
	void Transparent(bool state);

	~Model();
private:
    virtual void* getComponent() override { return this; }
    virtual Component::Type typ() override { return Component::Type::MODEL; }
	void LoadMeshesAndMaterials(const objLoad::Loader& loader);
	void LoadMesh(const objLoad::Mesh& mesh);
	void LoadMaterials(const objLoad::Material& material);
	bool opaque;
	std::vector<Mesh*> mesh_list;
	std::vector<Texture*> texture_list;
};
//#endif