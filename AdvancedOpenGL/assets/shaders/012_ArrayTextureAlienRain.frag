#version 450 core                                                   
                                                                    
layout (location = 0) out vec4 color;                               
                                                                    
in VS_OUT                                                           
{                                                                   
    flat int alien;                                                 
    vec2 tc;                                                        
} fs_in;                                                            
                                                                    
uniform sampler2DArray texAliens;                                  
                                                                    
void main(void)                                                     
{                                                                   
    color = texture(texAliens, vec3(fs_in.tc, float(fs_in.alien)));
}     