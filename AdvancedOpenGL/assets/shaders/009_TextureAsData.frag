#version 450 core

uniform sampler2D tex;  
out vec4 color;

void main()
{
    color = texture(tex, gl_FragCoord.xy / textureSize(tex, 0)); 
}