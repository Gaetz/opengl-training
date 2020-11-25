#version 450 core

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

layout (location = 0) in vec4 position;
layout (location = 4) in vec2 tc;

out VS_OUT
{
    vec2 tc;
} vs_out;

void main(void)
{
    // Calculate the world position of each vertex
    vec4 pos_vs = mv_matrix * position;
    // Pass the texture coordinate through unmodified
    vs_out.tc = tc;
    // Compute screen position of vertex
    gl_Position = proj_matrix * pos_vs;
}
