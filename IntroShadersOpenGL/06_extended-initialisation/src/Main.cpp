#include <GL/glew.h>
#include <SDL.h>

#include <iostream>

#include "engine/GlDebug.hpp"
#include "engine/Log.h"

using std::cout;
using std::endl;

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

LogConfig LOG_CONFIG = {};

void logGlParams() {
    GLenum params[] = {
        GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
        GL_MAX_CUBE_MAP_TEXTURE_SIZE,
        GL_MAX_DRAW_BUFFERS,
        GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
        GL_MAX_TEXTURE_IMAGE_UNITS,
        GL_MAX_TEXTURE_SIZE,
        GL_MAX_VARYING_FLOATS,
        GL_MAX_VERTEX_ATTRIBS,
        GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
        GL_MAX_VERTEX_UNIFORM_COMPONENTS,
        GL_MAX_VIEWPORT_DIMS,
        GL_STEREO,
    };
    const char* names[] = {
        "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
        "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
        "GL_MAX_DRAW_BUFFERS",
        "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
        "GL_MAX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_TEXTURE_SIZE",
        "GL_MAX_VARYING_FLOATS",
        "GL_MAX_VERTEX_ATTRIBS",
        "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
        "GL_MAX_VIEWPORT_DIMS",
        "GL_STEREO",
    };
    LOG(Info) << "-----------------------------";
    LOG(Info) << "GL Context Params:";
    // integers - only works if the order is 0-10 integer return types
    for (int i = 0; i < 10; i++) {
        int v = 0;
        glGetIntegerv(params[i], &v);
        LOG(Info) << names[i] << " " << v;
    }
    // others
    int v[2];
    v[0] = v[1] = 0;
    glGetIntegerv(params[10], v);
    LOG(Info) << names[10] << " " << v[0] << " " << v[1];
    unsigned char s = 0;
    glGetBooleanv(params[11], &s);
    LOG(Info) << names[11] << " " << (unsigned int)s;
    LOG(Info) << "";
}

int main(int argc = 0, char** argv = nullptr) {
    // Handle args
    if (argc > 0) {
        for (int i = 0; i < argc; ++i) {
            cout << argv[i] << endl;
        }
    }

    SDL_Window* window = nullptr;
    SDL_GLContext context;
    int flags = SDL_WINDOW_OPENGL;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL failed to initialize" << endl;
        return 1;
    }

    // Initialize window and openGL
    window = SDL_CreateWindow("First triangle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, flags);
    context = SDL_GL_CreateContext(window);
    glewExperimental = GL_TRUE;
    glewInit();

    // Get info
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    cout << "Renderer: " << renderer << endl;
    cout << "OpenGL version supported: " << version << endl;

    // Tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST);  // enable depth-testing
    glDepthFunc(GL_LESS);     // depth-testing interprets a smaller value as "closer"

    // Set viewport and clear color
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

    if (glDebugMessageControlARB != nullptr) {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback((GLDEBUGPROCARB)debugGlErrorCallback, nullptr);
        GLuint unusedIds = 0;
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, GL_TRUE);
    }
    
    logGlParams();

    // Load
    GLfloat points[] = {0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    const char* vertexShader =
        "#version 460\n"
        "in vec3 vp;"
        "void main () {"
        "  gl_Position = vec4 (vp, 1.0);"
        "}";

    const char* fragmentShader =
        "#version 460\n"
        "out vec4 color;"
        "void main () {"
        "  color = vec4 (0.8, 0.5, 0.0, 1.0);"
        "}";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShader, NULL);
    glCompileShader(fs);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fs);
    glAttachShader(shaderProgram, vs);
    glLinkProgram(shaderProgram);

    // Game loop
    bool isRunning = true;
    while (isRunning) {
        // Inputs
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;

                default:
                    break;
            }
        }
        // Update

        // Draw
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the screen

        /* Draw Here */
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);  // Swapbuffer
    }

    // Quit
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);

    return 0;
}
