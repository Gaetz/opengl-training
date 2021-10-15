#ifndef COLOR_H
#define COLOR_H

struct Color
{
    float r;
    float g;
    float b;
    float a;

    Vector4 toVector() { return Vector4 { r, g, b, a }; }
};

constexpr Color WHITE { 1.0f, 0.9f, 0.9f, 1.0f };
constexpr Color GREY { .5f, .4f, .4f, 1.0f };
constexpr Color RED { 0.7f, 0.1f, 0.1f, 1.0f };
constexpr Color YELLOW { 1.0f, 0.8f , 0.2f, 1.0f };

#endif