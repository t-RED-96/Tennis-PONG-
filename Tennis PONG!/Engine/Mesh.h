#ifdef ENGINE
#pragma once
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <vector>
class Mesh
{
public:
private:
	GLuint VAO;
	std::vector<GLuint> dataVBOs;
	GLuint IBO;
	GLuint indexCount;
public:
	Mesh() = delete;
	Mesh(const std::vector<glm::vec3>& positions, const std::vector<size_t>& indices, const std::vector<glm::vec2>& TextureCOords);
	Mesh(const float* const positions,size_t size);
	void BindVAO();
	void UnbindVAO();
	GLuint IndexCount() { return indexCount; }
private:
	void CreateVAO();
	void CreateIndexBuffer(size_t* indices, size_t size);
	void CreateFloatAttribute(unsigned char attributeIndexInShader,const float* const data, size_t dataSize, unsigned char attributeSize);
	void CreateIntAttribute(unsigned char attributeIndexInShader,const int* const data,size_t dataSize,unsigned char attributeSize);
	static GLuint CreateVBO(GLenum _type);
	static void BindVBO(GLenum _type, GLuint vbo);
	static void StoreDataVBO(GLenum _type, size_t _Total_Size_In_Bytes, const void* data);
	static void DefineVBO_Attribute(unsigned char index, GLenum dataTyp, unsigned char attributeLength,unsigned char strideDataSizeInBytes);
	static void UnindVBO(GLenum _type);
};

#endif