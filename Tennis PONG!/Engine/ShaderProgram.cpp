#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	ID = 0;
}

void ShaderProgram::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
	CompileShader(vertexCode, fragmentCode);
}

void ShaderProgram::CreateFromFiles(const char* vertexLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	const char* vertexCode = vertexString.c_str();

	CompileShader(vertexCode);
}

void ShaderProgram::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	CompileShader(vertexCode, fragmentCode);
}

void ShaderProgram::CreateFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string geometryString = ReadFile(geometryLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* geometryCode = geometryString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	CompileShader(vertexCode, geometryCode, fragmentCode);
}

std::string ShaderProgram::ReadFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s! File doesn't exist.", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void ShaderProgram::CompileShader(const char* vertexCode)
{
	ID = glCreateProgram();

	if (!ID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	AddShader(ID, vertexCode, GL_VERTEX_SHADER);

	LinkProgram();
}

void ShaderProgram::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	ID = glCreateProgram();

	if (!ID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	AddShader(ID, vertexCode, GL_VERTEX_SHADER);
	AddShader(ID, fragmentCode, GL_FRAGMENT_SHADER);

	LinkProgram();
}

void ShaderProgram::CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode)
{
	ID = glCreateProgram();

	if (!ID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	AddShader(ID, vertexCode, GL_VERTEX_SHADER);
	AddShader(ID, geometryCode, GL_GEOMETRY_SHADER);
	AddShader(ID, fragmentCode, GL_FRAGMENT_SHADER);

	LinkProgram();
}

void ShaderProgram::Validate()const
{
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glValidateProgram(ID);
	glGetProgramiv(ID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(ID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}
}

void ShaderProgram::LinkProgram()
{
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(ID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}
	Validate();
}

void ShaderProgram::ClearShader()
{
	if (ID != 0)
	{
		for (auto id : shaderIDs) {
			glDetachShader(ID, id);
			glDeleteShader(id);
		}
		shaderIDs.clear();
		glDeleteProgram(ID);
		ID = 0;
	}
}


void ShaderProgram::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);
	const GLchar* theCode[1]; theCode[0] = shaderCode;

	GLint codeLength[1]; codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
	shaderIDs.push_back(theShader);
}

ShaderProgram::~ShaderProgram()
{
	ClearShader();
}
