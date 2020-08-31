#version 450 core

layout (binding = 0) uniform sampler2D tex_object;

in VS_OUT
{
    vec2 tc;
} fs_in;

out vec4 color;

void main(void)
{
    // Read the texture and scale coordinates, then assign color
    color = texture(tex_object, fs_in.tc * vec2(3.0, 1.0));
}
