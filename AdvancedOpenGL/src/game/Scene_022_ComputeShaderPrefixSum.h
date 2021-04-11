#ifndef Scene_022_ComputeShaderPrefixSum_H
#define Scene_022_ComputeShaderPrefixSum_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"
#include "../engine/MeshObject.h"

class Scene_022_ComputeShaderPrefixSum : public Scene {
public:
    Scene_022_ComputeShaderPrefixSum();
    ~Scene_022_ComputeShaderPrefixSum();
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
    GLuint vao;
    GLuint buffer;
    float totalTime;
    const float timeScale = 0.05f;
    MeshObject object;

    // Uniforms
    Matrix4 mvp;
    Matrix4 view;
    Matrix4 proj;

    Shader shader;
};


#endif //Scene_022_ComputeShaderPrefixSum_H
