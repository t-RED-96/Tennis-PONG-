#include "Sun.h"
#include "Entity.h"

void Sun::ApplyLight(GLuint colorLocationInShaderProg, GLuint ambientIntensityLocationInShaderProg, GLuint diffuseIntensityLocationInShaderProg, GLuint directionLocationInShaderProg) const
{
	glUniform3f(colorLocationInShaderProg, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocationInShaderProg, ambientIntensity);
	glUniform1f(diffuseIntensityLocationInShaderProg, diffuseIntensity);
	glm::vec3 dirn = thisObj.Front();
	glUniform3f(directionLocationInShaderProg, dirn.x, dirn.y, dirn.z);
}
