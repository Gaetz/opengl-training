// #ifdef __linux__
// #include <SDL2/SDL.h>
// #elif _WIN32
// #include <SDL.h>
// #endif
// #include <GL/glew.h>

// #include "batch.h"
// #include "log.h"
// #include "resource_manager.h"
// #include "color.h"

// Batch::Batch(unsigned uMaxNumVertices)
//     : maxNumVertices(uMaxNumVertices), _uNumUsedVertices(0), _vao(0), _vbo(0), _config(GL_TRIANGLE_STRIP, 0, 0), _lastVertex(Vector2(), Vector4())
// {
//     // Optimal size for a batch is between 1-4MB in size. Number of
//     // elements that can be stored in a batch is determined by
//     // calculating #bytes used by each vertex
//     shader = ResourceManager::getShader("sprite");
//     if (maxNumVertices < 1000)
//     {
//         LOG(Error) << __FUNCTION__ << " maxNumVertices{" << maxNumVertices << "} is too small. Choose a number >= 1000 ";
//         throw;
//     }
//     //clear error codes
//     glGetError();

//     // Create batch buffer
//     // vao = VertexArray(uMaxNumVertices);
//     glGenVertexArrays(1, &_vao);
//     glBindVertexArray(_vao);
//     glGenBuffers(1, &_vbo);
//     glBindBuffer(GL_ARRAY_BUFFER, _vbo);
//     glBufferData(GL_ARRAY_BUFFER, maxNumVertices * sizeof(SpriteVertex), nullptr, GL_STREAM_DRAW);
//     // unsigned uOffset = 0;
//     // ShaderManager::enableAttribute(A_POSITION, sizeof(SpriteVertex), uOffset);
//     // uOffset += sizeof(Vector2);
//     // ShaderManager::enableAttribute(A_COLOR, sizeof(SpriteVertex), uOffset);
//     // uOffset += sizeof(Vector4);
//     // ShaderManager::enableAttribute(A_TEXTURE_COORD0, sizeof(SpriteVertex), uOffset);
//     glBindVertexArray(0);
//     // ShaderManager::disableAttribute(A_POSITION);
//     // ShaderManager::disableAttribute(A_COLOR);
//     // ShaderManager::disableAttribute(A_TEXTURE_COORD0);
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     if (GL_NO_ERROR != glGetError())
//     {
//         cleanUp();
//         LOG(Error) << __FUNCTION__ + std::string(" failed to create batch");
//         throw;
//     }
// }

// Batch::~Batch() { cleanUp(); } //~Batch

// void Batch::cleanUp()
// {
//     if (_vbo != 0)
//     {
//         glBindBuffer(GL_ARRAY_BUFFER, 0);
//         glDeleteBuffers(1, &_vbo);
//         _vbo = 0;
//     }
//     if (_vao != 0)
//     {
//         glBindVertexArray(0);
//         glDeleteVertexArrays(1, &_vao);
//         _vao = 0;
//     }
// }

// bool Batch::isBatchConfig(const BatchConfig &config) const
// {
//     return (config == _config);
// }

// bool Batch::isEmpty() const
// {
//     return (0 == _uNumUsedVertices);
// }


// bool Batch::isEnoughRoom(unsigned uNumVertices) const
// {
//     //2 extra vertices are needed for degenerate triangles between each strip
//     unsigned uNumExtraVertices = (GL_TRIANGLE_STRIP == _config.renderType && _uNumUsedVertices > 0 ? 2 : 0);
//     return (_uNumUsedVertices + uNumExtraVertices + uNumVertices <= maxNumVertices);
// } 


// Batch *Batch::getFullest(Batch *pBatch) 
// { 
//     return (_uNumUsedVertices > pBatch->_uNumUsedVertices ? this : pBatch); 
// }

// int Batch::getPriority() const 
// { 
//     return _config.priority; 
// }


// void Batch::add(const vector<SpriteVertex>& vVertices, const BatchConfig &config)
// {
//     _config = config;
//     add(vVertices);
// }

// void Batch::add(const vector<SpriteVertex>& vertices)
// {
//     //2 extra vertices are needed for degenerate triangles between each strip
//     unsigned uNumExtraVertices = (GL_TRIANGLE_STRIP == _config.renderType && _uNumUsedVertices > 0 ? 2 : 0);
//     if (uNumExtraVertices + vertices.size() > maxNumVertices - _uNumUsedVertices)
//     {
//         LOG(Error) << __FUNCTION__ << " not enough room for {" << vertices.size() << "} vertices in this batch. Maximum number of vertices allowed in a batch is {" << maxNumVertices << "} and {" << _uNumUsedVertices << "} are already used";
//         if (uNumExtraVertices > 0)
//         {
//             LOG(Error) << " plus you need room for {" << uNumExtraVertices << "} extra vertices too";
//         }
//         throw;
//     }
//     if (vertices.size() > maxNumVertices)
//     {
//         LOG(Error) << __FUNCTION__ << " can not add {" << vertices.size() << "} vertices to batch. Maximum number of vertices allowed in a batch is {" << maxNumVertices << "}";
//         throw;
//     }
//     if (vertices.empty())
//     {
//         LOG(Error) << __FUNCTION__ << " can not add {" << vertices.size() << "} vertices to batch.";
//         throw;
//     } 
//     //add vertices to buffer
//     //vao.setActive();
//     glBindVertexArray( _vao );
//     glBindBuffer(GL_ARRAY_BUFFER, _vbo);
//     if (uNumExtraVertices > 0)
//     { //need to add 2 vertex copies to create degenerate triangles between this strip
//         //and the last strip that was stored in the batch
//         glBufferSubData(GL_ARRAY_BUFFER, _uNumUsedVertices * sizeof(SpriteVertex), sizeof(SpriteVertex), &_lastVertex);
//         glBufferSubData(GL_ARRAY_BUFFER, (_uNumUsedVertices + 1) * sizeof(SpriteVertex), sizeof(SpriteVertex), &vertices[0]);
//     } // Use glMapBuffer instead, if moving large chunks of data > 1MB
//     glBufferSubData(GL_ARRAY_BUFFER, (_uNumUsedVertices + uNumExtraVertices) * sizeof(SpriteVertex), vertices.size() * sizeof(SpriteVertex), &vertices[0]);
//     glBindVertexArray(0);
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     _uNumUsedVertices += vertices.size() + uNumExtraVertices;
//     _lastVertex = vertices[vertices.size() - 1];
// }


// void Batch::render()
// {
//     if (_uNumUsedVertices == 0)
//     {
//         //nothing in this buffer to render
//         return;
//     }
//     shader.use();
//     // bool usingTexture = INVALID_UNSIGNED != _config.textureId;

//     shader.setVector3f("spriteColor", Color().toVector3());
//     shader.setMatrix4("model", _config.transformMatrix);
//     // ShaderManager::setUniform(U_USING_TEXTURE, usingTexture);
//     //ShaderManager::setTexture(0, U_TEXTURE0_SAMPLER_2D, _config.textureId);
//     // ShaderManager::setUniform(U_TRANSFORM_MATRIX, _config.transformMatrix);
//     //draw contents of buffer
//     glBindVertexArray(_vao);
//     glDrawArrays(_config.renderType, 0, _uNumUsedVertices);
//     glBindVertexArray(0);
//     //reset buffer
//     _uNumUsedVertices = 0;
//     _config.priority = 0;
// }
