//
// Created by gaetz on 04/12/2019.
//

#ifndef Scene_003_Triangle_H
#define Scene_003_Triangle_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"


class Scene_003_Triangle : public Scene {
public:
    Scene_003_Triangle();
    ~Scene_003_Triangle();
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
};


#endif //Scene_003_Triangle_H
