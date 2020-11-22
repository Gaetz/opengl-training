#ifndef SHADER_H
#define SHADER_H
 
#include "Log.h"
 #include <GL/glew.h>

class Shader
{
public:
    Shader();
    virtual ~Shader();
 
    GLuint programId;

    void compileVertexShader();
    void compileFragmentShader();
    void createShaderProgram();

 	// Sets the current shader as active
	Shader& use();
 
private:
    GLuint vs;
    GLuint fs;
 
    const char* vertexShader =
        "#version 430\n"
        "layout (location = 0) in vec3 vertexPosition;"
        "layout (location = 1) in vec2 uv;"
  
        "out vec2 textureCoordinates;"
 
        "void main ()"
        "{"
            "textureCoordinates = uv;"
            "gl_Position = vec4(vertexPosition, 1.0);"
        "}";

    const char* fragmentShader =
        "#version 430\n"

        "layout (binding = 0) uniform sampler2D basicTexture;"

        "in vec2 textureCoordinates;"
        "out vec4 fragColor;"
 
        "void main ()"
        "{"
            "vec4 texel = texture(basicTexture, textureCoordinates);"
            "fragColor = texel;"
        "}";
 
    void checkShaderErrors(GLuint shader, std::string shaderType);

    void printShaderInfoLog(GLuint shaderIndex);
    void printProgramInfoLog(GLuint programId);
    const char *GLTypeToString(GLenum type);
    void printAllParams(GLuint programId);
    bool isValid(GLuint programId);
 
    Shader(const Shader &) = delete;
    Shader& operator=(const Shader &) = delete;
};
 
#endif
