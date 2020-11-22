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
        "#version 460\n"
        "in vec3 vp;"
        "void main() {"
        "  gl_Position = vec4 (vp, 1.0);"
        "}";

    const char* fragmentShader =
        "#version 460\n"
        "out vec4 color;"
        "void main() {"
        "  color = vec4 (0.8, 0.5, 0.0, 1.0);"
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
