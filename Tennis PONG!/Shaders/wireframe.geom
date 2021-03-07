#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 pass_WorldPos[];

out vec3 pass_fragPos;
flat out vec3 pass_vert1;
flat out vec3 pass_vert2;
flat out vec3 pass_vert3;

void main() {
	pass_vert1 = pass_WorldPos[0];
	pass_vert2 = pass_WorldPos[1];
	pass_vert3 = pass_WorldPos[2];
	for(int i = 0; i < 3; i++) {
		gl_Position = gl_in[i].gl_Position;
		pass_fragPos = pass_WorldPos[i];
		EmitVertex();
	}
	EndPrimitive();
}