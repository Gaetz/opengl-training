#ifndef CUBE_H
#define CUBE_H

#include <array>
using std::array;

#include "../engine/Vector2.h"
#include "../engine/Vector3.h"
#include "../engine/Matrix4.h"
#include "../engine/Shader.h"
#include "Color.h"

constexpr float GRID_X_OFFSET { -5.0f };
constexpr float GRID_Z_OFFSET { -9.0f };

class Cube {
public:
    Cube() = default;
    Cube(Vector2 tilePosP, Color colorP);

    Vector2 getTilePos() const { return tilePos; }
    void setTransform(const Matrix4& newTransform) { transform = newTransform; }

    void load();
    void draw(Shader& shader);
    void clean();
    virtual void updateTransform();

protected:
    Color color { GREY };
    Vector2 tilePos { 0.0f, 0.0f };
    Vector3 pos { 0.0f, 0.0f, 0.0f };
    Matrix4 transform { Matrix4::identity };

    uint32_t vao { 0 };
    uint32_t vbo { 0 };
    static const array<float, 108> vertexPositions;

};

#endif