#ifndef Scene_024_ComputeShaderRaytracing_H
#define Scene_024_ComputeShaderRaytracing_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"

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

class Scene_024_ComputeShaderRaytracing : public Scene {
public:
    Scene_024_ComputeShaderRaytracing();
    ~Scene_024_ComputeShaderRaytracing();
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

    int texWidth { 512 };
    int texHeight { 512 };

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

#endif //Scene_024_ComputeShaderRaytracing_H
