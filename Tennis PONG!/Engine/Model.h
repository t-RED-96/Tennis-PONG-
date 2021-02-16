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
private:
	static GLuint pivotLocationInShaderProg;
public:
	enum class Pivot:unsigned char
	{
		Mid_Centre,
		Left_Centre,
		Right_Centre,
		Forward_Centre,
		Backward_Centre,
		Left_Forward_Centre,
		Right_Forward_Centre,
		Left_Backward_Centre,
		Right_Backward_Centre,
		Mid_Bottom,
		Left_Bottom,
		Right_Bottom,
		Forward_Bottom,
		Backward_Bottom,
		Left_Forward_Bottom,
		Right_Forward_Bottom,
		Left_Backward_Bottom,
		Right_Backward_Bottom,
		Mid_Top,
		Left_Top,
		Right_Top,
		Forward_Top,
		Backward_Top,
		Left_Forward_Top,
		Right_Forward_Top,
		Left_Backward_Top,
		Right_Backward_Top,
		TOTAL
	};
	static void SetLocationsInShaderProg(GLuint pivotLocationInShaderProg) {
		Model::pivotLocationInShaderProg = pivotLocationInShaderProg;
	}
public:
	static const Component::Type Typ = Component::Type::MODEL;
    Model() = delete;
    Model(Entity& thisObj): opaque(true),pivotTyp(Pivot::Mid_Centre), Component(thisObj) {};
	void LoadModel(const std::string& fileName);
	const glm::mat4& Matrix() const;
	void RenderModel() const;
	void ClearModel();
	Model& Transparent(bool state);
	Model& ChangeMaterial(float shininess, float specularIntensity);
	Model& ChangePivot(Pivot typ);

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
	glm::vec3 minOfBoundedBox;
	glm::vec3 maxOfBoundedBox;
	Pivot pivotTyp;
	glm::vec3 EvaluatePivot() const;
};
//#endif