#pragma once
#include "Texture.h"
#include <vector>
#include <GL/glew.h>

class Material
{
private:
	static GLuint ShininessLocationInShderProg;
	static GLuint SpecularIntensityLocationInShderProg;
public:
	static void SetLocationsInShaderProg(GLuint ShininessLocationInShderProg, GLuint SpecularIntensityLocationInShderProg) {
		Material::ShininessLocationInShderProg = ShininessLocationInShderProg;
		Material::SpecularIntensityLocationInShderProg = SpecularIntensityLocationInShderProg;
	}
public:
	Material();
	Material(float shininess, float specularIntensity);
	Material(const std::string& fileLocation);
	Material(const std::string& fileLocation, float shininess, float specularIntensity);
	void ChangeSpecularPowerTo(float shininess);
	void ChangeSpecularIntensityTo(float shininess);
	void Load(bool loadTexWithAlpha);
	void Use() const;
	~Material();
private:
	inline void Use(GLuint ShininessLocationInShderProg, GLuint SpecularIntensityLocationInShderProg) const;
private:
	Texture* tex;
	float shininess;
	float specularIntensity;
};