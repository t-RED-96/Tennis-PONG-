//#ifdef ENGINE
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <vector>
#include <tuple>
#pragma once
class Mesh
{
private:
	GLuint VAO;
	GLuint IBO;
	GLuint indexCount;
	std::vector<GLuint> dataVBOs;
	glm::vec3 MinOfBoundingBox;
	glm::vec3 MaxOfBoundingBox;
public:
	Mesh() = delete;
	Mesh(const std::vector<glm::vec3>& positions, const std::vector<size_t>& indices, const std::vector<glm::vec2>& TextureCOords);
	Mesh(const std::vector<glm::vec3>& positions, const std::vector<size_t>& indices, const std::vector<glm::vec2>& TextureCOords, const std::vector<glm::vec3>& Normals);
	Mesh(const float* const positions, size_t sizePositions, const size_t* const indices, size_t sizeIndices);
	Mesh(const float* const positions,size_t size);
	~Mesh();
	inline void BindVAO();
	inline void UnbindVAO();
	GLuint IndexCount() { return indexCount; }
	void Render();
	void Render(void(*_preRenderPrepare)(Mesh*));
	std::tuple<glm::vec3, glm::vec3> GetMinMaxOfBoundingBox() { return { MinOfBoundingBox ,MaxOfBoundingBox }; }
private:
	template<typename BoundingBoxType>
	void GenerateBoundingBox(const std::vector<BoundingBoxType>& positions);

	template<unsigned char Attribute_Size>
	void GenerateBoundingBox(const float* const positions, const unsigned int size);
	
	template<unsigned char Attribute_Size>
	static float* GenerateMinMaxAttrib(const float* const data, const unsigned int size);
	
	inline void CreateVAO();
	void CreateIndexBuffer(const size_t* indices, size_t size);
	void CreateFloatAttribute(unsigned char attributeIndexInShader,const float* const data, size_t dataSize, unsigned char attributeSize);
	void CreateIntAttribute(unsigned char attributeIndexInShader,const int* const data,size_t dataSize,unsigned char attributeSize);
	inline static GLuint CreateVBO(GLenum _type);
	inline static void BindVBO(GLenum _type, GLuint vbo);
	static void StoreDataVBO(GLenum _type, size_t _Total_Size_In_Bytes, const void* data);
	static void DefineVBO_Attribute(unsigned char index, GLenum dataTyp, unsigned char attributeLength,unsigned char strideDataSizeInBytes);
	inline static void UnindVBO(GLenum _type);
	inline static void DeleteVBO(GLuint& VBO);
	void CleanUP();
};

//#endif