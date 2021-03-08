 #version 440                  
                               
 in vec2 pass_texCoord;        
 in vec3 pass_fragPosn;        
 in vec3 pass_normal;          
                               
 struct Light{                 
    vec3 color;                
    float ambient_Int;         
    float diffuse_Int;         
 };                            
 struct DirectionalLight{      
    Light base;                
    vec3 direction;            
 };                            
 struct Material{
	float specular_Int;
	float shininess;
};
                               
 uniform sampler2D diffuse_Tex;       
 uniform DirectionalLight mainLight;  
 uniform Material material;       
 uniform vec3 eyePosition;       
                               
 out vec4 out_color;           
                               
vec3 CalcLightColorByDirn(Light light,vec3 dirn){
    float factor_amb = light.ambient_Int;
    float factor_diff = dot(pass_normal, dirn);  
    float factor_spec = 0.0f;  
    factor_diff *= light.diffuse_Int;                       
    
    if(factor_diff > 0.0f){
        vec3 fragToEye = normalize(eyePosition - pass_fragPosn);
        vec3 reflectedVertex = normalize(reflect(dirn, pass_normal));
        float specularFactor = dot(fragToEye, reflectedVertex);
		if (specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			factor_spec = material.specular_Int * specularFactor;
		}
    }

    factor_diff = max(factor_diff,0.0f);
    return light.color*(factor_amb + factor_diff + factor_spec);          
}

vec4 CalcColorByDirnlLight(){
    return vec4( CalcLightColorByDirn(mainLight.base ,mainLight.direction), 1.0f);
}
                               
void main(){                   
    vec4 finalColour = CalcColorByDirnlLight();

    out_color = vec4(1.0f,1.0f,1.0f,1.0f) * finalColour;  
}