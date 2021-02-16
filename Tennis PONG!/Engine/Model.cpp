#include "Model.h"
#include "Entity.h"
GLuint Model::pivotLocationInShaderProg = 0;

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
	material_list.reserve(loader.LoadedMeshes.size());
	minOfBoundedBox = glm::vec3(loader.LoadedMeshes[0].Vertices[0].Position.X, loader.LoadedMeshes[0].Vertices[0].Position.Y, loader.LoadedMeshes[0].Vertices[0].Position.Z);
	maxOfBoundedBox = minOfBoundedBox;
	for (size_t i = 0; i < loader.LoadedMeshes.size(); i++)
	{
		LoadMesh(loader.LoadedMeshes[i]);
		LoadMaterials(loader.LoadedMeshes[i].MeshMaterial);
	}
	glm::vec3 mean = (minOfBoundedBox + maxOfBoundedBox)/2.0f;
	std::cout << "Pivot: " << mean.x << " , " << mean.y << " , " << mean.z<<std::endl;
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

	Mesh* thisMesh = new Mesh(positions, mesh.Indices, TexCoords, Normals);
	auto [minBB, maxBB] = thisMesh->GetMinMaxOfBoundingBox();
	for (unsigned char i = 0;i < 3;i++) {
		if (minOfBoundedBox[i] > minBB[i])
			minOfBoundedBox[i] = minBB[i];
		if (maxOfBoundedBox[i] < maxBB[i])
			maxOfBoundedBox[i] = maxBB[i];
	}
	mesh_list.push_back(thisMesh);
}

void Model::LoadMaterials(const objLoad::Material& material) {
	material_list.emplace_back(material.map_Kd);
	material_list[material_list.size() - 1].Load(true);
}

