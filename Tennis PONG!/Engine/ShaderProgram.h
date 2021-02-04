//#ifdef ENGINE
#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <GL\glew.h>
#include <glm\gtc\type_ptr.hpp>

class ShaderProgram{
public:
	ShaderProgram();

	std::string ReadFile(const char* fileLocation);

	void CreateFromFiles(const char* vertexLocation);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
	void CreateFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation);

	void CreateFromString(const char* vertexCode, const char* fragmentCode);

	void Validate();

	GLuint GetProgramID() { return ID; }

	void ClearShader();

	~ShaderProgram();

	// activate deactivate the shader
	// ------------------------------------------------------------------------
	void Use()
	{
		glUseProgram(ID);
	}
	// ------------------------------------------------------------------------
	static void Stop() {
		glUseProgram(0);
	}
	// get uniform Location functions
	// ------------------------------------------------------------------------
	GLuint GetLocation(const std::string& name) const
	{
		return glGetUniformLocation(ID, name.c_str());
	}
	// utility uniform functions
	// ------------------------------------------------------------------------
	void SetBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value?1:0);
	}
	// ------------------------------------------------------------------------
	void SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void SetVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void SetVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void SetVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void SetVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void SetVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void SetVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void SetMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void SetMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void SetMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
private:
	GLuint ID;
	std::vector<GLuint> shaderIDs;//

	void CompileShader(const char* vertexCode);
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

	void LinkProgram();
};


//#endif // ENGINE