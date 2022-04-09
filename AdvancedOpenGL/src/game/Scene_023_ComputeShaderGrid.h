#ifndef Scene_023_ComputeShaderGrid_H
#define Scene_023_ComputeShaderGrid_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"
#include "../engine/MeshObject.h"

constexpr int NUM_ELEMENTS = 2048;

struct Coords {
  GLfloat x;
  GLfloat y;
  GLfloat s;
  GLfloat t;
};

struct Rgba {
  GLfloat Red;
  GLfloat Green;
  GLfloat Blue;
  GLfloat Alpha;
};

class Scene_023_ComputeShaderGrid : public Scene {
public:
    Scene_023_ComputeShaderGrid();
    ~Scene_023_ComputeShaderGrid();
    void load();
    void clean();
    void pause();
    void resume();
    void handleEvent(const InputState &);
    void update(float dt);
    void draw();
    void setGame(Game *);

private:
    Game *game;

    GLuint dataBuffer[2];
    float inputData[NUM_ELEMENTS];
    float outputData[NUM_ELEMENTS];

    Coords* quadTexture;
    Rgba* quadVertex;
    unsigned short int* quadIndex;

    GLuint quadIBO;
    GLuint quadVBO;
    GLuint quadVAO;
    GLuint quadTextureID;

    ComputeShader computeShader;
    Shader renderShader;
};

#endif //Scene_023_ComputeShaderGrid_H
