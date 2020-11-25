/*
 * Copyright � 2012-2015 Graham Sellers
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
 */

#define _CRT_SECURE_NO_WARNINGS 1

#include "MeshObject.h"

#include <stdio.h>

#include "GL/glew.h"

MeshObject::MeshObject() : dataBuffer(0), indexType(0), vao(0) {}

MeshObject::~MeshObject() {}

void MeshObject::load(const char *filename) {
    FILE *infile = fopen(filename, "rb");
    size_t filesize;
    char *data;

    this->free();

    fseek(infile, 0, SEEK_END);
    filesize = ftell(infile);
    fseek(infile, 0, SEEK_SET);

    data = new char[filesize];

    fread(data, filesize, 1, infile);

    char *ptr = data;
    SB6M_HEADER *header = (SB6M_HEADER *)ptr;
    ptr += header->size;

    SB6M_VERTEX_ATTRIB_CHUNK *vertex_attrib_chunk = NULL;
    SB6M_CHUNK_VERTEX_DATA *vertex_data_chunk = NULL;
    SB6M_CHUNK_INDEX_DATA *index_data_chunk = NULL;
    SB6M_CHUNK_SUB_OBJECT_LIST *sub_object_chunk = NULL;
    SB6M_DATA_CHUNK *data_chunk = NULL;

    unsigned int i;
    for (i = 0; i < header->num_chunks; i++) {
        SB6M_CHUNK_HEADER *chunk = (SB6M_CHUNK_HEADER *)ptr;
        ptr += chunk->size;
        switch (chunk->chunk_type) {
            case SB6M_CHUNK_TYPE_VERTEX_ATTRIBS:
                vertex_attrib_chunk = (SB6M_VERTEX_ATTRIB_CHUNK *)chunk;
                break;
            case SB6M_CHUNK_TYPE_VERTEX_DATA:
                vertex_data_chunk = (SB6M_CHUNK_VERTEX_DATA *)chunk;
                break;
            case SB6M_CHUNK_TYPE_INDEX_DATA:
                index_data_chunk = (SB6M_CHUNK_INDEX_DATA *)chunk;
                break;
            case SB6M_CHUNK_TYPE_SUB_OBJECT_LIST:
                sub_object_chunk = (SB6M_CHUNK_SUB_OBJECT_LIST *)chunk;
                break;
            case SB6M_CHUNK_TYPE_DATA:
                data_chunk = (SB6M_DATA_CHUNK *)chunk;
                break;
            default:
                break;  // goto failed;
        }
    }

    // failed:

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    if (data_chunk != NULL) {
        glGenBuffers(1, &dataBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
        glBufferData(GL_ARRAY_BUFFER, data_chunk->data_length, (unsigned char *)data_chunk + data_chunk->data_offset,
                     GL_STATIC_DRAW);
    } else {
        unsigned int data_size = 0;
        unsigned int size_used = 0;

        if (vertex_data_chunk != NULL) {
            data_size += vertex_data_chunk->data_size;
        }

        if (index_data_chunk != NULL) {
            data_size += index_data_chunk->index_count *
                         (index_data_chunk->indexType == GL_UNSIGNED_SHORT ? sizeof(GLushort) : sizeof(GLubyte));
        }

        glGenBuffers(1, &dataBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, dataBuffer);
        glBufferData(GL_ARRAY_BUFFER, data_size, NULL, GL_STATIC_DRAW);

        if (vertex_data_chunk != NULL) {
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_data_chunk->data_size, data + vertex_data_chunk->data_offset);
            size_used += vertex_data_chunk->data_offset;
        }

        if (index_data_chunk != NULL) {
            glBufferSubData(GL_ARRAY_BUFFER, size_used,
                            index_data_chunk->index_count *
                                (index_data_chunk->indexType == GL_UNSIGNED_SHORT ? sizeof(GLushort) : sizeof(GLubyte)),
                            data + index_data_chunk->index_data_offset);
        }
    }

    for (i = 0; i < vertex_attrib_chunk->attrib_count; i++) {
        SB6M_VERTEX_ATTRIB_DECL &attrib_decl = vertex_attrib_chunk->attrib_data[i];
        glVertexAttribPointer(i, attrib_decl.size, attrib_decl.type,
                              attrib_decl.flags & SB6M_VERTEX_ATTRIB_FLAG_NORMALIZED ? GL_TRUE : GL_FALSE,
                              attrib_decl.stride, (GLvoid *)(uintptr_t)attrib_decl.data_offset);
        glEnableVertexAttribArray(i);
    }

    if (index_data_chunk != NULL) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dataBuffer);
        indexType = index_data_chunk->indexType;
        indexOffset = index_data_chunk->index_data_offset;
    } else {
        indexType = GL_NONE;
    }

    if (sub_object_chunk != NULL) {
        if (sub_object_chunk->count > MAX_SUB_OBJECTS) {
            sub_object_chunk->count = MAX_SUB_OBJECTS;
        }

        for (i = 0; i < sub_object_chunk->count; i++) {
            subObject[i] = sub_object_chunk->subObject[i];
        }

        numSubObjects = sub_object_chunk->count;
    } else {
        subObject[0].first = 0;
        subObject[0].count = indexType != GL_NONE ? index_data_chunk->index_count : vertex_data_chunk->total_vertices;
        numSubObjects = 1;
    }

    delete[] data;

    fclose(infile);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void MeshObject::free() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &dataBuffer);

    vao = 0;
    dataBuffer = 0;
}

void MeshObject::renderSubObject(unsigned int objectIndex, unsigned int instanceCount, unsigned int baseInstance) {
    glBindVertexArray(vao);

    if (indexType != GL_NONE) {
        glDrawElementsInstancedBaseInstance(GL_TRIANGLES, subObject[objectIndex].count, indexType,
                                            (void *)subObject[objectIndex].first, instanceCount, baseInstance);
    } else {
        glDrawArraysInstancedBaseInstance(GL_TRIANGLES, subObject[objectIndex].first, subObject[objectIndex].count,
                                          instanceCount, baseInstance);
    }
}
