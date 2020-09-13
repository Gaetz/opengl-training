#ifndef GL_UTILS_HPP
#define GL_UTILS_HPP

#include <GL/glew.h>

// Check if extension is supported
int isExtensionSupported(const char* extname)
{
    GLint numExtensions;
    GLint i;

    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

    for (i = 0; i < numExtensions; i++)
    {
        const GLubyte * e = glGetStringi(GL_EXTENSIONS, i);
        if (!strcmp((const char *)e, extname))
        {
            return 1;
        }
    }

    return 0;
}

// Query the adress of extensions fonctions
GL3WglProc getProcAddress(const char * funcname)
{
    return gl3wGetProcAddress(funcname);
}

#endif