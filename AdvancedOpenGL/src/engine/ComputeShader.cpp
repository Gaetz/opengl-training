#include "ComputeShader.h"

ComputeShader &ComputeShader::use()
{
    glUseProgram(id);
    return *this;
}

void ComputeShader::compile(const GLchar *source)
{
    compileComputeShader(source);
    createShaderProgram();
}

void ComputeShader::compileComputeShader(const GLchar *source)
{
    cs = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(cs, 1, &source, nullptr);
    glCompileShader(cs);
    // checkShaderErrors(vs, "compute");
}

void ComputeShader::createShaderProgram()
{
    // Create program
    id = glCreateProgram();
    glAttachShader(id, cs);
    glLinkProgram(id);

/*
    // Check for linking error
    int params = -1;
    glGetProgramiv(id, GL_LINK_STATUS, &params);
    if (params != GL_TRUE)
    {
        LOG(Error) << "Could not link shader programme GL index " << id;
        printProgramInfoLog(id);
    }
    if (!isValid(id))
    {
        LOG(Error) << "Could not validate shader" << id;
    }
*/

    // Delete shaders for they are no longer used
    glDeleteShader(cs);
}