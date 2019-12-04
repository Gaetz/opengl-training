#include "math_core.h"

struct Rectangle
{
    Rectangle()
        : left(0), right(0), top(0), bottom(0), width(0), height(0) {}

    Rectangle(float left, float top, float width, float height)
        : left(left), right(left + width), top(top), bottom(top + height), width(width), height(height) {}

    virtual ~Rectangle() {}

    Vector2 getCenter()
    {
        return Vector2(left + width / 2.0f, top + height / 2);
    }

    float left;
    float right;
    float top;
    float bottom;
    float width;
    float height;
};