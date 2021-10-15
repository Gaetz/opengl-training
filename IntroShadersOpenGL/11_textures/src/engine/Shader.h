#ifndef SHADER_H
#define SHADER_H
 
#include "Log.h"
 #include <GL/glew.h>

class Shader
{
public:
    Shader();
    virtual ~Shader();
 
    GLuint programId;

    void compileVertexShader();
    void compileFragmentShader();
    void createShaderProgram();

 	// Sets the current shader as active
	Shader& use();
 
private:
    GLuint vs;
    GLuint fs;
 
    const char* vertexShader =
        "#version 430\n"
        "layout (location = 0) in vec3 vertexPosition;"
        "layout (location = 1) in vec2 uv;"
  
        "out vec2 textureCoordinates;"
 
        "void main ()"
        "{"
            "textureCoordinates = uv;"
            "gl_Position = vec4(vertexPosition, 1.0);"
        "}";

/*
    const char* fragmentShader =
        "#version 430\n"

        "layout (binding = 0) uniform sampler2D basicTexture;"

        "in vec2 textureCoordinates;"
        "out vec4 fragColor;"
 
        "void main ()"
        "{"
            "vec4 texel = texture(basicTexture, textureCoordinates);"
            "fragColor = texel;"
        "}";
*/

    const char* fragmentShader =
        "#version 430\n"

        "uniform vec2 iResolution;"

        "float circle(in vec2 _st, in float _radius) {"
            "vec2 dist = _st-vec2(0.5);"
            "return 1.-smoothstep(_radius-(_radius*0.01),"
                                "_radius+(_radius*0.01),"
                                "dot(dist,dist)*4.0);"
        "}"

        "vec2 tile (vec2 _st, float _zoom) {"
            "_st *= _zoom;"
            "return fract(_st);"
        "}"

        "void main(){"
            "vec2 st = gl_FragCoord.xy / iResolution.xy;"
            "st = tile(st,5.0);"

            "vec3 color = vec3(circle(st,0.6));"

            "gl_FragColor = vec4( color, 1.0 );"
        "}";
 
    void checkShaderErrors(GLuint shader, std::string shaderType);

    void printShaderInfoLog(GLuint shaderIndex);
    void printProgramInfoLog(GLuint programId);
    const char *GLTypeToString(GLenum type);
    void printAllParams(GLuint programId);
    bool isValid(GLuint programId);
 
    Shader(const Shader &) = delete;
    Shader& operator=(const Shader &) = delete;
};
 
#endif
