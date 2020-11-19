#include <SDL.h>
#include <iostream>

#include "engine/game.h"
#include "engine/window.h"

using std::cout;
using std::endl;

int main(int argc = 0, char **argv = nullptr) {
    if (argc > 0) {
        for (int i = 0; i < argc; ++i) {
            cout << argv[i] << endl;
        }
    }

    Window window = Window("Hello SDL");
    Game game;

    cout << "Hello handmade world" << endl;
    game.display();

    return 0;
}