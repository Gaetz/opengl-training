#include <SDL.h>
#include <iostream>

#include "engine/Game.h"
#include "engine/Window.h"

using std::cout;
using std::endl;

int main(int argc = 0, char **argv = nullptr) {
    if (argc > 0) {
        for (int i = 0; i < argc; ++i) {
            cout << argv[i] << endl;
        }
    }

    Window window;
    Game game;

    cout << "Hello handmade world" << endl;
    window.display();
    game.display();

    return 0;
}
