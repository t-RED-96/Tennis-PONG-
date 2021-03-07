#version 330

layout (location = 0) in vec3 pos;

out vec3 pass_WorldPos;

uniform mat4 model;
uniform mat4 projViewMat;

void main()
{
	vec4 worldPos = model * vec4(pos, 1.0);
	gl_Position = projViewMat * worldPos;
	pass_WorldPos = worldPos.xyz;
}