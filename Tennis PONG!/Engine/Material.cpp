#include "Material.h"
GLuint Material::ShininessLocationInShderProg = 0;
GLuint Material::SpecularIntensityLocationInShderProg = 0;

Material::Material() 
	:shininess(0),specularIntensity(0)
{
	tex = new Texture("");
}

Material::Material(float shininess, float specularIntensity)
	:shininess(shininess),specularIntensity(specularIntensity)
{
	tex = new Texture("");
}

Material::Material(const std::string& fileLocation)
	:shininess(0), specularIntensity(0)
{
	tex = new Texture(fileLocation.c_str());
}

Material::Material(const std::string& fileLocation, float shininess, float specularIntensity)
	: shininess(shininess), specularIntensity(specularIntensity)
{
	tex = new Texture(fileLocation);
}
void Material::ChangeSpecularPowerTo(float shininess)
{
	this->shininess = shininess;
}
void Material::ChangeSpecularIntensityTo(float specularIntensity)
{
	this->specularIntensity = specularIntensity;
}
void Material::Load(bool loadTexWithAlpha)
{
	if (!tex->LoadTexture(loadTexWithAlpha))
	{
		printf("Failed to load texture at %s\n", tex->GetTextureLocationInDisk().c_str());
		delete tex;
		tex = new Texture("../Textures/plain.png");
		tex->LoadTexture(false);
	}
}

inline void Material::Use(GLuint ShininessLocationInShderProg, GLuint SpecularIntensityLocationInShderProg) const
{
	tex->Use();
	glUniform1f(SpecularIntensityLocationInShderProg, specularIntensity);
	glUniform1f(ShininessLocationInShderProg, shininess);
}

void Material::Use() const
{
	Use(ShininessLocationInShderProg, SpecularIntensityLocationInShderProg);
}

Material::~Material()
{
	delete tex;
	tex = 0;
}
