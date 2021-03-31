#version 450 core

in vec4 vVertex;

void main(void)
{
    gl_Position = vVertex;
}