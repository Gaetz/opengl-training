#ifndef COMPUTE_SHADER_H
#define COMPUTE_SHADER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

class ComputeShader
{
public:
	// Program id
	GLuint id;

	// Constructor
	ComputeShader() { }

	// Sets the current shader as active
	ComputeShader& use();

	// Compiles the shader from given source code
	void compile(const GLchar *source);

private:
    GLuint cs;

    void compileComputeShader(const GLchar *cSource);
    void createShaderProgram();
};

#endif