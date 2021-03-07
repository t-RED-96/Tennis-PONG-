#version 330

in vec3 pass_fragPos;
flat in vec3 pass_vert1;
flat in vec3 pass_vert2;
flat in vec3 pass_vert3;


uniform float stroke;
uniform vec3 color;

out vec4 out_color;

float DistFromLine(vec3 x0,vec3 x1,vec3 x2){
/*
d = |(x0 - x1)X(x0 - x2)| / |x2 - x1|
*/
	return (length(cross(x0 - x1,x0 - x2)) / length(x2 - x1));
}

bool CheckForFragAtBorder(){
	if(stroke > DistFromLine( pass_fragPos, pass_vert1, pass_vert2 )){
		return true;
	}else if(stroke > DistFromLine( pass_fragPos, pass_vert2, pass_vert3 )){
		return true;
	}else if(stroke > DistFromLine( pass_fragPos, pass_vert1, pass_vert3 )){
		return true;
	}
	//if(stroke > length(fragPos - vert1)){
	//	return true;
	//}else if(stroke > length(fragPos - vert2)){
	//	return true;
	//}else if(stroke > length(fragPos - vert3)){
	//	return true;
	//}
	return false;
}
void main(){
	if(!CheckForFragAtBorder()){
		discard;
	}else{
		out_color = vec4(color,1.0);
	}
}