glm::vec3 Model::EvaluatePivot() const
{
	switch (pivotTyp) {
		case Pivot::Mid_Centre: 
			return (minOfBoundedBox + maxOfBoundedBox)/2.0f; 
		case Pivot::Left_Centre: 
			return glm::vec3(maxOfBoundedBox.x,(minOfBoundedBox.y + maxOfBoundedBox.y)/2.0f,(minOfBoundedBox.z + maxOfBoundedBox.z)/2.0f); 
		case Pivot::Right_Centre: 
			return glm::vec3(minOfBoundedBox.x,(minOfBoundedBox.y + maxOfBoundedBox.y)/2.0f,(minOfBoundedBox.z + maxOfBoundedBox.z)/2.0f); 
		case Pivot::Forward_Centre: 
			return glm::vec3((minOfBoundedBox.x + maxOfBoundedBox.x)/2.0f,(minOfBoundedBox.y + maxOfBoundedBox.y)/2.0f,maxOfBoundedBox.z); 
		case Pivot::Backward_Centre: 
			return glm::vec3((minOfBoundedBox.x + maxOfBoundedBox.x)/2.0f,(minOfBoundedBox.y + maxOfBoundedBox.y)/2.0f,minOfBoundedBox.z); 
		case Pivot::Left_Forward_Centre: 
			return glm::vec3(maxOfBoundedBox.x,(minOfBoundedBox.y + maxOfBoundedBox.y)/2.0f,maxOfBoundedBox.z); 
		case Pivot::Right_Forward_Centre: 
			return glm::vec3(minOfBoundedBox.x,(minOfBoundedBox.y + maxOfBoundedBox.y)/2.0f,maxOfBoundedBox.z); 
		case Pivot::Left_Backward_Centre: 
			return glm::vec3(maxOfBoundedBox.x,(minOfBoundedBox.y + maxOfBoundedBox.y)/2.0f,minOfBoundedBox.z); 
		case Pivot::Right_Backward_Centre: 
			return glm::vec3(minOfBoundedBox.x,(minOfBoundedBox.y + maxOfBoundedBox.y)/2.0f,minOfBoundedBox.z); 

		case Pivot::Mid_Bottom: /////////////////////////////////////////////////////////////////////////////////////////////////////////
			return glm::vec3((minOfBoundedBox.x + maxOfBoundedBox.x)/2.0f,minOfBoundedBox.y,(minOfBoundedBox.z + maxOfBoundedBox.z)/2.0f); 
		case Pivot::Left_Bottom: 
			return glm::vec3(maxOfBoundedBox.x,minOfBoundedBox.y,(minOfBoundedBox.z + maxOfBoundedBox.z)/2.0f); 
		case Pivot::Right_Bottom: 
			return glm::vec3(minOfBoundedBox.x,minOfBoundedBox.y ,(minOfBoundedBox.z + maxOfBoundedBox.z)/2.0f); 
		case Pivot::Forward_Bottom: 
			return glm::vec3((minOfBoundedBox.x + maxOfBoundedBox.x)/2.0f,minOfBoundedBox.y,maxOfBoundedBox.z); 
		case Pivot::Backward_Bottom: 
			return glm::vec3((minOfBoundedBox.x + maxOfBoundedBox.x)/2.0f,minOfBoundedBox.y,minOfBoundedBox.z); 
		case Pivot::Left_Forward_Bottom: 
			return glm::vec3(maxOfBoundedBox.x,minOfBoundedBox.y,maxOfBoundedBox.z); 
		case Pivot::Right_Forward_Bottom: 
			return glm::vec3(minOfBoundedBox.x,minOfBoundedBox.y,maxOfBoundedBox.z); 
		case Pivot::Left_Backward_Bottom: 
			return glm::vec3(maxOfBoundedBox.x,minOfBoundedBox.y,minOfBoundedBox.z); 
		case Pivot::Right_Backward_Bottom: 
			return glm::vec3(minOfBoundedBox.x,minOfBoundedBox.y,minOfBoundedBox.z); 

		case Pivot::Mid_Top: /////////////////////////////////////////////////////////////////////////////////////////////////////////////
			return glm::vec3((minOfBoundedBox.x + maxOfBoundedBox.x)/2.0f,maxOfBoundedBox.y,(minOfBoundedBox.z + maxOfBoundedBox.z)/2.0f); 
		case Pivot::Left_Top: 
			return glm::vec3(maxOfBoundedBox.x,maxOfBoundedBox.y,(minOfBoundedBox.z + maxOfBoundedBox.z)/2.0f); 
		case Pivot::Right_Top: 
			return glm::vec3(minOfBoundedBox.x,maxOfBoundedBox.y,(minOfBoundedBox.z + maxOfBoundedBox.z)/2.0f); 
		case Pivot::Forward_Top: 
			return glm::vec3((minOfBoundedBox.x + maxOfBoundedBox.x)/2.0f,maxOfBoundedBox.y,maxOfBoundedBox.z); 
		case Pivot::Backward_Top: 
			return glm::vec3((minOfBoundedBox.x + maxOfBoundedBox.x)/2.0f,maxOfBoundedBox.y,minOfBoundedBox.z); 
		case Pivot::Left_Forward_Top: 
			return glm::vec3(maxOfBoundedBox.x,maxOfBoundedBox.y,maxOfBoundedBox.z); 
		case Pivot::Right_Forward_Top: 
			return glm::vec3(minOfBoundedBox.x,maxOfBoundedBox.y,maxOfBoundedBox.z); 
		case Pivot::Left_Backward_Top: 
			return glm::vec3(maxOfBoundedBox.x,maxOfBoundedBox.y,minOfBoundedBox.z); 
		case Pivot::Right_Backward_Top: 
			return glm::vec3(minOfBoundedBox.x,maxOfBoundedBox.y,minOfBoundedBox.z);
	}
}

Model& Model::ChangeMaterial(float shininess, float specularIntensity) {
	for (auto& mat : material_list) {
		mat.ChangeSpecularIntensityTo(specularIntensity);
		mat.ChangeSpecularPowerTo(shininess);
	}
	return *this;
}

Model& Model::ChangePivot(Pivot typ)
{
	pivotTyp = typ;
	return *this;
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

	for (size_t i = 0; i < material_list.size(); i++)
	{
		material_list[i].~Material();
	}
	material_list.clear();
}

Model::~Model()
{
	ClearModel();
}

void Model::RenderModel() const
{
	if (opaque)
		glDisable(GL_BLEND);
	glm::vec3 pivot(EvaluatePivot());
	glUniform3f(pivotLocationInShaderProg, pivot.x, pivot.y, pivot.z);
	for (size_t i = 0; i < mesh_list.size(); i++)
	{
		material_list[i].Use();
		mesh_list[i]->Render();
	}
	if (opaque)
		glEnable(GL_BLEND);
}

Model& Model::Transparent(bool state) {
	opaque = !state;
	return *this;
}