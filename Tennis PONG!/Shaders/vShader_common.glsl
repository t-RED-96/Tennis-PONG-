 #version 440                                
                                             
 layout (location = 0) in vec3 pos;          
 layout (location = 1) in vec2 TexCoord;     
 layout (location = 2) in vec3 Norml;        
                                             
 out vec2 pass_texCoord;                     
 out vec3 pass_fragPosn;                     
 out vec3 pass_normal;                       
                          
 uniform vec3 pivot;
 uniform mat4 model;                         
 uniform mat4 projViewMat;
                                             
void main(){                       
    vec3 newPos = pos - pivot;
    vec4 World_Posn = model * vec4(pos.x - pivot.x,pos.y - pivot.y,pos.z - pivot.z, 1.0);
                                             
    gl_Position = projViewMat * World_Posn;  
    pass_texCoord = TexCoord;                
    pass_fragPosn = World_Posn.xyz;                     
    pass_normal = normalize(mat3(transpose(inverse(model))) * Norml);
}