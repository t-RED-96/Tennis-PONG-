//#ifdef ENGINE
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#pragma once
class Texture
{
public:
	Texture();
	Texture(const char* fileLoc);

	bool LoadTexture(bool withAlpha);

	bool LoadTexture(bool withAlpha, bool mipMap, bool Anisotropic, bool Nearest, bool ClampEdges);

	void Use();
	void UseAt(char Unit);
	void ClearTexture();

	~Texture();
private:
	GLuint textureID;
	int width, height, bitDepth;
	std::string fileLocation;
};
//#endif