#include "Mesh.h"
Mesh::Mesh(const std::vector<glm::vec3>& positions, const std::vector<size_t>& indices, const std::vector<glm::vec2>& TextureCOords)
{
	CreateVAO();
	BindVAO();
	CreateIndexBuffer((size_t*)(&indices[0]), indices.size());
	CreateFloatAttribute(0, (float*)(&positions[0].x), positions.size() * 3, 3);
	CreateFloatAttribute(0, (float*)(&TextureCOords[0].x), TextureCOords.size() * 2, 2);
	UnbindVAO();
}
Mesh::Mesh(const float* const positions, size_t size)
{
	CreateVAO();
	BindVAO();
	CreateFloatAttribute(0, positions, size , 3);
	indexCount = size;
	UnbindVAO();
}
void Mesh::CreateVAO() {
	glGenVertexArrays(1, &VAO);
}
void Mesh::BindVAO() {
	glBindVertexArray(VAO);
}
void Mesh::CreateIndexBuffer(size_t* indices, size_t size) {
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
void Mesh::UnbindVAO() {
	glBindVertexArray(NULL);
}