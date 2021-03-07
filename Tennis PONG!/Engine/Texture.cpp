#include "Texture.h"

Texture::Texture() {
	textureID = 0;
	width = 0, height = 0, bitDepth = 0;

	fileLocation = "";
}
Texture::Texture(const char* fileLoc) {
	textureID = 0;
	width = 0, height = 0, bitDepth = 0;

	fileLocation = fileLoc;
}
Texture::Texture(const std::string& fileLoc) {
	textureID = 0;
	width = 0, height = 0, bitDepth = 0;

	fileLocation = fileLoc;
}
bool Texture::LoadTexture(bool withAlpha) {

	unsigned char* texData = stbi_load(fileLocation.c_str(), &width, &height, &bitDepth, 0);
	if (!texData) {
		std::cout << "failed to find : " << fileLocation << std::endl;
		fileLocation = "../Textures/" + fileLocation;
		std::cout << "Changing Dir to: ../Textures/" << std::endl;

		texData = stbi_load(fileLocation.c_str(), &width, &height, &bitDepth, 0);
		if (!texData) {
			std::cout << "failed to find : " << fileLocation << std::endl;
			return false;
		}
	}
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, withAlpha ? GL_RGBA : GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(texData);

	return true;
}
bool Texture::LoadTexture(bool withAlpha,bool mipMap,bool Anisotropic_mipMap,bool Nearest,bool ClampEdges) {
	unsigned char* texData = stbi_load(fileLocation.c_str(), &width, &height, &bitDepth, 0);
	if (!texData) {
		std::cout << "failed to find : " << fileLocation << std::endl;
		return false;
	}
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, withAlpha ? GL_RGBA : GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
	if (mipMap) {
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		if (Anisotropic_mipMap && glfwExtensionSupported("GL_EXT_texture_filter_anisotropic")) {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0f);
		}
	}
	else if (Nearest) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	if (ClampEdges) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}
void Texture::Use() {
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureID);
}
void Texture::UseAt(char Unit) {
	glActiveTexture(GL_TEXTURE0 + Unit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}
void Texture::ClearTexture() {
	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0, height = 0, bitDepth = 0;
}

Texture::~Texture() {
	ClearTexture();
}