/*
 * Copyright � 2012-2013 Graham Sellers
 *
 * This code is part of the OpenGL SuperBible, 6th Edition.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "sb6mfile.h"
#include <GL/glew.h>

#ifndef SB6M_FILETYPES_ONLY

//#include <GL/glcorearb.h>

class MeshObject {
   public:
    MeshObject();
    ~MeshObject();

    inline void render(unsigned int instanceCount = 1, unsigned int baseInstance = 0) {
        renderSubObject(0, instanceCount, baseInstance);
    }

    void renderSubObject(unsigned int objectIndex, unsigned int instanceCount = 1, unsigned int baseInstance = 0);

    void getSubObjectInfo(unsigned int index, GLuint &first, GLuint &count) {
        if (index >= numSubObjects) {
            first = 0;
            count = 0;
        } else {
            first = subObject[index].first;
            count = subObject[index].count;
        }
    }

    unsigned int getSubObjectCount() const { return numSubObjects; }
    GLuint getVao() const { return vao; }
    void load(const char *filename);
    void free();

   private:
    GLuint dataBuffer;
    GLuint vao;
    GLuint indexType;
    GLuint indexOffset;
    unsigned int numSubObjects;

    enum { MAX_SUB_OBJECTS = 256 };
    SB6M_SUB_OBJECT_DECL subObject[MAX_SUB_OBJECTS];
};

#endif /* SB6M_FILETYPES_ONLY */

#endif /* __OBJECT_H__ */
