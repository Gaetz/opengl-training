#include <GL/glew.h>
#include <SDL.h>

#include <iostream>

using std::cout;
using std::endl;

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;



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

    const char* vertex_shader =
        "#version 460\n"
        "in vec3 vp;"
        "void main () {"
        "  gl_Position = vec4 (vp, 1.0);"
        "}";

    const char* fragment_shader = 
        "#version 460\n"
        "out vec4 color;"
        "void main () {"
        "  color = vec4 (0.8, 0.5, 0.0, 1.0);"
        "}";
        

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);

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
        glUseProgram(shader_programme);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);  // Swapbuffer
    }

    // Quit
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);

    return 0;
}
