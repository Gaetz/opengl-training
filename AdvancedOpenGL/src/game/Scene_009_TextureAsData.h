//
// Created by gaetz on 28/08/2020.
//

#ifndef Scene_009_TextureAsData_H
#define Scene_009_TextureAsData_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"

class Scene_009_TextureAsData : public Scene {
public:
    Scene_009_TextureAsData();
    ~Scene_009_TextureAsData();
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
    GLuint texture;
    Shader shader;

    void generateTexture(float * data, int width, int height);
};


#endif //Scene_009_Textures_H
