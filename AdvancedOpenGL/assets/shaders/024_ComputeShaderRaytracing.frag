#version 450

in vec4 inColor;
in vec2 outTexCoord;
out vec4 color;

uniform sampler2D currentTexture;

void main() {
  color = texture(currentTexture, outTexCoord);
}