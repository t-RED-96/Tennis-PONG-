#include "Mesh.h"
Mesh::Mesh(const std::vector<glm::vec3>& positions, const std::vector<size_t>& indices, const std::vector<glm::vec2>& TextureCOords)
{
	CreateVAO();
	BindVAO();
	CreateIndexBuffer((size_t*)(&indices[0]), indices.size());
	CreateFloatAttribute(0, (float*)(&positions[0].x), positions.size() * 3, 3);
	CreateFloatAttribute(1, (float*)(&TextureCOords[0].x), TextureCOords.size() * 2, 2);
	UnbindVAO();
}
Mesh::Mesh(const std::vector<glm::vec3>& positions, const std::vector<size_t>& indices, const std::vector<glm::vec2>& TextureCOords, const std::vector<glm::vec3>& Normals)
{
	CreateVAO();
	BindVAO();
	CreateIndexBuffer((size_t*)(&indices[0]), indices.size());
	CreateFloatAttribute(0, (float*)(&positions[0].x), positions.size() * 3, 3);
	CreateFloatAttribute(1, (float*)(&TextureCOords[0].x), TextureCOords.size() * 2, 2);
	CreateFloatAttribute(2, (float*)(&Normals[0].x), Normals.size() * 3, 3);
	UnbindVAO();
}
Mesh::Mesh(const float* const positions, size_t sizePositions, const size_t* const indices, size_t sizeIndices)
{
	CreateVAO();
	BindVAO();
	CreateIndexBuffer(indices, sizeIndices);
	CreateFloatAttribute(0, positions, sizePositions, 3);
	UnbindVAO();
}
Mesh::Mesh(const float* const positions, size_t size)
	:IBO(0)
{
	CreateVAO();
	BindVAO();
	CreateFloatAttribute(0, positions, size , 3);
	indexCount = size;
	UnbindVAO();
}
Mesh::~Mesh()
{
	CleanUP();
}
void Mesh::CreateVAO() {
	glGenVertexArrays(1, &VAO);
}
void Mesh::BindVAO() {
	glBindVertexArray(VAO);
}
void Mesh::CreateIndexBuffer(const size_t* indices, size_t size) {
	IBO = CreateVBO(GL_ELEMENT_ARRAY_BUFFER);
	BindVBO(GL_ELEMENT_ARRAY_BUFFER, IBO);
	StoreDataVBO(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(indices[0]), &indices[0]);
	indexCount = size;
}
void Mesh::CreateFloatAttribute(unsigned char attributeIndexInShader, const float* const data, size_t dataSize, unsigned char attributeLength) {
	GLuint vbo = CreateVBO(GL_ARRAY_BUFFER);
	BindVBO(GL_ARRAY_BUFFER, vbo);
	StoreDataVBO(GL_ARRAY_BUFFER, dataSize * sizeof(data[0]), &data[0]);
	DefineVBO_Attribute(attributeIndexInShader, GL_FLOAT,attributeLength,NULL);
	UnindVBO(GL_ARRAY_BUFFER);
	dataVBOs.push_back(vbo);
}
void Mesh::CreateIntAttribute(unsigned char attributeIndexInShader, const int* const data, size_t dataSize, unsigned char attributeLength) {
	GLuint vbo = CreateVBO(GL_ARRAY_BUFFER);
	BindVBO(GL_ARRAY_BUFFER, vbo);
	StoreDataVBO(GL_ARRAY_BUFFER, dataSize * sizeof(data[0]), &data[0]);
	DefineVBO_Attribute(attributeIndexInShader, GL_INT,attributeLength,NULL);
	UnindVBO(GL_ARRAY_BUFFER);
	dataVBOs.push_back(vbo);
}
GLuint Mesh::CreateVBO(GLenum _type) {
	GLuint id;
	glGenBuffers(1, &id);
	return id;
}
void Mesh::BindVBO(GLenum _type, GLuint vbo) {
	glBindBuffer(_type, vbo);
}
void Mesh::StoreDataVBO(GLenum _type, size_t _Total_Size_In_Bytes, const void* data) {
	glBufferData(_type, _Total_Size_In_Bytes, data, GL_STATIC_DRAW);
}
void Mesh::DefineVBO_Attribute(unsigned char index, GLenum dataTyp,unsigned char attributeLength,unsigned char strideDataSizeInBytes) {
	glVertexAttribPointer(index, attributeLength, dataTyp, GL_FALSE, strideDataSizeInBytes, nullptr);
	glEnableVertexAttribArray(index);
}
void Mesh::UnindVBO(GLenum _type) {
	glBindBuffer(_type, NULL);
}
inline void Mesh::DeleteVBO(GLuint& VBO)
{
	glDeleteBuffers(1, &VBO), VBO = 0;
}
void Mesh::CleanUP()
{
	if (IBO != 0)
		DeleteVBO(IBO);

	for (auto& VBO : dataVBOs) {
		if (VBO != 0)
			DeleteVBO(VBO);// clear can be done as array, but for turning dataVBOs = 0, we have to loop anyway 
	}//OR if(!dataVBOs.empty()) glDeleteBuffers(dataVBOs.size(), &dataVBOs[0]), dataVBOs.clear();
	
	if (VAO != 0)
		glDeleteVertexArrays(1, &VAO), VAO = 0;
	indexCount = 0;
}
void Mesh::UnbindVAO() {
	glBindVertexArray(NULL);
}

void Mesh::Render()
{
	BindVAO();
	for (GLuint i = 0;i < dataVBOs.size();i++)
		glEnableVertexAttribArray(i);

	if(IBO)
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT,0);
	else
		glDrawArrays(GL_TRIANGLES, 0, indexCount/3);

	for (GLuint i = 0;i < dataVBOs.size();i++)
		glDisableVertexAttribArray(i);
	UnbindVAO();
}

void Mesh::Render(void(*_preRenderPrepare)(Mesh*))
{
	BindVAO();
	for (GLuint i = 0;i < dataVBOs.size();i++)
		glEnableVertexAttribArray(i);

	_preRenderPrepare(this);
	if (IBO)
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, indexCount / 3);

	for (GLuint i = 0;i < dataVBOs.size();i++)
		glDisableVertexAttribArray(i);
	UnbindVAO();
}
