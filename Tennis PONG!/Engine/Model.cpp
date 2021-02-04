#include "Model.h"
#include "Entity.h"

void Model::LoadModel(const std::string& fileName)
{
	objLoad::Loader loader;
	bool gotLoaded = loader.LoadFile(fileName);
	if (!gotLoaded)
	{
		printf("Model %s failed to load\n", fileName.c_str());
		return;
	}
	else {
		LoadMeshesAndMaterials(loader);
	}
}

const glm::mat4& Model::Matrix() const
{
	return thisObj.Matrix();
}

void Model::LoadMeshesAndMaterials(const objLoad::Loader& loader)
{
	mesh_list.reserve(loader.LoadedMeshes.size());
	texture_list.reserve(loader.LoadedMeshes.size());
	for (size_t i = 0; i < loader.LoadedMeshes.size(); i++)
	{
		LoadMesh(loader.LoadedMeshes[i]);
		LoadMaterials(loader.LoadedMeshes[i].MeshMaterial);
	}
}

void Model::LoadMesh(const objLoad::Mesh& mesh) {
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> TexCoords;
	std::vector<glm::vec3> Normals;
	positions.reserve(mesh.Vertices.size());
	TexCoords.reserve(mesh.Vertices.size());
	Normals.reserve(mesh.Vertices.size());
	for (size_t i = 0; i < mesh.Vertices.size(); i++) {
		positions.push_back(glm::vec3(mesh.Vertices[i].Position.X, mesh.Vertices[i].Position.Y, mesh.Vertices[i].Position.Z));
		TexCoords.push_back(glm::vec2(mesh.Vertices[i].TextureCoordinate.X, mesh.Vertices[i].TextureCoordinate.Y));
		Normals.push_back(glm::vec3(mesh.Vertices[i].Normal.X, mesh.Vertices[i].Normal.Y, mesh.Vertices[i].Normal.Z));
		//positions.push_back(*((glm::vec3*)(&mesh.Vertices[i].Position)));
		//TexCoords.push_back(*((glm::vec2*)(&mesh.Vertices[i].TextureCoordinate)));
		//Normals.push_back(*((glm::vec3*)(&mesh.Vertices[i].Normal)));
	}

	Mesh* thisMesh = new Mesh(&positions[0].x,positions.size()*3,&mesh.Indices[0],mesh.Indices.size());

	mesh_list.push_back(thisMesh);
}

void Model::LoadMaterials(const objLoad::Material& material) {
	Texture* tex = new Texture(material.map_Kd.c_str());
	if (!tex->LoadTexture(true))
	{
		printf("Failed to load texture at %s\n", material.map_Kd.c_str());
		delete tex;
		tex = new Texture("plain.png");
		tex->LoadTexture(false);
	}
	texture_list.push_back(tex);
}

void Model::ClearModel()
{
	for (size_t i = 0; i < mesh_list.size(); i++)
	{
		if (mesh_list[i])
		{
			delete mesh_list[i];
			mesh_list[i] = nullptr;
		}
	}

	for (size_t i = 0; i < texture_list.size(); i++)
	{
		if (texture_list[i])
		{
			delete texture_list[i];
			texture_list[i] = nullptr;
		}
	}
}

Model::~Model()
{
	ClearModel();
}

void Model::RenderModel() const
{
	if (opaque)
		glDisable(GL_BLEND);
	for (size_t i = 0; i < mesh_list.size(); i++)
	{
		texture_list[i]->Use();
		mesh_list[i]->Render();
	}
	if (opaque)
		glEnable(GL_BLEND);
}
void Model::Transparent(bool state) {
	opaque = !state;
}