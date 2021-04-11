#ifndef COMPUTE_SHADER_H
#define COMPUTE_SHADER_H

#include "maths/Vector3.h"

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

	void setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
	void setVector3f(const GLchar *name, const Vector3 &value);

private:
    GLuint cs;

    void compileComputeShader(const GLchar *cSource);
    void createShaderProgram();
};

#endif