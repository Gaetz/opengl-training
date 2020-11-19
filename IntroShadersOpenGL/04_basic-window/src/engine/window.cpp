#include "window.h"

#include <iostream>

using std::cout;
using std::endl;

Window::Window(const std::string &title)
    : title(title),
      previousSeconds(0),
      currentSeconds(0),
      frameCount(0),
      context(nullptr) {}

Window::~Window() { SDL_Quit(); }

bool Window::init(int xPos, int yPos, int width, int height,
                  bool isFullscreen) {
    int flags = SDL_WINDOW_OPENGL;
    if (isFullscreen) {
        flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                            SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

        // Sdl window
        window =
            SDL_CreateWindow(title.c_str(), xPos, yPos, width, height, flags);
        if (!window) {
            return false;
        }

        // OpenGL context
        context = SDL_GL_CreateContext(window);
        if (!context) {
            return false;
        }

        // OpenGL setup
        glewExperimental = GL_TRUE;
        GLenum initGLEW(glewInit());
        if (initGLEW != GLEW_OK) {
            return false;
        }

        // Size of the viewport
        glViewport(0, 0, width, height);

        // Enable transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Window color
        glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
        return true;
    } else {
        return false;
    }
}

void Window::clearBuffer() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swapBuffer() { SDL_GL_SwapWindow(window); }

void Window::clean() {
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);
}

void Window::updateFpsCounter(float dt) {
    double elapsedSeconds;

    currentSeconds += dt;
    elapsedSeconds = currentSeconds - previousSeconds;
    /* limit text updates to 4 per second */
    if (elapsedSeconds > 0.25) {
        previousSeconds = currentSeconds;
        char tmp[128];
        double fps = (double)frameCount / elapsedSeconds;
        sprintf_s(tmp, "%s @ fps: %.2f", title.c_str(), fps);
        SDL_SetWindowTitle(window, tmp);
        frameCount = 0;
    }
    frameCount++;
}