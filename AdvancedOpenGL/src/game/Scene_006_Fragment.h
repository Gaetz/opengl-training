//
// Created by gaetz on 04/12/2019.
//

#ifndef Scene_006_Fragment_H
#define Scene_006_Fragment_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"


class Scene_006_Fragment : public Scene {
public:
    Scene_006_Fragment();
    ~Scene_006_Fragment();
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
    Shader shader;
    float timeSinceStart;
};


#endif //Scene_006_Fragment_H
